#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <math.h>
#include "serial/serial.h"
#include <axon_link/Taobot.h>
void taoBotCallback(const axon_link::Taobot::ConstPtr& msg);

using namespace std;
void taoBotCallback(const axon_link::Taobot::ConstPtr& msg)
{
  ROS_INFO("I heard: [%d %d %d %d %d %d %d]", msg->data.motorA_encoder, msg->data.motorA_dir, 
  	msg->data.motorB_encoder, msg->data.motorB_dir, msg->data.motorC_encoder, 
  	msg->data.motorC_dir, msg->data.voltage);
}

int main(int argc, char **argv){
	ros::init(argc, argv, "Taobot_reciever");
	ros::NodeHandle n;



	ros::Subscriber sub = n.subscribe("taobot_listener", 1000, taoBotCallback);


	ros::spin();


	return 0;



}