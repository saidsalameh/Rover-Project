cmake_minimum_required(VERSION 3.8)
project(pi_nodes)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

# Find ROS 2 packages
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# Add your executable (repeat this block for each node)
add_executable(sensor_publisher src/sensor_publisher.cpp)
ament_target_dependencies(sensor_publisher rclcpp std_msgs)

add_executable(motor_controller src/motor_controller.cpp)  
ament_target_dependencies(motor_controller rclcpp std_msgs)

# Install the executables
install(TARGETS
  sensor_publisher
  motor_controller
  DESTINATION lib/${PROJECT_NAME}
)

# Install launch files (if you have any)
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)

# Export dependencies
ament_export_dependencies(rclcpp std_msgs)

# Finally, generate the package
ament_package()
