cmake_minimum_required(VERSION 3.8)
project(vam_dl3_auto)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

add_executable(distance_sensor src/distance_sensor.cpp)
ament_target_dependencies(distance_sensor rclcpp std_msgs)

add_executable(auto_controller src/auto_controller.cpp)
ament_target_dependencies(auto_controller rclcpp std_msgs geometry_msgs)

install(TARGETS distance_sensor auto_controller
  DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME})

ament_package()
