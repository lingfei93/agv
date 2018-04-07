#include <ros/ros.h>
#include <actionlib_msgs/GoalID.h>
#include <ar_track_alvar_msgs/AlvarMarkers.h>
#include <ar_track_alvar_msgs/AlvarMarkers.h>


ros::Publisher move_base_clear_goal;
ros::Subscriber ar_tracker_sub;
float lastSeenZDistanceToAR; //this is the z orientation which the ar_pose_tracker should take over the steering of robot


void arTrackerCallBack(const ar_track_alvar_msgs::AlvarMarkers::ConstPtr &ar_tracker_data){
	
	if (ar_tracker_data->markers){
		ar_track_alvar_msgs::AlvarMarker currentMarker = ar_tracker_data->markers[0];
		ROS_INFO("currentMarker is, %f", currentMarker.pose.pose.position.x);
	}
	


}
int main(int argc, char** argv){
	ros::init(argc, argv, "Taobot_Info");
    ros::NodeHandle n;

    actionlib_msgs::GoalID emptyGoal;
    // emptyGoal.id = {}; //define an emptyGoal
    // emptyGoal.time = {};

    move_base_clear_goal =  n.advertise<actionlib_msgs::GoalID>("/move_base/cancel", 10);
    


    ar_tracker_sub = n.subscribe<ar_track_alvar_msgs::AlvarMarkers>("/ar_pose_marker", 5, arTrackerCallBack);
    while (ros::ok()){



    ros::spinOnce();
    }//for ros::ok();
}