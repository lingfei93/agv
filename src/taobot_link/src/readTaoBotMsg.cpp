#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <math.h>
#include "serial/serial.h"
#include <taobot_link/Taobot.h>
#include <taobot_link/Odom.h>
#include <Eigen/Dense>
#include <cmath>
using Eigen::MatrixXd;

void taoBotOdomCallback(const taobot_link::Taobot& msg);
int checkIfUpdate(int motorA_encoder, int motorB_encoder, int motorC_encoder);
ros::Publisher odom_pub;
ros::Subscriber odom_sub;
float x_pos;
float y_pos;
float theta;

using namespace std;

int checkIfUpdate(int motorA_encoder, int motorB_encoder, int motorC_encoder);
{
    return (motorA_encoder == 0 && motorB_encoder == 0 && motorC_encoder == 0) ? 0 : 1;
}
void taoBotOdomCallback(const taobot_link::Taobot& msg)
{
    taobot_link::Odom odomMsg;
    odomMsg.x_pos = x_pos;
    odomMsg.y_pos = y_pos;
    odomMsg.theta = theta;
  ROS_INFO("I heard: [%d %d %d %d %d %d %d]", msg.motorA_encoder, msg.motorA_dir, 
  	msg.motorB_encoder, msg.motorB_dir, msg.motorC_encoder, 
  	msg.motorC_dir, msg.voltage);

    //ONLY UPDATE IF THERE IS ACTUALLY SOMETHING TO UPDATE
    if(checkIfUpdate(msg.motorA_encoder, msg.motorB_encoder, msg.motorC_encoder)){

	double radius, lengthToCenter, paramA, paramB;
	double x_pos, y_pos, theta;
	double motorA_speed, motorB_speed, motorC_speed;
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

    //TODO:::::
    // input(0,0) = verticalPress;
    // input(1,0) = horizontalPress;
    // input(2,0) = angle;


    //ouput = m * input;

    x_pos = output(0,0);
    y_pos = output(1,0);
    theta = output(2,0);

    odom_pub.publish(odomMsg);


    }

}

int main(int argc, char **argv){
	ros::init(argc, argv, "Taobot_reciever");
	ros::NodeHandle n;
    x_pos = 0;
    y_pos = 0;
    theta = 0;

	odom_pub = n.advertise<taobot_link::Odom>("taobot_odom", 1000);
	odom_sub = n.subscribe("taobot_listener", 1000, taoBotOdomCallback);
	

	ros::spin();

    //test;


	return 0;



}
