#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <geometry_msgs/Twist.h>
#include <actionlib_msgs/GoalID.h>
#include <ar_track_alvar_msgs/AlvarMarkers.h>
#include <ar_track_alvar_msgs/AlvarMarkers.h>
#include <tf/transform_datatypes.h> //for yaw;
#include <tf/transform_listener.h> //for transform_listener



ros::Publisher move_base_clear_goal;
ros::Subscriber ar_tracker_sub;
ros::Publisher move_base_path_pub;
ros::Subscriber move_to_trolley_sub;
float lastZ, lastX, lastYaw; //this is the z orientation which the ar_pose_tracker should take over the steering of robot
float orientationOfQR;
int followPath, moveToAngular, moveToVertical, moveToHorizontal, angularPositionReached, count;

void moveToAngularPosition();
void moveToVerticalPosition();
void moveToHorizontalPosition(); 
void sendVelToRobot(float x_speed, float y_speed, float angle, float timeToWriteSpeed);
float desiredZ = 0.637;
float desiredX = 0.196;
float desiredYaw = 0.02;
//z is 0.637
//x is 0.196


void arTrackerCallBack(const ar_track_alvar_msgs::AlvarMarkers::ConstPtr &ar_tracker_data){
	
	if (ar_tracker_data->markers.size() > 0){
		ar_track_alvar_msgs::AlvarMarker currentMarker = ar_tracker_data->markers[0];
		lastZ = currentMarker.pose.pose.position.z;
		lastX = currentMarker.pose.pose.position.x;
		ROS_INFO("currentMarker z is, %f", currentMarker.pose.pose.position.z);
		ROS_INFO("currentMarker x is, %f", currentMarker.pose.pose.position.x);
		ROS_INFO("currentMarker y is, %f", currentMarker.pose.pose.position.y);
	 	lastYaw = tf::getYaw(currentMarker.pose.pose.orientation);
	 	ROS_INFO("orientationOfQR is, %f", lastYaw);
	 	count++;

	}
	


}
void arMarkerMoveCallBack(const std_msgs::Int32::ConstPtr &msg){

	ROS_INFO("recieved info for ar_marker_callback, it is, %d", msg->data);
	if (msg->data == 1){
		followPath = 1;
		moveToVertical = 1;
	}
	if (msg->data == 0){
		followPath = 0;
	}
}
void moveToVerticalPosition(){
	float scalingFactor = 5.5;
	float timeToSendSpeed = abs(desiredX - lastX);
    if(timeToSendSpeed < 0.05){
    	moveToVertical = 0;
    	moveToHorizontal = 1;
    }
    else {
    	sendVelToRobot(0, (desiredX - lastX)/timeToSendSpeed, 0, timeToSendSpeed * scalingFactor); //second variable is direction, last is control amount to send
	}
}

void moveToHorizontalPosition(){
	float scalingFactor = 5.5;
	float timeToSendSpeed = abs(desiredZ - lastZ);
    if(timeToSendSpeed < 0.05){
    	moveToHorizontal = 0;
    	moveToAngular = 1;
    }
    else {
    	sendVelToRobot((desiredZ - lastZ)/timeToSendSpeed, 0 , 0, timeToSendSpeed * scalingFactor); //second variable is direction, last is control amount to send
	}
}

void moveToAngularPosition(){
	ROS_INFO("entering angular control");
	float scalingFactor = 5.5;
	float timeToSendSpeed = abs(desiredYaw - lastYaw);
    if(timeToSendSpeed < 0.05){
    	moveToAngular = 0;
    	angularPositionReached = 1;
    }
    else {
    	sendVelToRobot(0, 0 , (desiredYaw - lastYaw)/timeToSendSpeed, timeToSendSpeed * scalingFactor); //second variable is direction, last is control amount to send
	}
}



void sendVelToRobot(float x_speed, float y_speed, float angle, float timeToWriteSpeed){
	geometry_msgs::Twist wlr_cmd;
	wlr_cmd.linear.x         = x_speed * 0.2;
    wlr_cmd.linear.y        = y_speed * 0.2;
    wlr_cmd.angular.z = angle * 0.2;
    ROS_INFO("timeToWriteSpeed is %f", timeToWriteSpeed);
    move_base_path_pub.publish(wlr_cmd);

    ros::Duration(timeToWriteSpeed).sleep();
    wlr_cmd.linear.x         = 0;
    wlr_cmd.linear.y        = 0;
    wlr_cmd.angular.z = 0;
    move_base_path_pub.publish(wlr_cmd);




}

void moveToTrolley(){
	ROS_INFO("enter moveTrolley");
	float timeToWriteSpeed = lastZ * 6.25;
	sendVelToRobot(1, 0, 0, timeToWriteSpeed);
}

int main(int argc, char** argv){
	ros::init(argc, argv, "Taobot_Info");
    ros::NodeHandle n;

    actionlib_msgs::GoalID emptyGoal;
    // emptyGoal.id = {}; //define an emptyGoal
    // emptyGoal.time = {};

    move_base_clear_goal =  n.advertise<actionlib_msgs::GoalID>("/move_base/cancel", 10);
    
	move_base_path_pub = n.advertise<geometry_msgs::Twist>("cmd_vel_path", 100);

    ar_tracker_sub = n.subscribe<ar_track_alvar_msgs::AlvarMarkers>("/ar_pose_marker", 5, arTrackerCallBack);

    move_to_trolley_sub = n.subscribe<std_msgs::Int32>("/tow_cmd", 5, arMarkerMoveCallBack);


	//this is for the pose of the ar_tag for control purposes
    tf::TransformListener listener;
    geometry_msgs::PoseStamped robot_pose;
    tf::StampedTransform poseRobot;
    while (   ros::ok()){
    	if (followPath == 1 && moveToVertical == 1){
    		moveToTrolley(); 
    		moveToVertical = 0;//testMoveToTrolley();
    		//moveToVerticalPosition();
    	}
    	if (followPath == 1 && moveToHorizontal ==1){
    		moveToHorizontalPosition();
    	}
    	if (followPath == 1 && moveToAngular == 1){
    		moveToAngularPosition();
    	}
    	if (followPath == 1 && angularPositionReached == 1){
    		moveToTrolley();
    	}



    ros::spinOnce();
    }//for ros::ok();
}