#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <math.h>
#include "serial/serial.h"
#include <taobot_link/Taobot.h>
#include <taobot_link/Odom.h>
#include <vicon_xb/viconPoseMsg.h>
#include <Eigen/Dense>
#include <cmath>
#include <math.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>

using Eigen::MatrixXd;


void taoBotOdomCallback(const taobot_link::Taobot& msg);
void viconPoseCallback(const vicon_xb::viconPoseMsg& msg);
int checkIfUpdate(int motorA_encoder, int motorB_encoder, int motorC_encoder);
ros::Publisher odom_pub;
ros::Publisher odom_official_pub;
ros::Subscriber odom_sub;
ros::Subscriber vicon_sub;


#define _USE_MATH_DEFINES;
int counter;
float x_pos;
float y_pos;
float theta;
float initial_vicon_x;
float initial_vicon_y;
float initial_vicon_yaw;
float current_vicon_x;
float current_vicon_y;
float current_vicon_yaw;
ros::Time current_time;


using namespace std;

int checkIfUpdate(int motorA_encoder, int motorB_encoder, int motorC_encoder)
{
    return (motorA_encoder == 0 && motorB_encoder == 0 && motorC_encoder == 0) ? 0 : 1;
}
void taoBotOdomCallback(const taobot_link::Taobot& msg)
{
    taobot_link::Odom odomMsg;
    // odomMsg.x_pos = x_pos;
    // odomMsg.y_pos = y_pos;
    // odomMsg.theta = theta;
    float motorA_incr;
    float motorB_incr;
    float motorC_incr;
    float magical_x_factor = 2760;
    float magical_y_factor = 2700;
    float angle_factor = 2755/150;
  // ROS_INFO("I heard: [%d %d %d %d %d %d %f]", msg.motorA_encoder, msg.motorA_dir, 
  // 	msg.motorB_encoder, msg.motorB_dir, msg.motorC_encoder, 
  // 	msg.motorC_dir, msg.voltage);

    //ONLY UPDATE IF THERE IS ACTUALLY SOMETHING TO UPDATE -> checked to work
    if(checkIfUpdate(msg.motorA_encoder, msg.motorB_encoder, msg.motorC_encoder)){
    
    motorA_incr = msg.motorA_encoder * ( msg.motorA_dir - 1 );
    motorB_incr = msg.motorB_encoder * ( msg.motorB_dir - 1 );
    motorC_incr = msg.motorC_encoder * ( msg.motorC_dir - 1 );

    // x_pos = x_pos + motorA_incr;
    // y_pos = y_pos + motorB_incr;
    // theta = theta ;

	double radius, lengthToCenter, paramA, paramB;

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

    input(0,0) = motorA_incr;
    input(1,0) = motorB_incr;
    input(2,0) = motorC_incr;



    output = m * input;

    //TODO:::::
    // input(0,0) = verticalPress;
    // input(1,0) = horizontalPress;
    // input(2,0) = angle;


    //ouput = m * input;

    // x_pos = output(0,0);
    // y_pos = output(1,0);
    // theta = output(2,0);

    ROS_INFO("%f is X %f is Y %f is theta", output(0,0), output(1,0), output(2,0));

    x_pos = x_pos + output(0,0)/magical_x_factor;
    y_pos = y_pos + -1*output(1,0)/magical_y_factor;
    theta = theta + output(2,0)/angle_factor;

    float x_vel = output(0,0)/magical_x_factor;
    float y_vel = -1*output(1,0)/magical_y_factor;
    float theta_vel = output(2,0)/angle_factor;
    if (theta > (float) 2 * 3.14159) {
    	theta = theta - (float) 2 * 3.14159;
    }

    if (theta < (float) -2 * 3.14159) {
    	theta = theta + (float) 2 * 3.14159;
    }
  
    odomMsg.x_pos = x_pos;
    odomMsg.y_pos = y_pos;
    odomMsg.theta = theta; 

    //need to convert theta(yaw) to a quarternion value
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(theta);
    tf::TransformBroadcaster odom_broadcaster;

    geometry_msgs::TransformStamped odom_trans;

    current_time = ros::Time::now();

    odom_trans.header.stamp = current_time;

    
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_link";

    odom_trans.transform.translation.x = x_pos;
    odom_trans.transform.translation.y = y_pos;
    odom_trans.transform.translation.z = 0.0;
    odom_trans.transform.rotation = odom_quat;



    //send the transform
    odom_broadcaster.sendTransform(odom_trans);


    nav_msgs::Odometry odom;
    odom.header.stamp = current_time;
    odom.header.frame_id = "odom";

    odom.pose.pose.position.x = x_pos;
    odom.pose.pose.position.y = y_pos;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = odom_quat;

    //SPEED IS just distance travelled for now. not sure about time atm!
	odom.child_frame_id = "base_link";
    odom.twist.twist.linear.x = x_vel;
    odom.twist.twist.linear.y = y_vel;
    odom.twist.twist.angular.z = theta_vel;



    odom_official_pub.publish(odom);
    ROS_INFO("%f is final X %f is final Y %f is floatinal theta", x_pos, y_pos, theta);
    ROS_INFO("%f is vicon X %f is vicon Y %f is vicon theta", current_vicon_x - initial_vicon_x
    											,current_vicon_y - initial_vicon_y, 
    											current_vicon_yaw - initial_vicon_yaw);
    ROS_INFO("%f is X %f is Y %f is theta", x_pos - (current_vicon_x - initial_vicon_x)
    											,y_pos - (current_vicon_y - initial_vicon_y), 
    											theta- (current_vicon_yaw - initial_vicon_yaw));

    odom_pub.publish(odomMsg);


    }

 

}

   void viconPoseCallback(const vicon_xb::viconPoseMsg& msg){
    	// ROS_INFO("recieved vicon");
    	counter++;
    	if (counter == 1){
    	initial_vicon_x = msg.x;
    	initial_vicon_y = msg.y;
    	initial_vicon_yaw = msg.yaw;
    	}
    	current_vicon_yaw = msg.yaw;
    	current_vicon_x = msg.x;
    	current_vicon_y = msg.y;
    	// ROS_INFO("x pos is: %f y pos is: %f yaw is: %f ", vicon_x, vicon_y, vicon_yaw);
    	// ROS_INFO("x pos is: %f y pos is: %f yaw is: %f ", msg.x - vicon_x, msg.y - vicon_y, msg.yaw - vicon_yaw);
    }

int main(int argc, char **argv){
	ros::init(argc, argv, "Taobot_reciever");
	ros::NodeHandle n;
    x_pos = 0;
    y_pos = 0;
    theta = 0;

	odom_pub = n.advertise<taobot_link::Odom>("taobot_odom", 1000);
	odom_official_pub = n.advertise<nav_msgs::Odometry>("odom",50);
	odom_sub = n.subscribe("taobot_listener", 1000, taoBotOdomCallback);
	vicon_sub = n.subscribe("vicon_xb_node/viconPoseTopic", 1000, viconPoseCallback);

	//SETUP FOR ODOM

    tf::TransformBroadcaster odom_broadcaster;
    ros::Time current_time, last_time;
    current_time = ros::Time::now();
    
    last_time = ros::Time::now();
    ros::Rate r(10);

	//for tf






	

	

    //test;
    while(n.ok()){

    ros::spinOnce();               // check for incoming messages
    current_time = ros::Time::now();

    //compute odometry in a typical way given the velocities of the robot
    // double dt = (current_time - last_time).toSec();
    // double delta_x = (vx * cos(th) - vy * sin(th)) * dt;
    // double delta_y = (vx * sin(th) + vy * cos(th)) * dt;
    // double delta_th = vth * dt;

    // x += delta_x;
    // y += delta_y;
    // th += delta_th;

    //since all odometry is 6DOF we'll need a quaternion created from yaw
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(theta);

    //first, we'll publish the transform over tf
    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = current_time;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_link";

    odom_trans.transform.translation.x = x_pos;
    odom_trans.transform.translation.y = y_pos;
    odom_trans.transform.translation.z = 0.0;
    odom_trans.transform.rotation = odom_quat;

    //send the transform
    odom_broadcaster.sendTransform(odom_trans);

    //next, we'll publish the odometry message over ROS
    nav_msgs::Odometry odom;
    odom.header.stamp = current_time;
    odom.header.frame_id = "odom";

    //set the position
    odom.pose.pose.position.x = x_pos;
    odom.pose.pose.position.y = y_pos;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = odom_quat;

    //set the velocity
    odom.child_frame_id = "base_link";
    odom.twist.twist.linear.x = 0;
    odom.twist.twist.linear.y = 0;
    odom.twist.twist.angular.z = 0;

    //publish the message
    odom_official_pub.publish(odom);

    last_time = current_time;
    r.sleep();
  }


	return 0;



}
