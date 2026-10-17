#include <array>
#include <chrono>
#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

// Szimulalt tavolsagszenzor: a harom ertek mindharom uzemmodot bemutatja.
class DistanceSensor : public rclcpp::Node
{
public:
  DistanceSensor() : Node("distance_sensor")
  {
    publisher_ = create_publisher<std_msgs::msg::Float32>("obstacle_distance", 10);
    timer_ = create_wall_timer(
      std::chrono::seconds(2), std::bind(&DistanceSensor::publish_distance, this));
  }

private:
  void publish_distance()
  {
    std_msgs::msg::Float32 message;
    message.data = distances_[index_];
    publisher_->publish(message);
    RCLCPP_INFO(get_logger(), "Obstacle distance: %.2f m", message.data);
    index_ = (index_ + 1) % distances_.size();
  }

  const std::array<float, 3> distances_{{5.0F, 2.0F, 0.5F}};
  std::size_t index_{0};
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<DistanceSensor>());
  rclcpp::shutdown();
  return 0;
}
