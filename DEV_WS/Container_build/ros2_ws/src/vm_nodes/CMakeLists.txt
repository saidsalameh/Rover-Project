cmake_minimum_required(VERSION 3.8)
project(vm_nodes)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

# Find ROS 2 packages
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# Find Python packages if you have Python nodes
find_package(ament_cmake_python REQUIRED)
find_package(rclpy REQUIRED)

# Add your C++ executable (repeat for each C++ node)
add_executable(visualization_node src/visualization_node.cpp)
ament_target_dependencies(visualization_node rclcpp std_msgs)

add_executable(mission_control src/mission_control.cpp)
ament_target_dependencies(mission_control rclcpp std_msgs)

# Add your Python nodes (repeat for each Python node)
# Note: Python nodes need to be marked as executable in the filesystem
install(PROGRAMS
  scripts/visualization_gui.py
  scripts/data_logger.py
  DESTINATION lib/${PROJECT_NAME}
)

# Install the C++ executables
install(TARGETS
  visualization_node
  mission_control
  DESTINATION lib/${PROJECT_NAME}
)

# Install Python modules
install(DIRECTORY
  vm_nodes/
  DESTINATION lib/${PROJECT_NAME}
)

# Install launch files
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)

# Install config files (if you have any)
install(DIRECTORY
  config
  DESTINATION share/${PROJECT_NAME}
)

# Export dependencies
ament_export_dependencies(rclcpp std_msgs rclpy)

# Finally, generate the package
ament_package()
