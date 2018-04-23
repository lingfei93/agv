#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>
#include <sensor_msgs/Imu.h>
#include <iostream>
#include <math.h>
#include <cmath>
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
void moveRobotAlongPath();
void turnRobot(float initial, float end);
void getPose();
uint8_t* changeToOmniSpeed(double verticalPress, double horizontalPress, double angle);
int directionToRotate(float initial, float end);
float amountToTurn(float difference);
int count_average = 0;
double total_difference = 0;
int wasInPath = 0;
int pathAvailable;
int executePath;
int previousLength;
float lastY = 0;
float lastX = 0;
float lastKnownYaw = 0;
float yawToTurn;
double plan[4][2000] = {{0}};
double tsegc[2000] = {0};
int len;
geometry_msgs::Twist wlr_cmd;




// char reply[9];

double convertToEuclid(double x1, double y1, double x2, double y2){
    ROS_INFO("x1 is %f, y1 is %f, x2 is %f, y2 is %f",x1,y1,x2,y2);
    return sqrt(pow((x1 - x2),2) + pow((y1 - y2),2));
}

void checkPath(float x1, float y1, float x2, float y2, int len){
  if (fabs(y2 - y1) < 0.5  && fabs(x2 - x1) < 0.5){
   wasInPath = 0;
 }
 if ((len -1) != previousLength){
    wasInPath = 0;
	}
}

int directionToRotate(float initial, float end){

  float otherRange = end - 3.14159;

  if (otherRange > 0) {
     if(end > initial  && initial > otherRange) return -1;
     else  return 1;

   }

  else {
   otherRange += 6.28;
     if(end < initial && initial < otherRange) return 1;
     else return -1;
   

   }
}

float amountToTurn(float difference){
    if (fabs(difference) < 3.14) return fabs(difference);
    else return (3.14159*2 - fabs(difference));


}

void turnRobot(float initial, float end){
    ROS_INFO("initial is %f and end is %f", initial, end);

    double timeToSleep;
    double difference = 2 * 3.14; 
    difference = end - initial;


     


    timeToSleep = amountToTurn(difference);
    wlr_cmd.angular.z = directionToRotate(initial, end);
    ROS_INFO("direction to rotate is %f", wlr_cmd.angular.z);
    move_base_path_pub.publish(wlr_cmd);
    ros::Duration(timeToSleep * 1.07).sleep();
    wlr_cmd.angular.z = 0;
   
    move_base_path_pub.publish(wlr_cmd);
    ros::Duration(10).sleep(); //sleep for five second to read the lastKnownYaw
   // difference = fabs(lastKnownYaw - end);
    initial = lastKnownYaw;
    difference = end - initial;
    ROS_INFO("last known yaw is %f", lastKnownYaw);
    ROS_INFO("difference is %f", amountToTurn(difference));

    
 
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
    int i;
    ros::Time current_time, start_time;
    ros::Duration time_elapsed;
    start_time = ros::Time::now();
    current_time = ros::Time::now();
    time_elapsed = current_time - start_time;
    for (i=0;i<previousLength+50;i++)
    {
        ROS_INFO("in loop %d", i);
        current_time = ros::Time::now();
        time_elapsed = current_time - start_time;
		ROS_INFO("tsegc is %d, %f", i, tsegc[i]);


        while(time_elapsed.toSec() < tsegc[i]){



        sendVelCommand(plan[0][i],plan[1][i],plan[0][i+1],plan[1][i+1]);
        current_time = ros::Time::now();
        time_elapsed = current_time - start_time;

        }



    }
    ROS_INFO(" i reached executePath");
    executePath = 1;

}

void movePathCallBack(const nav_msgs::Path::ConstPtr &path_data){

   len = path_data->poses.size();

   float distanceToGoal;

   float timeForPath;
   float idealSpeed = 0.21;
   float eachTimeSlot;



   ROS_INFO("ENTERED CALLBACK WITH SIZE = %d", len);
   int i;

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
                       ROS_INFO("tsegc is %f", tsegc[i]);
                   }



                  }




        pathAvailable = 1;
        previousLength = len;

   }

   else {

       ROS_INFO("size of path is %d", len);
   }

}




void sendVelCommand(float x_start, float y_start, float x_end, float y_end){
    geometry_msgs::Twist wlr_cmd;
    //uint8_t reply[30];

    //NOT SURE WHY I NEED TO FLIP THIS
    wlr_cmd.linear.x         = (x_end - x_start) * 0.65;
    wlr_cmd.linear.y        = (y_end - y_start) * 0.65;
    wlr_cmd.angular.z = 0;

    move_base_path_pub.publish(wlr_cmd);
    //double directionToRotate = 0; 

}




int main(int argc, char** argv)
{

    ros::init(argc, argv, "Taobot_Info");
    ros::NodeHandle n;
    float previousYaw, difference;
    //ros::AsyncSpinner spinner(2);
   //spinner.start();




    move_base_path_pub = n.advertise<geometry_msgs::Twist>("cmd_vel_path", 10);
    
    move_base_path_sub  = n.subscribe<nav_msgs::Path>("/move_base_node/NavfnROS/plan", 1, movePathCallBack);
 	
   
    ROS_INFO(("enter into here"));
    ros::Rate loop_rate(20);

    tf::TransformListener listener;
    geometry_msgs::PoseStamped robot_pose;
    tf::StampedTransform poseRobot;
    lastKnownYaw = 0;
    while (ros::ok()){




        try{
        listener.lookupTransform("/map", "/base_link", ros::Time(0), poseRobot);
        robot_pose.pose.orientation.x = poseRobot.getRotation().getX();
        robot_pose.pose.orientation.y = poseRobot.getRotation().getY();
        robot_pose.pose.orientation.z = poseRobot.getRotation().getZ();
        robot_pose.pose.orientation.w = poseRobot.getRotation().getW();
        lastKnownYaw = tf::getYaw(robot_pose.pose.orientation) + 3.14;

        }
        catch (tf::TransformException &ex) {
            ROS_ERROR("%s",ex.what());
            ros::Duration(1.0).sleep();
            continue;
        }

            if (previousYaw != lastKnownYaw){
                ROS_INFO("last known yaw updated, it is %f ", lastKnownYaw);
                previousYaw = lastKnownYaw;
            }

            if (pathAvailable == 1){
                ROS_INFO("sending a path data");
                try{
                listener.lookupTransform("/map", "/base_link", ros::Time(0), poseRobot);
                robot_pose.pose.orientation.x = poseRobot.getRotation().getX();
                robot_pose.pose.orientation.y = poseRobot.getRotation().getY();
                robot_pose.pose.orientation.z = poseRobot.getRotation().getZ();
                robot_pose.pose.orientation.w = poseRobot.getRotation().getW();
                lastKnownYaw = tf::getYaw(robot_pose.pose.orientation) + 3.14;
                }
                catch (tf::TransformException &ex) {
                    ROS_ERROR("%s",ex.what());
                    ros::Duration(1.0).sleep();
                    continue;
                }


                difference = 3.14 - lastKnownYaw;
                while (amountToTurn(difference) > 0.25){
                turnRobot(lastKnownYaw, 3.14);
                try{
                listener.lookupTransform("/map", "/base_link", ros::Time(0), poseRobot);
                robot_pose.pose.orientation.x = poseRobot.getRotation().getX();
                robot_pose.pose.orientation.y = poseRobot.getRotation().getY();
                robot_pose.pose.orientation.z = poseRobot.getRotation().getZ();
                robot_pose.pose.orientation.w = poseRobot.getRotation().getW();
                lastKnownYaw = tf::getYaw(robot_pose.pose.orientation) + 3.14;

                difference = 3.14 - lastKnownYaw;
                }
                catch (tf::TransformException &ex) {
                    ROS_ERROR("%s",ex.what());
                    ros::Duration(1.0).sleep();
                    continue;
                }


                }

                moveRobotAlongPath();
                pathAvailable = 0;
            }
            if (wasInPath == 1 && executePath == 1){
                ROS_INFO("reached wasinPath = 1");
                try{
                listener.lookupTransform("/map", "/base_link", ros::Time(0), poseRobot);
                robot_pose.pose.orientation.x = poseRobot.getRotation().getX();
                robot_pose.pose.orientation.y = poseRobot.getRotation().getY();
                robot_pose.pose.orientation.z = poseRobot.getRotation().getZ();
                robot_pose.pose.orientation.w = poseRobot.getRotation().getW();
                lastKnownYaw = tf::getYaw(robot_pose.pose.orientation) + 3.14;

                }
                catch (tf::TransformException &ex) {
                    ROS_ERROR("%s",ex.what());
                    ros::Duration(1.0).sleep();
                    continue;
                }
                difference = yawToTurn - lastKnownYaw;

                while (amountToTurn(difference) > 0.25){
                ROS_INFO("turn robot sent with commands %f, %f", lastKnownYaw, yawToTurn);
                turnRobot(lastKnownYaw, yawToTurn);

                try{
                listener.lookupTransform("/map", "/base_link", ros::Time(0), poseRobot);

                robot_pose.pose.orientation.x = poseRobot.getRotation().getX();
                robot_pose.pose.orientation.y = poseRobot.getRotation().getY();
                robot_pose.pose.orientation.z = poseRobot.getRotation().getZ();
                robot_pose.pose.orientation.w = poseRobot.getRotation().getW();
                lastKnownYaw = tf::getYaw(robot_pose.pose.orientation) + 3.14;

                }
                catch (tf::TransformException &ex) {
                    ROS_ERROR("%s",ex.what());
                    ros::Duration(1.0).sleep();
                    continue;
                }


                difference = yawToTurn - lastKnownYaw;
                }
                wasInPath = 0;
                executePath = 0;
            }


    ros::spinOnce();
   }//end while (ros::ok)
}// end main()
    

