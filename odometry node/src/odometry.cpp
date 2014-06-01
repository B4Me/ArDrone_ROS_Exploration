#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include </opt/ros/groovy/include/ardrone_autonomy/Navdata.h>

#define my_pi 3.14159265358979

int32_t magX = 0;
int32_t magY = 0; 
int32_t magZ = 0;

float angX = 0;
float angY = 0; 
float angZ = 0;

float accX = 0;
float accY = 0; 
float accZ = 0;

float speedX = 0;
float speedY = 0;
float speedZ = 0;

float altitude = 0;
uint32_t timestamp = 0;

  double x = 0.0;
  double y = 0.0;
  double th = 0.0;

  double vx = 0.0;
  double vy = 0.0;
  double vth = 0.0;

// nav_callback: This function is called every time a message is published
//		 and the subscriber object picks it up. We can use the callback
// 		 function to store the data and make sense of it and use it
//		 in our state feedback controller.
void nav_callback(const ardrone_autonomy::Navdata& msg_in)
{
    magX = msg_in.magX;
    magY = msg_in.magY; 
    magZ = msg_in.magZ;
    angX = msg_in.rotX;
    angY = msg_in.rotY; 
    angZ = msg_in.rotZ;
    speedX = msg_in.vx;
    speedY = msg_in.vy;
    speedZ = msg_in.vz;
    altitude = msg_in.altd;
    timestamp = msg_in.tm;

    vx = speedX/1000;
    vy = speedY/1000;
    th = (angZ*(my_pi/180));
}

int main(int argc, char** argv){
  ros::init(argc, argv, "odometry_publisher");

  ros::NodeHandle n;
  ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 50);
  ros::NodeHandle node;
  ros::Subscriber nav_sub;
  tf::TransformBroadcaster odom_broadcaster;



  ros::Time current_time, last_time;
  current_time = ros::Time::now();
  last_time = ros::Time::now();

  ros::Rate r(200.0);

  nav_sub = node.subscribe("/ardrone/navdata", 1, nav_callback);

  while(n.ok()){

    ros::spinOnce();               // check for incoming messages
    current_time = ros::Time::now();

    //compute odometry in a typical way given the velocities of the robot
    double dt = (current_time - last_time).toSec();
    double delta_x = (vx * cos(th) - vy * sin(th)) * dt;
    double delta_y = (vx * sin(th) + vy * cos(th)) * dt;
    double delta_th = vth * dt;

    x += delta_x;
    y += delta_y;
    th += delta_th;

    //since all odometry is 6DOF we'll need a quaternion created from yaw
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);

    //first, we'll publish the transform over tf
    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = current_time;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_link";

    odom_trans.transform.translation.x = x;
    odom_trans.transform.translation.y = y;
    odom_trans.transform.translation.z = 0.0;
    odom_trans.transform.rotation = odom_quat;

    //send the transform
    odom_broadcaster.sendTransform(odom_trans);

    //next, we'll publish the odometry message over ROS
    nav_msgs::Odometry odom;
    odom.header.stamp = current_time;
    odom.header.frame_id = "odom";

    //set the position
    odom.pose.pose.position.x = x;//x;
    odom.pose.pose.position.y = y;
    odom.pose.pose.position.z = altitude/1000;
    odom.pose.pose.orientation = odom_quat;

    //set the velocity
    odom.child_frame_id = "base_link";
    odom.twist.twist.linear.x = vx;
    odom.twist.twist.linear.y = vy;
    odom.twist.twist.angular.z = vth;

    //publish the message
    odom_pub.publish(odom);

    last_time = current_time;
    r.sleep();
  }
}
