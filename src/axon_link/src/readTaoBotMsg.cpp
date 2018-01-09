#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <math.h>
#include "serial/serial.h"
#include <axon_link/Taobot.h>

using namespace std;
void taoBotCallback(const axon_link::Taobot::ConstPtr& msg)
{
  ROS_INFO("I heard: [%d %d %d %d %d %d %d]", msg.motorA_encoder, msg.motorA_dir, msg.motorB_encoder, msg.motorB_dir, msg.motorC_encoder, msg.motorC_dir, voltage);
}

int main(int argc, char **argv){
	ros::init(argc, argv, "Taobot_reciever");
	ros::NodeHandle n;



	ros::Subscriber sub = n.subscribe("taobot_listener", 1000, taobotCallback);


	ros::spin();


	return 0;



}