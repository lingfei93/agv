
#include <std_msgs/Int32.h>
#include <math.h>
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
float previousZ, previousX, previousYaw;
float sleepFactor, speedFactor, calibratedParam,verticalScalingTime,verticalSpeedScale, horizontalScalingTime, horizontalSpeedScale;
int followPath, moveToAngular, moveToVertical, moveToHorizontal, angularPositionReached, count, inFinalControl = 0;
int verticalCount, horizontalCount;
void moveToAngularPosition();
void moveToVerticalPosition();
void moveToHorizontalPosition(); 
int checkIfShouldUpdate(float z, float x, float yaw);
//void updateValues(float z, float x, float yaw);
void sendVelToRobot(float x_speed, float y_speed, float angle, float timeToWriteSpeed);
float desiredZ = 0.745;
float desiredX = 0.229;
float desiredYaw = 0.02;
int lastSeenMarker = 0;
//z is 0.637
//x is 0.196

int checkIfShouldUpdate(float z, float x, float yaw){
    if (fabs(z - previousZ) < 0.005 && fabs(x - previousX) < 0.005 && fabs(yaw - previousYaw) < 0.005){
        lastZ = z;
        lastX = x;
        lastYaw = yaw;
        ROS_INFO("updated lastX");
    }
    else {
        lastZ = z;
        lastX = x;
        lastYaw = yaw;
    }
}

// void updateValues(float z, float x, float yaw){
//     previousZ = z;
//     previousX = x;
//     previousYaw = yaw;
// }

void arTrackerCallBack(const ar_track_alvar_msgs::AlvarMarkers::ConstPtr &ar_tracker_data){
	ar_track_alvar_msgs::AlvarMarker currentMarker;
	if (ar_tracker_data->markers.size() == 1 && inFinalControl == 1){
            currentMarker = ar_tracker_data->markers[0];
            //updateValues(currentMarker.pose.pose.position.z,currentMarker.pose.pose.position.x, 
            //tf::getYaw(currentMarker.pose.pose.orientation) );

			
            checkIfShouldUpdate(currentMarker.pose.pose.position.z, currentMarker.pose.pose.position.x,
                tf::getYaw(currentMarker.pose.pose.orientation));

			//lastZ = currentMarker.pose.pose.position.z;
			//lastX = currentMarker.pose.pose.position.x;

			ROS_INFO("currentMarker z is, %f", lastZ);
			ROS_INFO("currentMarker x is, %f", lastX);
			//ROS_INFO("currentMarker y is, %f", currentMarker.pose.pose.position.y);

		 	//lastYaw = tf::getYaw(currentMarker.pose.pose.orientation);

		 	ROS_INFO("orientationOfQR is, %f", lastYaw);
		 	count++;
            lastSeenMarker = 1;

	}

    if (ar_tracker_data->markers.size() == 1 && ((ar_tracker_data->markers[0].id % 2) == 0) ){

            currentMarker = ar_tracker_data->markers[0];
            checkIfShouldUpdate(currentMarker.pose.pose.position.z, currentMarker.pose.pose.position.x,
                tf::getYaw(currentMarker.pose.pose.orientation));
            //lastZ = currentMarker.pose.pose.position.z;
            //lastX = currentMarker.pose.pose.position.x;

            // ROS_INFO("currentMarker z is, %f", currentMarker.pose.pose.position.z);
            // ROS_INFO("currentMarker x is, %f", currentMarker.pose.pose.position.x);
            // ROS_INFO("currentMarker y is, %f", currentMarker.pose.pose.position.y);

            // lastYaw = tf::getYaw(currentMarker.pose.pose.orientation);

            ROS_INFO("orientationOfQR is, %f", lastYaw);
            lastSeenMarker = 1;
            //count++;
    }

	if (ar_tracker_data->markers.size() == 2){

			if((ar_tracker_data->markers[0].id % 2) == 0){
				currentMarker = ar_tracker_data->markers[0];
			}
			else {
				currentMarker = ar_tracker_data->markers[1];
			}

            checkIfShouldUpdate(currentMarker.pose.pose.position.z, currentMarker.pose.pose.position.x,
                tf::getYaw(currentMarker.pose.pose.orientation));
			// lastZ = currentMarker.pose.pose.position.z;
			// lastX = currentMarker.pose.pose.position.x;

			   ROS_INFO("currentMarker z is, %f", lastZ);
			// ROS_INFO("currentMarker x is, %f", currentMarker.pose.pose.position.x);
			// ROS_INFO("currentMarker y is, %f", currentMarker.pose.pose.position.y);

		 // 	lastYaw = tf::getYaw(currentMarker.pose.pose.orientation);

		 // 	ROS_INFO("orientationOfQR is, %f", lastYaw);
		 // 	count++;
               lastSeenMarker = 1;

	}

    if(ar_tracker_data->markers.size() == 0){
        //lastseenMarkeris 0
        ROS_INFO("CANNOT SEE MARKER");
        lastSeenMarker = 0;
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
	
	float timeToSendSpeed;
    timeToSendSpeed = fabs(desiredX - lastX);
    ROS_INFO("desiredX is %f, lastX is %f", desiredX, lastX);
    ROS_INFO("trying to move to Vertical Position");
    ROS_INFO("timeToSendSpeed is %f", timeToSendSpeed);
    
    if(timeToSendSpeed < 0.015){
        verticalCount++;
        ROS_INFO("verticalCount is %d", verticalCount);
        if (verticalCount > 10 ){
            verticalCount = 0;
    	    moveToVertical = 0;
            moveToHorizontal = 1;
            ROS_INFO("move into Vertical success");
        }
    	//moveToHorizontal = 1;
    }
    else {
        ROS_INFO("Time sent is %f", timeToSendSpeed * verticalScalingTime);
    	sendVelToRobot(0, (desiredX - lastX)/timeToSendSpeed * verticalSpeedScale, 0, timeToSendSpeed * verticalScalingTime); //second variable is direction, last is control amount to send
	}
}

void moveToHorizontalPosition(){
	float timeToSendSpeed;
    timeToSendSpeed = fabs(lastZ - desiredZ);
    ROS_INFO("desiredZ is %f, lastZ is %f", desiredZ, lastZ);
    ROS_INFO("trying to move to Horizontal Position");
    ROS_INFO("timeToSendSpeed is %f", timeToSendSpeed);
    if(timeToSendSpeed < 0.015){
        horizontalCount++;
    	if (horizontalCount > 10 ){
            horizontalCount = 0;
            moveToHorizontal = 0;
            ROS_INFO("move into Horizontal success");
        }
    }
    else {
        if(lastSeenMarker == 0){
            ROS_INFO("cannot see marker, moving forward");
            sendVelToRobot(1, 0, 0, 0.5);
        }
        else {
    	ROS_INFO("Time sent is %f", timeToSendSpeed * horizontalScalingTime);
        sendVelToRobot((lastZ - desiredZ)/timeToSendSpeed * horizontalSpeedScale, 0 , 0, timeToSendSpeed * horizontalScalingTime); 
        }
	}
    
}

void moveToAngularPosition(){
	ROS_INFO("entering angular control");
	float scalingFactor = 5.5;
	float timeToSendSpeed = fabs(desiredYaw - lastYaw);
    if(timeToSendSpeed < 0.005){
    	moveToAngular = 0;
    	angularPositionReached = 1;
    }
    else {
    	sendVelToRobot(0, 0 , (desiredYaw - lastYaw)/timeToSendSpeed, timeToSendSpeed * scalingFactor); //second variable is direction, last is control amount to send
	}
}



void sendVelToRobot(float x_speed, float y_speed, float angle, float timeToWriteSpeed){
	geometry_msgs::Twist wlr_cmd;
	wlr_cmd.linear.x         = x_speed * speedFactor;
    wlr_cmd.linear.y        = y_speed * speedFactor;
    wlr_cmd.angular.z = angle * speedFactor;
    ROS_INFO("x speed is %f, y speed is %f, angular speed is %f",wlr_cmd.linear.x, wlr_cmd.linear.y, wlr_cmd.angular.z );
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
	float timeToWriteSpeed = lastZ * sleepFactor * calibratedParam/(lastZ);
	sendVelToRobot(1, 0, 0, timeToWriteSpeed);
}

int main(int argc, char** argv){
	ros::init(argc, argv, "Taobot_Info");
    ros::NodeHandle n;

    n.getParam("sleepFactor", sleepFactor);
    n.getParam("speedFactor", speedFactor);
    n.getParam("calibratedParam", calibratedParam);
    n.getParam("verticalScalingTime", verticalScalingTime);
    n.getParam("verticalSpeedScale", verticalSpeedScale);
    n.getParam("horizontalScalingTime", horizontalScalingTime);
    n.getParam("horizontalSpeedScale", horizontalSpeedScale);

    ROS_INFO("verticalScalingTime: %f", verticalScalingTime);
    ROS_INFO("speedFactor: %f", speedFactor);

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
    ros::Rate r(1);
    while (   ros::ok()){
    	if (followPath == 1 && moveToVertical == 1){
    		//moveToTrolley(); 
    		//moveToVertical = 0;//testMoveToTrolley();
    		moveToVerticalPosition();
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
    ros::Duration(1).sleep();
    }//for ros::ok();
}