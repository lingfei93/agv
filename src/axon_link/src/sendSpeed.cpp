#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <math.h>
#include "serial/serial.h"
#include <axon_link/Taobot.h>

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
void sendCommand(uint8_t* arrayToSend, int length);
serial::Serial device(port, baud, serial::Timeout::simpleTimeout(1000));
ros::Publisher taobot_pub;
ros::Subscriber cmd_vel_sub_;

int count_average = 0;
double total_difference = 0;
// char reply[9];




void callback1(const ros::TimerEvent&)
{
    uint8_t reply[44];
    uint8_t temp;
    try{ 

        device.read(reply, 44);
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
        ROS_FATAL("Failed to read the AXON serial port!!!");
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
    axon_link::Taobot msg;

    for (int i = 0; i < N; i ++)
        if(reply[i] == 0xff && reply[i+11] == 0xff && reply[i+1] ==0xfe && reply[i+12] == 0xfe){
            ROS_INFO("%d set of data, i is %d", count + 1, i);
            count = count + 1;
            //assigning message here and publishing it here probably
            msg.motorA_encoder = reply[i+2];
            msg.motorA_dir     = reply[i+3];
            msg.motorB_encoder = reply[i+4];
            msg.motorB_dir     = reply[i+5];
            msg.motorC_encoder = reply[i+6];
            msg.motorC_dir     = reply[i+7];
            msg.voltage        = reply[i+10];
            taobot_pub.publish(msg);
        //print every set of correct messages
        for (int j = 0; j < 11; j ++){
            printf("0x%d%d\n", reply[i+j]/16, reply[i+j] % 16);
        }
        }

}
//send in an array of bytes and it will send for you;
void sendCommand(uint8_t* arrayToSend, int length){
    uint8_t toSend[1];
    for (int i = 0; i < length; i ++){
        toSend[0] = arrayToSend[i];
        usart_send(toSend);
        ROS_INFO("sending from here! %d %d", toSend[0]/16, toSend[0]%16);
    }
}

uint8_t* changeToOmniSpeed(double verticalPress, double horizontalPress){
    uint8_t toSend[10];
    toSend[0] = 0xff;
    toSend[1] = 0xfe;
    toSend[2] = 2;
}

void cmdVelReceived(const geometry_msgs::Twist::ConstPtr& cmd_vel){
    geometry_msgs::Twist wlr_cmd;
    double v_cmd = cmd_vel->linear.x;
    double   w_cmd = cmd_vel->angular.z;
    uint8_t arrayToSend[];
    arrayToSend = changeToOmniSpeed(v_cmd, w_cmd);
    sendCommand(arrayToSend, 10);
}

int main(int argc, char** argv)
{

    ros::init(argc, argv, "Taobot_Info");
    ros::NodeHandle n;

    //this channel publishes news recieved from the robot
    taobot_pub = n.advertise<axon_link::Taobot>("taobot_listener", 1000);

    //this channel is to subscribe to velocity commands from the joystick
    cmd_vel_sub_  = n.subscribe<geometry_msgs::Twist>("taobot_cmd_vel", 1000, cmdVelReceived);

    

    ros::Rate loop_rate(5);
    while (ros::ok()){
	uint8_t reply[44];
	uint8_t sendArray[10];


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


    ROS_INFO("The AXON serial port is opened.");
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

    sendArray[0] = 0xFF;
    sendArray[1] = 0xFE;
    sendArray[2] = 2;
    sendArray[3] = 0;
    sendArray[4] = 0x00;
    sendArray[5] = 0;
    sendArray[6] = 0x00;
    sendArray[7] = 0;
    sendArray[8] = 0x00;
    sendArray[9] = 0x07;
	
    sendCommand(sendArray, 10);

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
        ROS_FATAL("Failed to read the AXON serial port!!!");
        ROS_BREAK();
    }
	
    
    ros::Timer timer1 = n.createTimer(ros::Duration(0.1), callback1);           //keep calling 1 and 3
    //ros::Timer timer2 = n.createTimer(ros::Duration(1.0), callback2);
    
    ros::spin();
    }
    
}