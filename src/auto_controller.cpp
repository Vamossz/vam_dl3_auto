#include <cmath>
#include <functional>
#include <memory>

#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

// Minden beerkezo tavolsaghoz egy sebessegparancsot allit elo.
class AutoController : public rclcpp::Node
{
public:
  AutoController() : Node("auto_controller")
  {
    publisher_ = create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
    subscription_ = create_subscription<std_msgs::msg::Float32>(
      "obstacle_distance", 10,
      std::bind(&AutoController::on_distance, this, std::placeholders::_1));
  }

private:
  void on_distance(const std_msgs::msg::Float32::SharedPtr message)
  {
    const float distance = message->data;
    geometry_msgs::msg::Twist command;  // Alapertelmezetten minden komponens nulla.
    const char * state = "STOP";

    if (!std::isfinite(distance) || distance < 0.0F) {
      state = "INVALID INPUT - STOP";
    } else if (distance < 1.0F) {
      command.linear.x = 0.0;
    } else if (distance < 3.0F) {
      command.linear.x = 0.5;
      state = "SLOW";
    } else {
      command.linear.x = 1.5;
      state = "DRIVE";
    }

    publisher_->publish(command);
    RCLCPP_INFO(
      get_logger(), "Distance: %.2f m | %s | Speed: %.2f m/s",
      distance, state, command.linear.x);
  }

  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
  rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<AutoController>());
  rclcpp::shutdown();
  return 0;
}
