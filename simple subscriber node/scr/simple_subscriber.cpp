/*
Bjørn Smith
University of Southern Denmark 2014
*/
#include <ros/ros.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>
#include </opt/ros/groovy/stacks/ardrone_autonomy/msg_gen/cpp/include/ardrone_autonomy/Navdata.h>

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
uint32_t lasttimestamp = 0;
bool firsttime = true;

uint32_t tags_count;
uint32_t tags_xc[10];
// nav_callback: This function is called every time a message is published
//		 and the subscriber object picks it up. We can use the callback
// 		 function to store the data and make sense of it and use it
//		 in our state feedback controller.
void nav_callback(const ardrone_autonomy::Navdata& msg_in)
{
	/*
	// Take in state of ardrone	
	printf("vector: %f\n", msg_in.tags_xc.size());
	//vx = msg_in.vx;
	tags_count=msg_in.tags_count;
	// Write it to the terminal
	for (uint32_t i=0; i < tags_count; i++)
    {
		tags_xc[i]=msg_in.tags_xc[i];
    }
    * */
    magX = msg_in.magX;
    magY = msg_in.magY; 
    magZ = msg_in.magZ;
    angX = msg_in.rotX;
    angY = msg_in.rotY; 
    angZ = msg_in.rotZ;
    accX = msg_in.ax;
    accY = msg_in.ay;
    accZ = msg_in.az;
    speedX = msg_in.vx;
    speedY = msg_in.vy;
    speedZ = msg_in.vz;
    altitude = msg_in.altd;
    timestamp = msg_in.tm;
}
			
int main(int argc, char** argv)
{
	printf("Simple Subscriber Starting");
	ros::init(argc, argv,"Subscriber_Tester"); // can be seen using rxgraph or rqt_graph
	ros::NodeHandle node;
	ros::Subscriber nav_sub;	

	while (ros::ok()) 
	{
		// ardrone_autonomy/Navdata publishes on /ardrone/navdata
		nav_sub = node.subscribe("/ardrone/navdata", 1, nav_callback);
		if(lasttimestamp < timestamp){
			lasttimestamp = timestamp;	
			if(firsttime==true){
				firsttime = false;
				//printf("Time, angX, angY, angZ, magX, magY, magZ, accX, accY, accZ, vx, vy, vz, altitude\n");
				//printf("Time, vx, vy\n");
			}	
			printf("%u,%f,%f", timestamp, speedX, speedY);
			fflush(stdout);
			//printf("%u, %f, %f, %f, %d, %d, %d, %f, %f, %f, %f, %f, %f, %f\n", timestamp, angX, angY, angZ, magX, magY, magZ, accX, accY, accZ, speedX, speedY, speedZ, altitude);

			//printf("Time: %u, angX: %f, angY: %f, angZ: %f, vx: %f, vy: %f, vz: %f, altitude: %f\n", timestamp, angX, angY, angZ, speedX, speedY, speedZ, altitude);
		}	
		//ROS_INFO("getting sensor reading: %f [mm/s]", vx);
		//ROS_INFO("Tag Distance: X: %f", tagx/*, msg_in.tags_yc, msg_in.tags_distance*/);	
		ros::spinOnce(); 	// receive published messages constantly
	}
	return 0; 	
}


