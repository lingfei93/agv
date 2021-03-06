#include <std_msgs/Int32.h>
#include <math.h>
#include <geometry_msgs/Twist.h>
#include <actionlib_msgs/GoalID.h>
#include <ar_track_alvar_msgs/AlvarMarkers.h>
#include <ar_track_alvar_msgs/AlvarMarker.h>
#include <tf/transform_datatypes.h> //for yaw;
#include <tf/transform_listener.h> //for transform_listener



ros::Publisher move_base_clear_goal;
ros::Subscriber ar_tracker_sub;
ros::Publisher move_base_path_pub;
ros::Subscriber move_to_trolley_sub;
ros::Publisher actuator_pub;
ros::Publisher stop_listener_pub;
std_msgs::Int32 actuator_msg;
std_msgs::Int32 stop_msg;

float lastZ, lastX, lastYaw, lastTime; //this is the z orientation which the ar_pose_tracker should take over the steering of robot
float orientationOfQR;
float previousZ, previousX, previousYaw;
float sleepFactor, speedFactor, calibratedParam,verticalScalingTime,verticalSpeedScale, horizontalScalingTime, horizontalSpeedScale;
int followPath, moveToAngular, moveToVertical, moveToHorizontal, verticalPositionReached, count, inFinalControl = 0;
int finalMoveToHorizontal, finalMoveToVertical, reachedGoal; 
int verticalCount, horizontalCount, angularCount, lastDirection;
float distanceToClearGoal = 0.900;
float lastSeenVertical;
void moveToAngularPosition();
void moveToVerticalPosition();
void moveToHorizontalPosition(); 
void finalMoveToHorizontalPosition();
void updateValues(float z, float x);

//void updateValues(float z, float x, float yaw);
void sendVelToRobot(float x_speed, float y_speed, float angle, float timeToWriteSpeed);
float desiredZ = 0.756;
float desiredX = 0.215;
float desiredYaw = -0.09;
float finalDesiredZ = 0.200;
float finalDesiredX = 0.09;
int lastSeenMarker = 0;
float yawStore[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
int altFlag;
int stopFlag = 0;

ros::Publisher stop_pub;

//z is 0.637
//x is 0.196

void updateValues(float z, float x){

    lastZ = z;
    lastX = x;
    if (z < 1.4 && stopFlag == 0){
        stop_msg.data = 0;
        stop_listener_pub.publish(stop_msg);
        stopFlag = 1;
    }
}

void avgYaw(){

if (count < 5){
        yawStore[count] = lastYaw;
    }
    if (count == 4){
        ROS_INFO("checking this");
        float avgYaw, sum = 0.0;
        float diffYaw[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
        for (int i = 0; i < 5; i++){
             sum += yawStore[i];
        }
        avgYaw = sum / 5.0; 
        for (int i = 0; i < 5; i++){
          diffYaw[i] = fabs(yawStore[i]-avgYaw);
        }
        float diff = 100.0;
        int index;
        for (int i = 0; i < 5; i++){
    
          if (diffYaw[i] < diff){
            diff = diffYaw[i];
            index = i;
          }
        }
        lastYaw = yawStore[index];
       
        //ROS_INFO("awg yaw is :%f, index is %d", avgYaw, index);
        //ROS_INFO("yawstore's lastYaw is %f",lastYaw);
    }

}


void arTrackerCallBack(const ar_track_alvar_msgs::AlvarMarkers::ConstPtr &ar_tracker_data){
    ar_track_alvar_msgs::AlvarMarker currentMarker;
    float z, w, angle;
    if (ar_tracker_data->markers.size() == 1 && inFinalControl == 1){
        currentMarker = ar_tracker_data->markers[0];
        updateValues(currentMarker.pose.pose.position.z, currentMarker.pose.pose.position.x);
        z = currentMarker.pose.pose.orientation.z;
        w = currentMarker.pose.pose.orientation.w;
        angle   = (2*acos(w));
        lastYaw = z/sin(angle/2);
        avgYaw();
        count++;
        lastSeenMarker = 1;

    }

    if (ar_tracker_data->markers.size() == 1 && ((ar_tracker_data->markers[0].id % 2) == 0) ){
        currentMarker = ar_tracker_data->markers[0];
        updateValues(currentMarker.pose.pose.position.z, currentMarker.pose.pose.position.x);
        z = currentMarker.pose.pose.orientation.z;
        w = currentMarker.pose.pose.orientation.w;
        angle   = (2*acos(w));
        lastYaw = z/sin(angle/2);
        avgYaw();//calculate avg to throw away misnomers
        ROS_INFO(" z is %f, w is %f",z,w);
        count++;
        lastSeenMarker = 1;
    }

    if (ar_tracker_data->markers.size() == 2){

        if((ar_tracker_data->markers[0].id % 2) == 0){
            currentMarker = ar_tracker_data->markers[0];
        }
        else {
            currentMarker = ar_tracker_data->markers[1];
        }

        updateValues(currentMarker.pose.pose.position.z, currentMarker.pose.pose.position.x);
        z = currentMarker.pose.pose.orientation.z;
        w = currentMarker.pose.pose.orientation.w;
        angle = (2*acos(w));
        lastYaw = z/sin(angle/2);
        avgYaw();
        count++;
        lastSeenMarker = 1;
    }

    if(ar_tracker_data->markers.size() == 0){
        ROS_INFO("CANNOT SEE MARKER");
        lastSeenMarker = 0;
        count++;
    }
    


}
void arMarkerMoveCallBack(const std_msgs::Int32::ConstPtr &msg){

    ROS_INFO("recieved info for ar_marker_callback, it is, %d", msg->data);
    if (msg->data == 1){
        followPath = 1;
        moveToAngular = 1;
    }
    if (msg->data == 0){
        followPath = 0;
        
        stop_msg.data = 0;
        stop_listener_pub.publish(stop_msg);

        actuator_msg.data = 0;
        actuator_pub.publish(actuator_msg);

        //lower actuator
        //cleargoal
    }
}
void moveToVerticalPosition(){
    
    float timeToSendSpeed;
    timeToSendSpeed = fabs(desiredX - lastX);
    ROS_INFO("desiredX is %f, lastX is %f", desiredX, lastX);
    ROS_INFO("trying to move to Vertical Position");
    ROS_INFO("timeToSendSpeed is %f", timeToSendSpeed);
    
    if(timeToSendSpeed < 0.05){
        verticalCount++;
        ROS_INFO("verticalCount is %d", verticalCount);
        if (verticalCount > 3 ){
            verticalCount = 0;
            moveToVertical = 0;
            verticalPositionReached = 1;
            ROS_INFO("move into Vertical success");
        }
        //moveToHorizontal = 1;
    }
    else {
        if(lastSeenMarker == 0){
            ROS_INFO("cannot see marker, moving right");
            sendVelToRobot(0, 1, 0, 0.5);
        }
        else {

        ROS_INFO("Time sent is %f", timeToSendSpeed * verticalScalingTime);
        sendVelToRobot(0, (desiredX - lastX)/timeToSendSpeed * verticalSpeedScale, 0, timeToSendSpeed * verticalScalingTime); //second variable is direction, last is control amount to send
        }
    }
}

void moveToHorizontalPosition(){
    float timeToSendSpeed;
    timeToSendSpeed = fabs(lastZ - desiredZ);
    ROS_INFO("desiredZ is %f, lastZ is %f", desiredZ, lastZ);
    ROS_INFO("trying to move to Horizontal Position");
    ROS_INFO("timeToSendSpeed is %f", timeToSendSpeed);
    if(timeToSendSpeed < 0.05){
        horizontalCount++;
        if (horizontalCount > 3 ){
            horizontalCount = 0;
            moveToHorizontal = 0;
            moveToVertical = 1;
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


void finalMoveToHorizontalPosition(){
    
    float timeToSendSpeed;
    timeToSendSpeed = fabs(lastZ - finalDesiredZ);
    ROS_INFO("desiredZ is %f, lastZ is %f", finalDesiredZ, lastZ);
    ROS_INFO("trying to move to Horizontal Position");
    ROS_INFO("timeToSendSpeed is %f", timeToSendSpeed);
    if(timeToSendSpeed < 0.03){
        horizontalCount++;
        if (horizontalCount > 3 ){
            horizontalCount = 0;
            finalMoveToHorizontal = 0;
            //finalMoveToVertical = 1;
            if (finalMoveToVertical == 0){
                reachedGoal = 1;
            }
            ROS_INFO("move into final Horizontal success");
        }
    }
    else {
        if(lastSeenMarker == 0){
            ROS_INFO("cannot see marker, moving backwards");
            sendVelToRobot(-0.5, 0, 0, 0.5);
            altFlag = 0;
            finalMoveToVertical = 1;
        }
        else {
            ROS_INFO("Time sent is %f", timeToSendSpeed * horizontalScalingTime);
            ROS_INFO("send to robot these values first value %f, second value %f ",((lastZ - finalDesiredZ)/timeToSendSpeed * horizontalSpeedScale * 0.1), timeToSendSpeed * horizontalScalingTime );
            sendVelToRobot((lastZ - finalDesiredZ)/timeToSendSpeed * horizontalSpeedScale, 0 , 0, timeToSendSpeed * horizontalScalingTime * 0.75); 
            //altFlag = 0;
        }
    }
    
}


void finalMoveToVerticalPosition(){
    
    float timeToSendSpeed;
    timeToSendSpeed = fabs(finalDesiredX - lastX);
    ROS_INFO("desiredX is %f, lastX is %f", finalDesiredX, lastX);
    ROS_INFO("trying to move to Vertical Position");
    ROS_INFO("timeToSendSpeed is %f", timeToSendSpeed);
    
    if(timeToSendSpeed < 0.03){
        verticalCount++;
        ROS_INFO("verticalCount is %d", verticalCount);
        if (verticalCount > 3 ){
            verticalCount = 0;
            finalMoveToVertical = 0;
            if (finalMoveToHorizontal == 0){
            reachedGoal = 1;
            }
            ROS_INFO("move into Vertical success");
            altFlag = 1;
        }

    }
    else {
        if(lastSeenMarker == 0){
            ROS_INFO("cannot see marker, moving rightwards");
            sendVelToRobot(0, -lastSeenVertical, 0, 0.5);
            altFlag = 1;
        }
        else {
            ROS_INFO("Time sent is %f", timeToSendSpeed * verticalScalingTime);
        lastSeenVertical = (finalDesiredX - lastX)/timeToSendSpeed;
        ROS_INFO("lastSeenVertical is %f", lastSeenVertical);
        sendVelToRobot(0, (finalDesiredX - lastX)/timeToSendSpeed * verticalSpeedScale, 0, timeToSendSpeed * verticalScalingTime);
        altFlag = 1;
        //altFlag = 1;
        } //second variable is direction, last is control amount to send
    }
}



void moveToAngularPosition(){
    ROS_INFO("entering angular control");
    float scalingFactor = 5.5/4;
    float timeToSendSpeed = fabs(desiredYaw - lastYaw);
    ROS_INFO("desiredYaw is %f, lastYaw is %f, timeToSendSpeed is %f", desiredYaw, lastYaw, timeToSendSpeed);
    if(timeToSendSpeed < 0.09){
        angularCount++;
        if (angularCount > 10){
        moveToAngular = 0;
        moveToHorizontal = 1;
        }
    }
    else {

        if(lastSeenMarker == 0){
            ROS_INFO("cannot see marker");
            sendVelToRobot(0, lastDirection , 0, 0.5);
        }
        else {
        sendVelToRobot(0, 0 , (desiredYaw - lastYaw)/timeToSendSpeed * 0.5, timeToSendSpeed * scalingFactor); //second variable is direction, last is control amount to send
        lastDirection = (desiredYaw - lastYaw)/timeToSendSpeed;
        lastTime = timeToSendSpeed * scalingFactor;
        ROS_INFO("last time is %f", lastTime);
        }
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
    verticalPositionReached = 0;
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
    move_base_clear_goal =  n.advertise<actionlib_msgs::GoalID>("/move_base/cancel", 10);  
    move_base_path_pub = n.advertise<geometry_msgs::Twist>("cmd_vel_path", 100);
    ar_tracker_sub = n.subscribe<ar_track_alvar_msgs::AlvarMarkers>("/ar_pose_marker", 1, arTrackerCallBack);
    move_to_trolley_sub = n.subscribe<std_msgs::Int32>("/tow_cmd", 1, arMarkerMoveCallBack);

    actuator_pub = n.advertise<std_msgs::Int32>("/actuator", 1);
    
    stop_listener_pub  = n.advertise<std_msgs::Int32>("stop_cmd", 10);

       
    //this is for the pose of the ar_tag for control purposes
    tf::TransformListener listener;
    geometry_msgs::PoseStamped robot_pose;
    tf::StampedTransform poseRobot;
    ros::Rate r(1);
    while (ros::ok()){
        ROS_INFO("count is %d", count);
        //inFinalControl = 1; //UNCOMMENT OUT LATER;
        //ROS_INFO("last yaw is %f", lastYaw);
        if (count > 5){
            count = 0;
        if (followPath == 1 && moveToAngular == 1){
            //moveToAngularPosition(); do not uncomment
            moveToAngular = 0;
            moveToHorizontal = 1;
           // ROS_INFO("stuck in loop 1");
            }
        else if (followPath == 1 && moveToHorizontal ==1){
            // moveToHorizontal = 0;
            // moveToVertical = 1;
            ROS_INFO("stuck in loop 2");
            moveToHorizontalPosition();//test, UNCOMMENT LATER
        }
        else if (followPath == 1 && moveToVertical == 1){
            // moveToVertical = 0;
            // verticalPositionReached =1;
            // ROS_INFO("stuck in loop 3");
            moveToVerticalPosition(); //ttest, UNCOMMENT LATER
        }
        else if (followPath == 1 && verticalPositionReached == 1){
            moveToTrolley();
            ros::Duration(10).sleep(); //UNCOMMENT THESE TWO LINES LAATER!
            inFinalControl = 1;
            finalMoveToHorizontal = 1;
            finalMoveToVertical = 1;
            altFlag = 1;
            //followPath = 0; //COMMENT THIS OUT LATER
            //ROS_INFO("stuck in loop 4");
        }
        //checkQRcodeInside, final move();
        else if (inFinalControl == 1 && finalMoveToHorizontal == 1 && altFlag == 1){
            //ROS_INFO("stuck in loop 5");
            finalMoveToHorizontalPosition();
        }
        //checkQRcodeinside, final vertical move
        else if (inFinalControl == 1 && finalMoveToVertical == 1){
            finalMoveToVerticalPosition();
        }

        else if (reachedGoal){

           ROS_INFO("Have reached the end");
           actuator_msg.data = 1;
           actuator_pub.publish(actuator_msg);

        }

       
    }
    ros::Duration(0.5).sleep();
    ros::spinOnce();
    
    }//for ros::ok();
}
