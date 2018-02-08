#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <math.h>
#include "serial/serial.h"
#include <taobot_link/Taobot.h>

using namespace std;




#define PI           3.14159265358979323846
#define RTD          180.0/PI       //Radian to Degree
#define DTR          PI/180.0       //Degree to Radian
#define TS 0.1                      //unit:s

// for SERIAL communication
#define TIMEOUT 1000
#define port "/dev/ttyUSB0"
#define baud 115200

void format(uint8_t* reply, int N);
void usart_send(char* toSend);
serial::Serial device(port, baud, serial::Timeout::simpleTimeout(1000));
ros::Publisher taobot_pub;

int count_average = 0;
double total_difference = 0;
// char reply[9];




void callback1(const ros::TimerEvent&)
{
    uint8_t reply[44];
    uint8_t temp;
    try{ device.read(reply, 44);
    ROS_INFO("Successful Read without Write!");
    format(reply, 43);
    // for (int i =0; i < 43; i ++){
    // //ROS_INFO("%c", reply[i]);}
    // temp=reply[i];
    // printf("0x%d%d\n", temp/16, temp % 16);

    // }
    }

    catch(exception& e)
    {
        ROS_FATAL("Failed to read the taobot serial port!!!");
        ROS_BREAK();
    }
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

//format the reply so that it becomes nice. checks if the data is formatted properly. throws away the last set of 
    //data for now
    //TODO: can we check if the last set of data can be read?, actually i think it works for now!
void format(uint8_t* reply, int N){
    int count = 0;
    taobot_link::Taobot msg;

    for (int i = 0; i < N; i ++)
        if(reply[i] == 0xff && reply[i+10] == 0xff && reply[i+1] ==0xfe && reply[i+11] == 0xfe){
        ROS_INFO("%d set of data, i is %d", count + 1, i);
        count = count + 1;
        //assigning message here and publishing it here probably
        msg.motorA_encoder = reply[i+2];
        msg.motorA_dir     = reply[i+3];
        msg.motorB_encoder = reply[i+4];
        msg.motorB_dir     = reply[i+5];
        msg.motorC_encoder = reply[i+6];
        msg.motorC_dir     = reply[i+7];
        msg.voltage        = 20.1 .//THIS IS A PLACEHOLDER;
        taobot_pub.publish(msg);
        for (int j = 0; j < 11; j ++){

        printf("0x%d%d\n", reply[i+j]/16, reply[i+j] % 16);
        }
        }

}

int main(int argc, char** argv)
{

    ros::init(argc, argv, "Taobot_Info");
    ros::NodeHandle n;

    taobot_pub = n.advertise<taobot_link::Taobot>("taobot_listener", 1000);
    

    ros::Rate loop_rate(5);
    while (ros::ok()){
	uint8_t reply[44];
	


    int i;

	uint8_t temp;
    std::string serial_port;
    uint8_t firstByte[2], secondByte[1], thirdByte[1], fourthByte[1], fifthByte[1];
    uint8_t sixthByte[1], seventhByte[1], eigthByte[1], ninthByte[1], tenthByte[1];


    ROS_INFO("I get SerialPort: %s", port);

 
    ROS_INFO("I get BaudRate: %d", baud);

  

    // Change the next line according to your port name and baud rate
    if(device.isOpen()){
        ROS_INFO("serial is successful");
    }


    ROS_INFO("The taobot serial port is opened.");
    char send_speed1[] = { '0xFF', '0xFE', '2', '0', '72', '0', '0', '0', '44', '0x07', '\0'};

    ros::Rate r(10);

//this is for all the wheels to turn with a same speed. rotation ont he spot.
    firstByte[0] = 0xFF;
    secondByte[0] = 0xFE;
    thirdByte[0] = 2;
    fourthByte[0] = 0;
    fifthByte[0] = 0x00;
    sixthByte[0] = 0;
    seventhByte[0] = 0x00;
    eigthByte[0] = 0;
    ninthByte[0] = 0x00;
    tenthByte[0] = 0x07;

	usart_send(firstByte);
    usart_send(secondByte);
    usart_send(thirdByte);
    usart_send(fourthByte);
    usart_send(fifthByte);
    usart_send(sixthByte);
    usart_send(seventhByte);
    usart_send(eigthByte);
    usart_send(ninthByte);
    usart_send(tenthByte);


	
	try{ device.read(reply, 44);
    format(reply, 43);
	ROS_INFO("Successful Read without Write!");
	// for (int i =0; i < 43; i ++){
	// //ROS_INFO("%c", reply[i]);}
 //    temp=reply[i];
	// printf("0x%d%d\n", temp/16, temp % 16);

	// }
	}

	catch(exception& e)
    {
        ROS_FATAL("Failed to read the taobot serial port!!!");
        ROS_BREAK();
    }
	
    
    ros::Timer timer1 = n.createTimer(ros::Duration(0.1), callback1);           //keep calling 1 and 3
    //ros::Timer timer2 = n.createTimer(ros::Duration(1.0), callback2);
    
    ros::spin();
    }
    
}
