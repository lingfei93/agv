#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Int32.h>
#include <actionlib_msgs/GoalID.h>
#include <iostream>

ros::Publisher stop_pub;

void stopReceived(const std_msgs::Int32::ConstPtr& msg){
	if (msg->data==1){
		actionlib_msgs::GoalID stop_msg;
		stop_msg = {};
		stop_pub.publish(stop_msg);
	}
}

int main(int argc, char **argv){
	ros::init(argc, argv, "stop_ctrl");
	ros::NodeHandle n;
	
	//Create subscriber
	ros::Subscriber stop_listener  = n.subscribe<std_msgs::Int32>("stop_cmd", 1000, stopReceived);
	//Create publisher
	stop_pub = n.advertise<actionlib_msgs::GoalID>("move_base/cancel", 1000);

    actionlib_msgs::GoalID stop_msg;
    stop_msg = {};
	
	
	ros::Rate loop_rate(5);
	
	while (ros::ok()){
		
        //stop_pub.pub(stop_msg);
	
		ros::spinOnce();
	}
	
	return 0;
}
