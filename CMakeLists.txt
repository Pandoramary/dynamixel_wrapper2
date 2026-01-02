cmake_minimum_required(VERSION 3.5)
project(dynamixel_wrapper)

# C++14 を使用
set(CMAKE_CXX_STANDARD 14)

# 必要なパッケージを探す
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(dynamixel_sdk REQUIRED)
find_package(std_msgs REQUIRED)

include_directories(
  include
)

# ライブラリのビルド（元の dynamixel_wrapper.cpp をライブラリ化）
add_library(${PROJECT_NAME}
  src/dynamixel_wrapper/dynamixel_wrapper.cpp
)
ament_target_dependencies(${PROJECT_NAME}
  rclcpp
  dynamixel_sdk
  std_msgs
)

# 実行ノードのビルド（例：position_control.cpp）
add_executable(position_node src/examples/position_control.cpp)
target_link_libraries(position_node ${PROJECT_NAME})
ament_target_dependencies(position_node
  rclcpp
  dynamixel_sdk
  std_msgs
)

add_executable(positioning_node src/examples/positioning_control.cpp)
target_link_libraries(positioning_node ${PROJECT_NAME})
ament_target_dependencies(positioning_node
  rclcpp
  dynamixel_sdk
  std_msgs
<<<<<<< HEAD
=======
)

add_executable(positioning_control_subscriber_node src/examples/position_control_subscriber.cpp)
target_link_libraries(positioning_control_subscriber_node ${PROJECT_NAME})
ament_target_dependencies(positioning_control_subscriber_node
  rclcpp
  dynamixel_sdk
  std_msgs
>>>>>>> 5ac5b7b (2026/01/02 よくわからんけどコミット)
)

# インストール設定
install(TARGETS
  ${PROJECT_NAME}
  position_node
  positioning_node
  positioning_control_subscriber_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION include/${PROJECT_NAME}
)

ament_package()