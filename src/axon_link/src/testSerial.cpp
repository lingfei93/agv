#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <cereal_port/CerealPort.h>
#include <iostream>

using namespace std;




#define PI           3.14159
#define RTD          180.0/PI       //Radian to Degree
#define DTR          PI/180.0       //Degree to Radian
#define TS 0.1                      //unit:s

#define AXON_ROBOT_R 0.1075         //unit:m
#define AXON_ROBOT_L 0.2680         //unit:m

#define AXON_WHEEL_MINSPEED 0.0065 //(rad/s)
#define AXON_WHEEL_CMD_LIMIT 127

#define LENGTH 8
#define TIMEOUT 1000
cereal::CerealPort device;
unsigned char rx_buff[8];
char reply[8];

void commandSend(unsigned char a, unsigned char b, unsigned char c){	
	char foo[4];
	unsigned char bar[3];
	int d;
	bar[0] = a;
	bar[1] = b;
	bar[2] = c;
	foo[0] = (char) a;
	foo[1] = (char) b;
	foo[2] = (char) c;
	foo[4] = '\0';
	d = device.write(foo, 3);
	cout << d << endl;
	cout<< "this is printing" << endl;

	
	try{ device.read(reply, LENGTH, TIMEOUT); }
    catch(cereal::Exception& e)
    {
        ROS_FATAL("Failed to read the AXON serial port!!!");
        ROS_BREAK();
    }
	ROS_INFO("I'm trying to write");
}


int main(int argc, char** argv)
{

    ros::init(argc, argv, "axon_link_node");
    ros::NodeHandle n;
    // ros::Subscriber cmd_vel_sub_;


   

    // rm.L=AXON_ROBOT_L;
    // rm.r=AXON_ROBOT_R;
    // rc.ts=TS;

    int i;
    int baud_rate=0;
    std::string serial_port;

    serial_port = "/dev/ttyUSB0";
    baud_rate = 38400;
    ROS_INFO("I get SerialPort: %s", serial_port.c_str());

 
    ROS_INFO("I get BaudRate: %d", baud_rate);

  

    // Change the next line according to your port name and baud rate
    
    try{ device.open(serial_port.c_str(), baud_rate); }
    catch(cereal::Exception& e)
    {
        ROS_FATAL("Failed to open the AXON serial port!!!");
        ROS_BREAK();
    }
    ROS_INFO("The AXON serial port is opened.");

    ros::Rate r(10);
    while(ros::ok())
    {	
    	commandSend(3, 0, 0);

        ros::spinOnce();
        r.sleep();
    }   
}