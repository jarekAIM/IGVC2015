cmake_minimum_required(VERSION 2.8.3)
project(sb_msgs)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)

## Generate messages in the 'msg' folder
 add_message_files(
   FILES
   gps.msg
   AISimMap.msg
   AISimGPS.msg
   CarCommand.msg
   GPSWaypoint.msg
   IMU.msg
   jausin.msg
   jausout.msg
   LidarNav.msg
   Pose.msg
   RobotState.msg
   ServoCommand.msg
   TurretCommand.msg
   Velocity.msg
   VisionNav.msg
   Waypoint.msg
   WaypointList.msg
 )

## Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
   std_msgs
 )

catkin_package(
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime

)

include_directories(
  ${catkin_INCLUDE_DIRS}
)
