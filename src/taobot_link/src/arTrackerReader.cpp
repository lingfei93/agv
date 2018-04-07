#include <ros/ros.h>
#include <actionlib_msgs/GoalID.h>
#include <ar_track_alvar_msgs/AlvarMarkers.h>
#include <ar_track_alvar_msgs/AlvarMarkers.h>
#include <tf/transform_datatypes.h> //for yaw;



ros::Publisher move_base_clear_goal;
ros::Subscriber ar_tracker_sub;
float lastSeenZDistanceToAR; //this is the z orientation which the ar_pose_tracker should take over the steering of robot
float orientationOfQR;
int followPath;
void moveToTrolley();
void moveToAngularPosition();
void moveToVerticalPosition();
void moveToHorizontalPosition(); 


void arTrackerCallBack(const ar_track_alvar_msgs::AlvarMarkers::ConstPtr &ar_tracker_data){
	
	if (ar_tracker_data->markers.size() > 0){
		ar_track_alvar_msgs::AlvarMarker currentMarker = ar_tracker_data->markers[0];
		lastSeenZDistanceToAR = currentMarker.pose.	pose.position.z;
		ROS_INFO("currentMarker z is, %f", currentMarker.pose.pose.position.z);
		ROS_INFO("currentMarker x is, %f", currentMarker.pose.pose.position.x);
		ROS_INFO("currentMarker y is, %f", currentMarker.pose.pose.position.yz);
	 	orientationOfQR = tf::getYaw(currentMarker.pose.pose.orientation);
	 	ROS_INFO("orientationOfQR is, %f", orientationOfQR);
	}
	


}
void arMarkerMoveCallBack(const std_msgs::Int32::ConstPtr &msg){
	if (msg.data == 1){
		followPath = 1;
	}
	if (msg.data == 0){
		followPath = 0;
	}
}
void moveToTrolley(){
	moveToAngularPosition();
	moveToVerticalPosition();
	moveToHorizontalPosition();
}
int main(int argc, char** argv){
	ros::init(argc, argv, "Taobot_Info");
    ros::NodeHandle n;

    actionlib_msgs::GoalID emptyGoal;
    // emptyGoal.id = {}; //define an emptyGoal
    // emptyGoal.time = {};

    move_base_clear_goal =  n.advertise<actionlib_msgs::GoalID>("/move_base/cancel", 10);
    


    ar_tracker_sub = n.subscribe<ar_track_alvar_msgs::AlvarMarkers>("/ar_pose_marker", 5, arTrackerCallBack);

    move_to_trolley_sub = n.subscribe<std_msgs::Int32>("/tow_cmd", 5, arMarkerMoveCallBack);
    while (ros::ok()){
    	if (followPath == 1){
    		moveToTrolley();
    	}



    ros::spinOnce();
    }//for ros::ok();
}