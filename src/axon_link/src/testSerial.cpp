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

// #define LENGTH 9
#define TIMEOUT 1000
void commandSend();
cereal::CerealPort device;
unsigned char reply[8];
// char reply[9];
void callback1(const ros::TimerEvent&)
{
  commandSend(3, 0, 0);
}

void callback2(const ros::TimerEvent&)
{
  commandSend(1, 64, 64);
}


void commandSend(unsigned char a, unsigned char b, unsigned char c){	
	char foo[4];
	unsigned char bar[3];
    int n;
    char reply[9];
    int left_ec;
    int right_ec;
     //dynamic declare how big the reply array is.
    int LENGTH = 2; //reply length, declare as 2 for testing purpose.
	int d; //testing variable
	int e; //testing variable
	int j; //for loop
	bar[0] = a;
	bar[1] = b;
	bar[2] = c;
	foo[0] = (char) a;
	foo[1] = (char) b;
	foo[2] = (char) c;
	foo[4] = '\0';
	d = device.write(foo, 3);

    if ((int) a == 3) {
        LENGTH = 9;
    }

    else if ((int) a == 1) {
        
        LENGTH = 2;
    }

	// e = device.read(reply, LENGTH, TIMEOUT);
	// cout << e << endl;

	try{ device.read(reply, LENGTH, TIMEOUT);

        if(LENGTH == 9){
            left_ec=0;
            right_ec=0;

            left_ec=(int)(reply[1]<<24);
            left_ec=left_ec+(int)(reply[2]<<16);
            left_ec=left_ec+(int)(reply[3]<<8);
            left_ec=left_ec+(int)(reply[3]);

            right_ec=(int)(reply[5]<<24);
            right_ec=left_ec+(int)(reply[6]<<16);
            right_ec=left_ec+(int)(reply[7]<<8);
            right_ec=left_ec+(int)(reply[8]);
            cout <<"left ec is : "<< left_ec << "right ec is: " <<right_ec << endl;     
        }
		for (j = 0; j < LENGTH; j ++) {

			cout << (int)reply[j] << endl;
			cout <<"this is reply " << j << endl;
			}
		}
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

    ros::Rate r(5);
    // commandSend(3, 0, 0);
    // commandSend(3, 0, 0);
    // commandSend(3, 0, 0);
    // commandSend(3, 0, 0);
    // commandSend(3, 0, 0);

    ros::Timer timer1 = n.createTimer(ros::Duration(0.1), callback1);
    ros::Timer timer2 = n.createTimer(ros::Duration(1.0), callback2);

    // while(ros::ok())
    // {	
    // 	commandSend(1, 64, 64);

    //     ros::spinOnce();
    //     r.sleep();
    // }
    commandSend(3, 0, 0);   
}