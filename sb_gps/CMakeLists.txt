cmake_minimum_required(VERSION 2.8.3)
project(sb_gps)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  sb_msgs
  message_generation
)

add_service_files(
	FILES
	GotoWaypoint.srv
)

generate_messages(
	DEPENDENCIES
	std_msgs
	sb_msgs
)

catkin_package(
CATKIN_DEPENDS roscpp rospy std_msgs sb_msgs message_runtime
)

## catkin_add_gtest(utest test/gps_test.cpp)

include_directories(${catkin_INCLUDE_DIRS})

add_executable(sb_gps src/gps.cpp)

add_dependencies(sb_gps sb_msgs_generate_messages_cpp)
add_dependencies(sb_gps sb_gps_generate_messages_cpp)
add_executable(createAngleTrial src/createAngleTrial.cpp)

target_link_libraries(sb_gps ${catkin_LIBRARIES})
target_link_libraries(createAngleTrial ${catkin_LIBRARIES})

## To add package paths:
## source ~/catkin_ws/devel/setup.bash
