#! /bin/bash

export PATH=/opt/ros/groovy/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games
export ROS_ROOT=/opt/ros/groovy/share/ros
export ROS_PACKAGE_PATH=/opt/ros/groovy/share:/opt/ros/groovy/stacks
export ROS_MASTER_URI=http://localhost:11311
export LD_LIBRARY_PATH=/opt/ros/groovy/lib
export CPATH=/opt/ros/groovy/include
export ROS_DISTRO=groovy
export PYTHONPATH=/opt/ros/groovy/lib/python2.7/dist-packages
export PKG_CONFIG_PATH=/opt/ros/groovy/lib/pkgconfig
export CMAKE_PREFIX_PATH=/opt/ros/groovy
export ROS_ETC_DIR=/opt/ros/groovy/etc/ros

source ~/catkin_ws/devel/setup.sh


roslaunch ardrone_autonomy ardrone.launch &
