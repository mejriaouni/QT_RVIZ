cmake_minimum_required(VERSION 3.0.2)
project(qt_rviz)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  rviz
  rviz_visual_tools
  message_generation
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)
add_message_files(
  FILES
  Shape.msg
  Shapes.msg
)
generate_messages(
  DEPENDENCIES
  std_msgs
  geometry_msgs
)
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES qt_rviz
  CATKIN_DEPENDS roscpp rospy message_runtime
#  DEPENDS system_lib
)
############ INCLUSION OF Qt ################
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
add_executable(qt_rviz
    src/main.cpp
    qt_files/mainwindow.cpp
  )
 target_link_libraries(qt_rviz ${catkin_LIBRARIES} Qt5::Widgets )
 target_include_directories(qt_rviz PRIVATE qt_files)
 add_dependencies(qt_rviz qt_rviz_generate_messages_cpp)
