#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

#include <std_msgs/Int32.h>

int goUp = 0;
int goDown = 0;
ros::Publisher cmd_vel_pub_;
ros::Subscriber actuator_sub;

void actuatorSubCallback(const std_msgs::Int32::ConstPtr &msg){
	ROS_INFO("recieved info for ar_marker_callback, it is, %d", msg->data);
	if (msg->data == 1){
		goUp = 1;
		goDown = 0;
		
	}
	if (msg->data == 0){
		goDown = 1;
		goUp = 0;
	}
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "actuator");
    ros::NodeHandle n;
    
    geometry_msgs::Twist cmd_vel;

    cmd_vel_pub_= n.advertise<geometry_msgs::Twist>("/taobot_cmd_vel", 1);

    actuator_sub = n.subscribe<std_msgs::Int32>("/actuator", 1, actuatorSubCallback);

    while(ros::ok()){

    	if(goUp == 1){
    		cmd_vel.angular.x = 1;
    		for(int i = 0; i < 1500; i ++){
    			ROS_INFO("in this loop 1");
    			cmd_vel_pub_.publish(cmd_vel);
                ros::Duration(0.05).sleep();
    		}
    		goUp = 0;
    	}

    	if(goDown == 1){
    		cmd_vel.angular.x = -1;
    		for(int i = 0; i < 1500; i ++){
    			ROS_INFO("in this loop 2");
    			cmd_vel_pub_.publish(cmd_vel);
                ros::Duration(0.05).sleep();
    		}
    		goDown = 0;

    	}

    	ros::spinOnce();

    }//ros::ok
}//main