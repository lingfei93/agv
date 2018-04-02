
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>
#include <sensor_msgs/Imu.h>
#include <iostream>
#include <math.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include "serial/serial.h"
#include <tf/transform_datatypes.h>
#include <taobot_link/Taobot.h>
#include <Eigen/Dense>
#include <nav_msgs/Path.h>
#include <tf/transform_listener.h>


#include <cmath>
using Eigen::MatrixXd;
using namespace std;


#define PI           3.14159265358979323846
#define RTD          180.0/PI       //Radian to Degree
#define DTR          PI/180.0       //Degree to Radian
#define TS 0.1                      //unit:s

// for SERIAL communication
#define TIMEOUT 1000
#define port "/dev/ttyUSB0"
#define baud 115200


ros::Publisher move_base_path_pub;
ros::Subscriber move_base_path_sub;
ros::Subscriber imu_pose_sub;
ros::Subscriber amcl_pose_sub;

double convertToEuclid(float x1, float y1, float x2, float y2);
void checkPath(float x1, float y1, float x2, float y2);
void sendVelCommand(float x_start, float y_start, float x_end, float y_end);
void turnRobot(float initial, float end);
uint8_t* changeToOmniSpeed(double verticalPress, double horizontalPress, double angle);
int directionToRotate(float initial, float end);
float amountToTurn(float difference);
int count_average = 0;
double total_difference = 0;
int wasInPath = 0;
int pathAvailable;
int previousLength;
float lastY = 0;
float lastX = 0;
float lastKnownYaw = 0;
float yawToTurn;
double plan[4][2000];
double tsegc[2000];
tf::TransformListener listener;
geometry_msgs::Twist wlr_cmd;
geometry_msgs::PoseStamped robot_pose;
tf::StampedTransform poseRobot;



// char reply[9];

double convertToEuclid(double x1, double y1, double x2, double y2){
    ROS_INFO("x1 is %f, y1 is %f, x2 is %f, y2 is %f",x1,y1,x2,y2);
    return sqrt(pow((x1 - x2),2) + pow((y1 - y2),2));
}

void checkPath(float x1, float y1, float x2, float y2, int len){
  if (abs(y2 - y1) < 0.5  && abs(x2 - x1) < 0.5){
   wasInPath = 0;
 }
 if ((len -1) != previousLength){
    wasInPath = 0;
	}
}

int directionToRotate(float initial, float end){

  float otherRange = end - 3.14159;

  if (otherRange > 0) {
     if(end > initial  && initial > otherRange) return 1;
     else  return -1;

   }

  else {
   otherRange += 6.28;
     if(end < initial && initial < otherRange) return 1;
     else return -1;
   

   }
}

float amountToTurn(float difference){
    if (abs(difference) < 3.14) return abs(difference);
    else return (6.28 - abs(difference));


}

void turnRobot(float initial, float end){
    ROS_INFO("initial is %f and end is %f", initial, end);

    double timeToSleep;
    double difference = 2 * 3.14; 
    difference = end - initial;


     


    timeToSleep = amountToTurn(difference);
    wlr_cmd.angular.z = directionToRotate(initial, end);
    move_base_path_pub.publish(wlr_cmd);
    ros::Duration(timeToSleep * 1.07).sleep();
    wlr_cmd.angular.z = 0;
   
    move_base_path_pub.publish(wlr_cmd);
    ros::Duration(10).sleep(); //sleep for five second to read the lastKnownYaw
   // difference = abs(lastKnownYaw - end);
    initial = lastKnownYaw;
    difference = end - initial;
    ROS_INFO("last known yaw is %f", lastKnownYaw);
    ROS_INFO("difference is %f", difference);

    
 
}

void getPoseCallBack(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& pose_data){
    lastKnownYaw = tf::getYaw(pose_data->pose.pose.orientation) + 3.14;
    ROS_INFO("last known yaw updated, it is now %f", lastKnownYaw);

}

void getImuPoseCallBack(const sensor_msgs::Imu::ConstPtr& imu_pose_data){
    lastKnownYaw = tf::getYaw(imu_pose_data->orientation);
    ROS_INFO("last known yaw updated, it is now %f", lastKnownYaw);

}

void moveRobotAlongPath(){

    for (i=0;i<len+50;i++)
    {
      //  ROS_INFO("in loop %d", i);
        current_time = ros::Time::now();
        time_elapsed = current_time - start_time;





        while(time_elapsed.toSec() < tsegc[i]){

       // ROS_INFO("sending a vel command");
      //  ROS_INFO("time elapsed is %f, tsegc[i] is %f, tsegc[i+1] is %f", time_elapsed.toSec(), tsegc[i], tsegc[i+1]);

        sendVelCommand(plan[0][i],plan[1][i],plan[0][i+1],plan[1][i+1]);
        current_time = ros::Time::now();
        time_elapsed = current_time - start_time;

        }



    }

}

void movePathCallBack(const nav_msgs::Path::ConstPtr &path_data){
   plan[4][2000] = {{0}};
   tsegc[2000] = {0};
   len = path_data->poses.size();

   ROS_INFO("ENTERED CALLBACK WITH SIZE = %d", len);
   int i;
   int len;
   if (len == previousLength + 1){
       wasInPath = 1;
       yawToTurn = tf::getYaw(path_data->poses[len-1].pose.orientation) + 3.14;
   }
   if (len > 0 && wasInPath == 0){



           distanceToGoal = 0;



               printf("START LOADING PATH, PLAN_SIZE=%d\n", len);
               for (i=0;i<len;i++)
               {
                   plan[0][i]=path_data->poses[i].pose.position.x;                 //x
                   plan[1][i]=path_data->poses[i].pose.position.y;                 //y
                   plan[2][i]=0;
                                                  //z
                   plan[3][i]=tf::getYaw(path_data->poses[i].pose.orientation);   //angle(yaw)

                   if(i > 0){
                   distanceToGoal = distanceToGoal + convertToEuclid(plan[0][i-1],plan[1][i-1], plan[0][i],plan[1][i]);}
                   }

               for (i=len;i<len+100;i++)
               {
                   plan[0][i]=path_data->poses[len-1].pose.position.x;                 //x
                   plan[1][i]=path_data->poses[len-1].pose.position.y;                 //y
                   plan[2][i]=0;                                                   //z
                   plan[3][i]=tf::getYaw(path_data->poses[len-1].pose.orientation);


               }
               ROS_INFO("distanceToGoal is %f", distanceToGoal);


               if (len>=2)
               {
                   timeForPath = distanceToGoal/idealSpeed;



                   eachTimeSlot = timeForPath / len;

                 //  ROS_INFO("Each time slot is %f, time for totalPath is %f,", eachTimeSlot, timeForPath);





                   tsegc[0]=0.0;
                   for (i=1; i < len; i++){
                       tsegc[i] = eachTimeSlot * i;
                   // ROS_INFO("tsegc is %f, %f",tsegc[i], tsegc[i+1]);
                   }

                   for (i= len; i < len + 100; i++){
                       tsegc[i] = timeForPath;
                   }



                  }




        pathAvailable = 1;
        previousLength = len;

   }

   else {

       ROS_INFO("size of path is %d", len);
   }

}

//void movePathCallBack(const nav_msgs::Path::ConstPtr& path_data)
//{
//    int i;
//    int len;
//    int idx, flag, path_plan;
//    //set the idealSpeed as a rando.
//    double idealSpeed = 0.21;
//    double eachTimeSlot;

//    len = path_data->poses.size();
  
//    double plan[4][2000] = {{0}};

//    //double plan[4][len+100] = {{0}};
//    double tsegc[2000] = {0};
//    //double tsegc[len+100] = {0};
  
   
//    double dis, dis2 = 0;
//    double distanceToGoal;
//    double timeForPath;
//    double dsegc, dseg;
//    int finishPath = 0;


//    ROS_INFO("ENTERED CALLBACK WITH SIZE = %d", len);

//    // for (i = 0; i < len; i++){
//    //      plan[0][i]=path_data->poses[i].pose.position.x;                 //x
//    //      plan[1][i]=path_data->poses[i].pose.position.y;                 //y
//    //      plan[2][i]=0;
//    //      //plan[3][i]=Quat_to_Yaw(path_data->poses[i].pose.orientation);
//    // }

//    while (finishPath == 0){
//	if (wasInPath == 1 && len > 0){
           
//           ROS_INFO("send to turnRobot with values %f, %f",tf::getYaw(path_data->poses[0].pose.orientation), tf::getYaw(path_data->poses[len-1].pose.orientation));
//           turnRobot(tf::getYaw(path_data->poses[0].pose.orientation) + 3.14, tf::getYaw(path_data->poses[len-1].pose.orientation) + 3.14); //move somewhere
//	   ROS_INFO("last quat is %f, %f", tf::getYaw(path_data->poses[len-1].pose.orientation), path_data->poses[len-1].pose.orientation.w);
           
//	   checkPath(lastX, lastY, path_data->poses[0].pose.position.x, path_data->poses[0].pose.position.y, len);
//	}
//        if (len>0 && wasInPath == 0){
//           turnRobot(lastKnownYaw, 3.14);


//        {
//	    distanceToGoal = 0;

//            //distanceToGoal = convertToEuclid(path_data->poses[0].pose.position.x, path_data->poses[0].pose.position.y ,    path_data->poses[len-2].pose.position.x, path_data->poses[len-2].pose.position.y);
//	   ROS_INFO("distance to goal is %f", distanceToGoal);
//            //dis2=DIS_XY(rc.x_c, rc.y_c, path_data->poses[len-1].pose.position.x, path_data->poses[len-1].pose.position.y); //last path point
//            if (distanceToGoal >= 0 )
//                path_plan = 1 ;
//            else
//                path_plan = 0 ;
//        }

//        if ( (len>0) && (path_plan==1) )
//        {
//	    previousLength = len;
//            printf("START LOADING PATH, PLAN_SIZE=%d\n", len);
//            for (i=0;i<len;i++)
//            {
//                plan[0][i]=path_data->poses[i].pose.position.x;                 //x
//                plan[1][i]=path_data->poses[i].pose.position.y;                 //y
//                plan[2][i]=0;
//                   		               //z
//                plan[3][i]=tf::getYaw(path_data->poses[i].pose.orientation);   //angle(yaw)
//                //printf("NUM=%d x=%+3.3f y=%+3.3f z=%+3.3f yaw=%+3.3f\n", i, plan[0][i],  q[1][i], plan[2][i], plan[3][i]);
//                ROS_INFO("this is w, %f", path_data->poses[i].pose.orientation.w);
//		ROS_INFO("this is yaw, %f", plan[3][i]);
//	    if(i > 0){
//            distanceToGoal = distanceToGoal + convertToEuclid(plan[0][i-1],plan[1][i-1], plan[0][i],plan[1][i]);}
//            }
//            for (i=len;i<len+100;i++)
//            {
//                plan[0][i]=path_data->poses[len-1].pose.position.x;                 //x
//                plan[1][i]=path_data->poses[len-1].pose.position.y;                 //y
//                plan[2][i]=0;                                                   //z
//               plan[3][i]=tf::getYaw(path_data->poses[len-1].pose.orientation);

//		//ROS_INFO("this is yaw, %f", plan[3][i]); //angle(yaw)
//                //printf("NUM=%d x=%+3.3f y=%+3.3f z=%+3.3f yaw=%+3.3f\n", i, plan[0][i], plan[1][i], plan[2][i], plan[3][i]);
//            }
//	ROS_INFO("distanceToGoal is %f", distanceToGoal);
//        }


//            //making angle by path
//            if (len>=2)
//            {
//                timeForPath = distanceToGoal/idealSpeed;



//                eachTimeSlot = timeForPath / len;

//              //  ROS_INFO("Each time slot is %f, time for totalPath is %f,", eachTimeSlot, timeForPath);

                

               

//                tsegc[0]=0.0;
//                for (i=1; i < len; i++){
//                    tsegc[i] = eachTimeSlot * i;
//		// ROS_INFO("tsegc is %f, %f",tsegc[i], tsegc[i+1]);
//                }

//                for (i= len; i < len + 100; i++){
//                    tsegc[i] = timeForPath;
//                }
                

//                dsegc=0.0;
//                ros::Time current_time, start_time;
//                ros::Duration time_elapsed;
                
//                start_time = ros::Time::now();
//                current_time = ros::Time::now();
//                time_elapsed = current_time - start_time;
//                ROS_INFO("send to turnRobot with values %f, %f", plan[3][0], plan[3][len-1]);
//                //turnRobot(plan[3][0], plan[3][len-1]);
//                for (i=0;i<len+50;i++)
//                {
//                  //  ROS_INFO("in loop %d", i);
//                    current_time = ros::Time::now();
//                    time_elapsed = current_time - start_time;
//                  //  ROS_INFO("time elapsed is %f, tsegc[i] is %f, tsegc[i+1] is %f, number 2 is %f", time_elapsed.toSec(), tsegc[i], tsegc[i+1], tsegc[i+2]);
//                    dseg=convertToEuclid(plan[0][i],plan[1][i],plan[0][i-1],plan[1][i-1]);
//                    dsegc=dsegc+dseg;

                    


//                    while(time_elapsed.toSec() < tsegc[i]){

//                   // ROS_INFO("sending a vel command");
//                  //  ROS_INFO("time elapsed is %f, tsegc[i] is %f, tsegc[i+1] is %f", time_elapsed.toSec(), tsegc[i], tsegc[i+1]);

//                    sendVelCommand(plan[0][i],plan[1][i],plan[0][i+1],plan[1][i+1]);
//                    current_time = ros::Time::now();
//                    time_elapsed = current_time - start_time;

//                    }

                  

//                }
//                //send a 0 command to stop the bot;ZERO
//                sendVelCommand(0,0,0,0);
//                //DO ANGLE PLANNING skok LATER;
//                //sendFinalAngleCommand(path_data->poses[len-1].pose.orientation);

//            //
//            }
//        wasInPath = 1;
//        lastX = plan[0][len];
//	lastY = plan[1][len];
//        }
//            else printf("PLAN_SIZE ZERO\n");
//            finishPath = 1;

//        }
//    }



void sendVelCommand(float x_start, float y_start, float x_end, float y_end){
    geometry_msgs::Twist wlr_cmd;
    uint8_t reply[30];

    //NOT SURE WHY I NEED TO FLIP THIS
    wlr_cmd.linear.x         = (x_end - x_start) * 0.71;
    wlr_cmd.linear.y        = (y_end - y_start) * 0.71;
    wlr_cmd.angular.z = 0;

    move_base_path_pub.publish(wlr_cmd);
    //double directionToRotate = 0; 

}


void getPose(){
    listener.lookupTransform("/map", "/base_link", ros::Time(0), poseRobot);
    robot_pose.pose.orientation.x = poseRobot.getRotation().getX();
    robot_pose.pose.orientation.y = poseRobot.getRotation().getY();
    robot_pose.pose.orientation.z = poseRobot.getRotation().getZ();
    robot_pose.pose.orientation.w = poseRobot.getRotation().getW();
    lastKnownYaw = tf::getYaw(robot_pose.pose.orientation) + 3.14;
}






int main(int argc, char** argv)
{
    float previousYaw;
    ros::init(argc, argv, "Taobot_Info");
    ros::NodeHandle n;
    //ros::AsyncSpinner spinner(2);
   //spinner.start();




    move_base_path_pub = n.advertise<geometry_msgs::Twist>("cmd_vel_path", 100);
    
    move_base_path_sub  = n.subscribe<nav_msgs::Path>("/move_base_node/NavfnROS/plan", 5, movePathCallBack);
 	
   //imu_pose_sub  = n.subscribe<sensor_msgs::Imu>("/imu/data",1000, getImuPoseCallBack);
  // amcl_pose_sub = n.subscribe<geometry_msgs::PoseWithCovarianceStamped>("/amcl_pose",5, getPoseCallBack);
  
    ROS_INFO(("enter into here"));
    ros::Rate loop_rate(5);

    lastKnownYaw = 0;
    while (ros::ok()){
        try{

            getPose();


            if (previousYaw != lastKnownYaw){
                ROS_INFO("last known yaw updated, it is %f ", lastKnownYaw);
                previousYaw = lastKnownYaw;
            }

            if (pathAvailable == 1){
                getPose();
                difference = 3.14 - lastKnownYaw;
                while (amountToTurn(difference) > 0.25){
                turnRobot(lastKnownYaw, 3.14);
                getPose();
                difference = 3.14 - lastKnownYaw;
                }

                moveRobotAlongPath();
                pathAvailable = 0;
            }
            if (wasInPath == 1){
                getPose();

                while (amountToTurn(difference) > 0.25){
                turnRobot(lastKnownYaw, yawToTurn);
                getPose();
                difference = yawToTurn - lastKnownYaw;
                }
                wasInPath = 0;
            }

        }
        catch (tf::TransformException &ex) {
            ROS_ERROR("%s",ex.what());
            ros::Duration(1.0).sleep();
            continue;
        }
    ros::spinOnce();
   }//end while (ros::ok)
}// end main()
    

