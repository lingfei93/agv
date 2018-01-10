/*
//Title: Joystick Control AXON platform (IoT Lab.)
//Author: Chen Chun-Lin
//Data: 2015/08/15, 2017/04/06
//Update:

Joystick button:
Speed 1: "A"  (MIN Speed)
Speed 2: "B"
Speed 3: "X"
Speed 4: "Y"
Speed 5: "L1"
Speed 6: "R1"
Speed 7: "BACK"
Speed 8: "START" (MAX Speed)

*/

#include <ros/ros.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>

#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
using namespace std;

#define PI           3.14159
#define RTD          180.0/PI       //Radian to Degree
#define DTR          PI/180.0       //Degree to Radian

ros::Publisher cmd_vel_pub_;
ros::Subscriber joy_sub_;

//ROS Parameter
#define MAIN_FREQ           50.0        //Controller main frequency
#define TF_REV_DELAY_T      150         //TF of MAP_ODOM frame receive start delay units * ts

//------------------------------------------
double main_freg_=MAIN_FREQ ;
double tf_rev_delay_t_=TF_REV_DELAY_T;

double cmd_vel_v=0;
double cmd_vel_w=0;
double cmd_scale=0.05;
double old_cmd_scale=0.05;

//Publish output command
void CTRL_OUT(double V, double W)
{
    geometry_msgs::Twist cmd_vel;
    cmd_vel.linear.x=V;
    cmd_vel.angular.z=W;
    cmd_vel_pub_.publish(cmd_vel);
}

void JoySubCallback(const sensor_msgs::Joy::ConstPtr& joy_msg)
{
    ROS_INFO("testing2");
    int i;
    double joy_axes[8];
    double joy_buttons[11];
    joy_axes[0]=joy_msg->axes[0];
    joy_axes[1]=joy_msg->axes[1];

    for (i=0;i<11;i++)
        joy_buttons[i]=joy_msg->buttons[i];

    for (i=0;i<8;i++)
    {
        if (joy_buttons[i]==1)
        {
            cmd_scale=(double)(double(i+1))/8.0;
            old_cmd_scale=cmd_scale*0.796107; //Robot Max. V(m/s)
        }
    }
    if (joy_buttons[10]==1)
        cmd_scale=0.0;
    else
        cmd_scale=old_cmd_scale;

    printf("I Get Joy axes[0]=%+3.3f axes[1]=%+3.3f cmd_scale=%+3.3f\n", joy_axes[0], joy_axes[1], cmd_scale);
    cmd_vel_v=joy_axes[1]*cmd_scale*1;
    cmd_vel_w=joy_axes[0]*cmd_scale*1;
    printf("Joy V=%+3.3f W=%+3.3f\n", cmd_vel_v, cmd_vel_w);
}

int main(int argc, char** argv)
{
    int i;
    ROS_INFO("testing");
    ros::init(argc, argv, "joy_ctrl_axon_node");
    ros::NodeHandle n;

    //==================================================
    //load ROS Parameter
    n.getParam("main_freg", main_freg_) ;
    n.getParam("tf_rev_delay_t", tf_rev_delay_t_);

    //-----------------------------------------------------------------
    cmd_vel_pub_= n.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    joy_sub_=n.subscribe<sensor_msgs::Joy>("joy", 50, JoySubCallback);

    ros::Rate loop_rate(main_freg_);      //50HZ
    while(ros::ok())
    {
        CTRL_OUT(cmd_vel_v, cmd_vel_w);
        //==============================================
        ros::spinOnce();
        loop_rate.sleep();
    }   
}
