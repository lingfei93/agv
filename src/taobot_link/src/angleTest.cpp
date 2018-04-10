#include <std_msgs/Int32.h>
#include <math.h>
#include <geometry_msgs/Twist.h>
#include <actionlib_msgs/GoalID.h>
#include <ar_track_alvar_msgs/AlvarMarker.h>
#include <ar_track_alvar_msgs/AlvarMarkers.h>
#include <tf/transform_datatypes.h> //for yaw;
#include <tf/transform_listener.h> //for transform_listener

ros::Subscriber ar_tracker_sub;

void arTrackerCallBack(const ar_track_alvar_msgs::AlvarMarkers::ConstPtr &ar_tracker_data){
	ar_track_alvar_msgs::AlvarMarker currentMarker;
	float z, w, y, x, angle, angle2, yaw, pitch, roll;
	
	if (ar_tracker_data->markers.size() == 1 || ar_tracker_data->markers.size() == 2){
            currentMarker = ar_tracker_data->markers[0];
            
            z = currentMarker.pose.pose.orientation.z;
            w = currentMarker.pose.pose.orientation.w;
            y = currentMarker.pose.pose.orientation.y;
            x = currentMarker.pose.pose.orientation.x;
            angle = (2*acos(w));
            angle2 = z/sin(angle/2);
            ROS_INFO("angle 1 is : %f,angle2 is : %f", angle, angle2);
            
            yaw = atan2(2.0*(y*z + w*x), w*w - x*x - y*y + z*z);
			pitch = asin(-2.0*(x*z - w*y));
			roll = atan2(2.0*(x*y + w*z), w*w + x*x - y*y - z*z);	
			ROS_INFO("yaw is %f, pitch is %f, roll is %f", yaw, pitch, roll);
	}


    else if(ar_tracker_data->markers.size() == 0){
        //lastseenMarkeris 0
        ROS_INFO("CANNOT SEE MARKER");
        //lastSeenMarker = 0;
    }

}

int main(int argc, char** argv){
	ros::init(argc, argv, "Taobot_Info");
	ros::NodeHandle n;
	
	//Create subscriber
	ar_tracker_sub = n.subscribe<ar_track_alvar_msgs::AlvarMarkers>("/ar_pose_marker", 5, arTrackerCallBack);
	
	ros::spin();
	/*
	ros::Rate r(1);
    while (ros::ok()){
    	
    }
    */
}