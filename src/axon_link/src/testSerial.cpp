#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <cereal_port/CerealPort.h>




#define PI           3.14159
#define RTD          180.0/PI       //Radian to Degree
#define DTR          PI/180.0       //Degree to Radian
#define TS 0.1                      //unit:s

#define AXON_ROBOT_R 0.1075         //unit:m
#define AXON_ROBOT_L 0.2680         //unit:m

#define AXON_WHEEL_MINSPEED 0.0065 //(rad/s)
#define AXON_WHEEL_CMD_LIMIT 127


int main(int argc, char** argv)
{

    ros::init(argc, argv, "axon_link_node");
    ros::NodeHandle n;
    // ros::Subscriber cmd_vel_sub_;


   

    // rm.L=AXON_ROBOT_L;
    // rm.r=AXON_ROBOT_R;
    // rc.ts=TS;
    cereal::CerealPort device;
    int i;
    int baud_rate=0;
    std::string serial_port;

    serial_port = "/dev/ttyUSB2";
    baud_rate = 38400;
    ROS_INFO("I get SerialPort: %s", serial_port.c_str());

 
    ROS_INFO("I get BaudRate: %d", baud_rate);

  

    // Change the next line according to your port name and baud rate
    try{ device.open("/dev/ttyUSB2", 38400); }
    catch(cereal::Exception& e)
    {
        ROS_FATAL("Failed to open the AXON serial port222!!!");
        ROS_BREAK();
    }
    try{ device.open(serial_port.c_str(), baud_rate); }
    catch(cereal::Exception& e)
    {
        ROS_FATAL("Failed to open the AXON serial port!!!");
        ROS_BREAK();
    }
    ROS_INFO("The AXON serial port is opened.");

    ros::Rate r(20);
    while(ros::ok())
    {

        ros::spinOnce();
        r.sleep();
    }   
}