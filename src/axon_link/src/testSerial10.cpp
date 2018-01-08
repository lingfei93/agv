#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <math.h>
#include "serial/serial.h"

using namespace std;




#define PI           3.14159265358979323846
#define RTD          180.0/PI       //Radian to Degree
#define DTR          PI/180.0       //Degree to Radian
#define TS 0.1                      //unit:s

// for SERIAL communication
#define TIMEOUT 1000
#define port "/dev/ttyUSB0"
#define baud 115200

void updateOdometry(double x_distance, double y_distance, bool isClear);
double encoderToDistance(int encoderCount);
void usart_send(char* toSend);
serial::Serial device(port, baud, serial::Timeout::simpleTimeout(1000));
unsigned char reply[8];
double x_pos; //y position
double y_pos; //x position
double theta; //rad
int count_average = 0;
double total_difference = 0;
// char reply[9];
void callback1(const ros::TimerEvent&)
{
  commandSend(3, 0, 0);
}

void callback2(const ros::TimerEvent&)
{
  commandSend(1, 10, 10);
}

double encoderToDistance(int encoderCount) {
   

    return (encoderCount * METER_PER_COUNT);
    
}

void updateOdometry(double l_distance, double r_distance, bool isClear){
    if (!isClear){
        x_pos = 0;
        y_pos = 0;
        theta = 0;
    }
    else {

        double distance_travelled;
        double delta_theta;
        double delta_x;
        double delta_y;

        distance_travelled = (l_distance + r_distance) / 2;
        delta_theta = (l_distance - r_distance) / AXON_ROBOT_L;
        delta_x = distance_travelled * cos(theta + delta_theta/2);
        delta_y = distance_travelled * sin(theta + delta_theta/2);

        x_pos = x_pos + delta_x;
        y_pos = y_pos + delta_y;
        theta = theta + delta_theta;
    }
}

void getOdometry(){
    cout << "The current position is: x:" << x_pos << "y: " <<y_pos<<"angle: "<< theta<<endl;
}




void usart_send(uint8_t* toSend) 
	{
		size_t N;
        N = device.write(toSend, 1);
        
        //below is just testing purposes
		unsigned char temp, temp2;
        
		temp = toSend[0];
        temp2 = toSend[1];
		ROS_INFO("%d %d %d %d this is tosend updated", temp/16,temp%16, temp, N);
	}

int main(int argc, char** argv)
{

    ros::init(argc, argv, "axon_link_node");
    ros::NodeHandle n;


	uint8_t reply[40];
	


    int i;

	uint8_t temp;
    std::string serial_port;
    uint8_t firstByte[2];

    ROS_INFO("I get SerialPort: %s", port.c_str());

 
    ROS_INFO("I get BaudRate: %d", baud);

  
    updateOdometry(0, 0, false);
    getOdometry(); //get the odometry
    // Change the next line according to your port name and baud rate
    if(device.isOpen()){
        ROS_INFO("serial is successful");
    }


    ROS_INFO("The AXON serial port is opened.");
    char send_speed1[] = { '0xFF', '0xFE', '2', '0', '72', '0', '0', '0', '44', '0x07', '\0'};

    ros::Rate r(10);

    firstByte[0] = 0xFF;

    ROS_INFO("I broke before here");
	usart_send(firstByte);

	
	try{ device.read(reply, 100);
	ROS_INFO("Successful Read without Write!");
	for (int i =0; i < 40; i ++){
	//ROS_INFO("%c", reply[i]);}
    temp=reply[i];
	printf("0x%d%d\n", temp/16, temp % 16);

	}
	}

	catch(exception& e)
    {
        ROS_FATAL("Failed to read the AXON serial port!!!");
        ROS_BREAK();
    }
	
    /*
    ros::Timer timer1 = n.createTimer(ros::Duration(0.1), callback1);           //keep calling 1 and 3
    ros::Timer timer2 = n.createTimer(ros::Duration(1.0), callback2);
    */
    ros::spin();

    
}
