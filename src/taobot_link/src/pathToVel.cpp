
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>
#include <iostream>
#include <math.h>
#include "serial/serial.h"
#include <taobot_link/Taobot.h>
#include <Eigen/Dense>
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

int count_average = 0;
double total_difference = 0;
// char reply[9];

double convertToEuclid(float x1, float y1, float x2, float y2){
    return sqrt(pow((x1 - x2),2) + pow((y1 - y2),2));
}

void MovePathCallback(const nav_msgs::Path::ConstPtr& path_data)
{
    int i;
    int len;
    int idx, flag, path_plan;
    //set the idealSpeed as a rando.
    double idealSpeed = 0.5;
    double eachTimeSlot;

    len = path_data_>poses.size();

    double path[4][len+101] = {{0}};

    double tsegc[len] = {0};

    double dis, dis2 = 0;
    double distanceToGoal;

    // for (i = 0; i < len; i++){
    //      plan[0][i]=path_data->poses[i].pose.position.x;                 //x
    //      plan[1][i]=path_data->poses[i].pose.position.y;                 //y
    //      plan[2][i]=0;
    //      //plan[3][i]=Quat_to_Yaw(path_data->poses[i].pose.orientation);                    
    // }



        if (len>0){


        {
            distanceToGoal = convertToEuclid(path_data->poses[0].pose.position.x, path_data->poses[0].pose.position.y , 
                path_data->poses[len-1].pose.position.x, path_data->poses[len-1].pose.position.y);
            //dis2=DIS_XY(rc.x_c, rc.y_c, path_data->poses[len-1].pose.position.x, path_data->poses[len-1].pose.position.y); //last path point
            if (distanceToGoal >= 0 )
                path_plan = 1 ;
            else
                path_plan = 0 ;
        }

        if ( (len>0) && (path_plan==1) )
        {
            printf("START LOADING PATH, PLAN_SIZE=%d\n", len);
            for (i=0;i<len;i++)
            {
                plan[0][i]=path_data->poses[i].pose.position.x;                 //x
                plan[1][i]=path_data->poses[i].pose.position.y;                 //y
                plan[2][i]=0;                                                   //z
                //plan[3][i]=Quat_to_Yaw(path_data->poses[i].pose.orientation);   //angle(yaw)
                //printf("NUM=%d x=%+3.3f y=%+3.3f z=%+3.3f yaw=%+3.3f\n", i, plan[0][i],  q[1][i], plan[2][i], plan[3][i]);
            }
            for (i=len;i<len+100;i++)
            {
                plan[0][i]=path_data->poses[len-1].pose.position.x;                 //x
                plan[1][i]=path_data->poses[len-1].pose.position.y;                 //y
                plan[2][i]=0;                                                   //z
               // plan[3][i]=Quat_to_Yaw(path_data->poses[len-1].pose.orientation);   //angle(yaw)
                //printf("NUM=%d x=%+3.3f y=%+3.3f z=%+3.3f yaw=%+3.3f\n", i, plan[0][i], plan[1][i], plan[2][i], plan[3][i]);
            }

        }


            //making angle by path
            if (len>=2)
            {   
                timeForPath = distanceToGoal/idealSpeed;



                eachTimeSlot = timeForPath / len;

                ROS_INFO("Each time slot is %d, time for totalPath is %d,", eachTimeSlot, timeForPath);

                ros::Time current_time, start_time, time_elapsed;
                
                start_time = ros::Time::now();
                current_time = ros::Time::now();

                time_elapsed = current_time - start_time;

                tsegc[0]=0.0;
                for (i=1; i < len; i++){
                    tsegc[i] = eachTimeSlot * i;
                }

                dsegc=0.0;
                for (i=0;i<len;i++)
                {
                    current_time = ros::Time::now();
                    time_elapsed = current_time - start_time;

                    dseg=convertToEuclid(plan[0][i],plan[1][i],plan[0][i-1],plan[1][i-1]);
                    dsegc=dsegc+dseg;

                    

                    while(!(time_elapsed> tsegc[i] && time_elapsed < tsegc[i+1])){

                    ROS_INFO("sending a vel command");
                    sendVelCommand(plan[0][i],plan[1][i],plan[0][i+1],plan[1][i+1]);
                    current_time = ros::Time::now();
                    time_elapsed = current_time - start_time;

                    }

                  

                }
                //DO ANGLE PLANNING skok LATER;
                //sendFinalAngleCommand(path_data->poses[len-1].pose.orientation);

            //     
            }

        }
            else printf("PLAN_SIZE ZERO\n");
    }



void sendVelCommand(float x_start, float y_start, float x_end, float y_end){
    geometry_msgs::Twist wlr_cmd;
    uint8_t reply[30];

    //NOT SURE WHY I NEED TO FLIP THIS
    double v_cmd         = x_end - x_start;
    double w_cmd         = y_end - y_start;
    double directionToRotate = 0; 
    uint8_t* arrayToSend;

    arrayToSend = changeToOmniSpeed(v_cmd, w_cmd, directionToRotate);

    sendCommand(arrayToSend, 10);
}




uint8_t* changeToOmniSpeed(double verticalPress, double horizontalPress, double angle){
//THIS FIXED IT//
    uint8_t* toSend = new uint8_t[10];
    double radius, lengthToCenter, paramA, paramB;
    double motorA_speed, motorB_speed, motorC_speed, max;
    int count;

    radius = 5;
    paramA = 1/sqrt(3);
    paramB = 1/sqrt(9);
    lengthToCenter = 26.3;
    MatrixXd m(3,3);
    MatrixXd input(3,1);
    MatrixXd output(3,1);
    
    m(0,0) =  0;
  
    m(0,1) = -paramA*radius;
    m(0,2) = paramA*radius;
    m(1,0) = -2*paramB*radius;
    m(1,1) = paramB*radius;
    m(1,2) = paramB*radius; 
    m(2,0) = radius*paramB/lengthToCenter;
    m(2,1) = radius*paramB/lengthToCenter;
    m(2,2) = radius*paramB/lengthToCenter;
    input(0,0) = verticalPress;
    input(1,0) = horizontalPress;
    input(2,0) = angle;
    max = 0;
    output = m.inverse() * input;

    //find out whats the max speed so i can normalize it
    for (int i = 0; i < 2; i++){
        if (std::abs(output(i,0)) > max){
            max = std::abs(output(i,0));
        }
    }
    count = 0;

    motorA_speed = output(0,0);
    motorB_speed = output(1,0);
    motorC_speed = output(2,0);

    //figure out the direction for each of the motor
    if (motorA_speed < 0) {count = count + 4;}
    if (motorB_speed < 0) {count = count + 2;}
    if (motorC_speed < 0) {count = count + 1;}
    if (horizontalPress == 0){
    ROS_INFO("going up and down");
    //normalize the speed
    motorA_speed = std::abs(motorA_speed)/max;
    motorB_speed = std::abs(motorB_speed)/max;
    motorC_speed = std::abs(motorC_speed)/max * 1.025 ;
    }   

    else {

    ROS_INFO("going LEFT and RIGHT right RIGHT");
    motorA_speed = std::abs(motorA_speed)/max;
    motorB_speed = std::abs(motorB_speed)/max * 1.025;
    motorC_speed = std::abs(motorC_speed)/max;
    }
    //prepare the message in the taobot format
    toSend[0] = 0xff;

    toSend[1] = 0xfe;
    toSend[2] = 2;
    toSend[3] = 0;
    toSend[4] = motorA_speed * 0xf;
    toSend[5] = 0;
    toSend[6] = motorB_speed * 0xf;

    toSend[7] = 0;
    
    toSend[8] = motorC_speed * 0xf; 

    toSend[9] = count;

    return toSend;
}




void cmdVelReceived(const geometry_msgs::Twist::ConstPtr& cmd_vel){
    geometry_msgs::Twist wlr_cmd;
    uint8_t reply[30];

    //NOT SURE WHY I NEED TO FLIP THIS
    double v_cmd 	     = cmd_vel->linear.x * -1 ;
    double w_cmd 	     = cmd_vel->angular.z;
    double directionToRotate = cmd_vel->linear.y / 0.5 ; 
    uint8_t* arrayToSend;

    arrayToSend = changeToOmniSpeed(v_cmd, w_cmd, directionToRotate);

    sendCommand(arrayToSend, 10);

     
  
    
}

void moveBaseCmdVelReceived(const geometry_msgs::Twist::ConstPtr& cmd_vel){
    geometry_msgs::Twist wlr_cmd;
    uint8_t reply[30];

    //NOT SURE WHY I NEED TO FLIP THIS
    float x_vel         = cmd_vel->linear.x * -1;
    float y_vel         = cmd_vel->linear.y;
    float theta_vel     = cmd_vel->angular.z / 0.5;
    
    uint8_t* arrayToSend;

    arrayToSend = changeToOmniSpeed(x_vel, y_vel, theta_vel);

    sendCommand(arrayToSend, 10);

     
  
    
}



int main(int argc, char** argv)
{

    ros::init(argc, argv, "Taobot_Info");
    ros::NodeHandle n;


    move_base_path_pub = n.advertise<geometry_msgs::Twist>("cmd_vel_path", 1000)
    
    move_base_path_sub  = n.subscribe<nav_msgs::Path>("HVAENT_DETERMINED", 1000, movePathCallBack);
    
  

    ros::Rate loop_rate(5);
    while (ros::ok()){

    ros::spin();
    }
    
    
    }
