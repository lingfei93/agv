#include <ros/ros.h>
#include <actionlib_msgs/GoalID.h>
#include <ar_track_alvar_msgs/AlvarMarker.h>


ros::Publisher move_base_clear_goal;

float lastSeenZDistanceToAR; //this is the z orientation which the ar_pose_tracker should take over the steering of robot


void arTrackerCallBack(const ar_track_alvar_msgs::AlvarMarker::ConstPtr &ar_tracker_data){
	ar_track_alvar::AlvarMarker currentMarker = ar_tracker_data->markers[0];
	if (currentMarker.header != null){

		ROS_INFO("currentMarker is, %f", currentMarker.pose.pose.position.x);
	}
	


}
int main(int argc, char** argv){
	ros::init(argc, argv, "Taobot_Info");
    ros::NodeHandle n;

    actionlib_msgs::GoalID emptyGoal;
    emptyGoal.id = {}; //define an emptyGoal
    emptyGoal.time = {};

    move_base_clear_goal =  n.advertise<actionlib_msgs::GoalID>("/move_base/cancel", 10);
    


    ar_tracker_sub = n.subscribe<ar_track_alvar_msgs::AlvarMarker>("/ar_pose_marker", 5, arTrackerCallBack);
    while (ros::ok()){



    ros::spinOnce();
    }//for ros::ok();
}