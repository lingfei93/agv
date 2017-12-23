#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <cereal_port/CerealPort.h>
#include <iostream>
#include <math.h>

using namespace std;




#define PI           3.14159265358979323846
#define RTD          180.0/PI       //Radian to Degree
#define DTR          PI/180.0       //Degree to Radian
#define TS 0.1                      //unit:s

#define AXON_ROBOT_R 0.1075         //unit:m
#define AXON_ROBOT_L 0.2680         //unit:m
#define CIRCUMFERENCE AXON_ROBOT_R * PI * 2.000 //units:m


#define AXON_WHEEL_MINSPEED 0.0065 //(rad/s)
#define AXON_WHEEL_CMD_LIMIT 127
#define ENCODER_COUNT_BASE 1024.000 * 25.000 //this is how much it turns in one round
#define METER_PER_COUNT  (AXON_ROBOT_R * PI * 2.000) / (1024.000 * 25.000)

// #define LENGTH 9
#define TIMEOUT 5000

void commandSend();
void updateOdometry(double x_distance, double y_distance, bool isClear);
double encoderToDistance(int encoderCount);
cereal::CerealPort device;
unsigned char reply[8];
double x_pos; //y position
double y_pos; //x position
double theta; //rad
int count_average = 0;
double total_difference = 0;
// char reply[9];
void callback1(const ros::TimerEvent&)
{
  commandSend();
}

void callback2(const ros::TimerEvent&)
{
  commandSend();
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

void commandSend(){
    char reply[9];
    char initialization[10] ={0};

    int LENGTH = 9;
    device.write(initialization, 10);
    device.write(initialization, 10);
    ROS_INFO("IM HERE");
    try {
        device.read(reply, LENGTH, TIMEOUT);

    }
    catch(cereal::Exception& e)
    {
        ROS_FATAL("What's going on here");
        ROS_BREAK();
    }


}
// void commandSend(unsigned char a, unsigned char b, unsigned char c){	
// 	char command[4];
//     int n;
//     char reply[9];
//     int left_ec;
//     int right_ec;

//     int LENGTH; //reply length, declare as 2 for testing purpose.


// 	int j; //for loop

// 	command[0] = (char) a;
// 	command[1] = (char) b;
// 	command[2] = (char) c;
// 	command[4] = '\0'; //have to terminate in null;
//     try {
// 	device.write(command, 3);
//     }
//     catch(cereal::Exception& e)
//     {
//         ROS_FATAL("I can't write");
//         ROS_BREAK();
//     }


//     if ((int) a == 3) {
//         LENGTH = 9;
//     }

//     else if ((int) a == 1) {
        
//         LENGTH = 2;
//     }

// 	// e = device.read(reply, LENGTH, TIMEOUT);
// 	// cout << e << endl;

// 	try{ device.read(reply, LENGTH, TIMEOUT);

//         if(LENGTH == 9){
//             left_ec=0;
//             right_ec=0;

//             left_ec=(int)(reply[1]<<24);
//             left_ec=left_ec+(int)(reply[2]<<16);
//             left_ec=left_ec+(int)(reply[3]<<8);
//             left_ec=left_ec+(int)(reply[3]);

//             right_ec=(int)(reply[5]<<24);
//             right_ec=left_ec+(int)(reply[6]<<16);
//             right_ec=left_ec+(int)(reply[7]<<8);
//             right_ec=left_ec+(int)(reply[8]);
//             cout <<"left ec is : "<< left_ec << "right ec is: " <<right_ec << endl;  
//             double difference = left_ec - right_ec;
//             count_average = count_average + 1;
//             total_difference = total_difference + difference;

//             cout <<"Average difference is : "<<total_difference / count_average << endl;
//             double leftTravel = encoderToDistance(left_ec);
//             double rightTravel = encoderToDistance(right_ec);
//             cout <<"left in meter is : "<< leftTravel << "m. right ec is: " <<rightTravel <<" m"<< endl;

//             updateOdometry(leftTravel, rightTravel, true);
//             getOdometry();

//         }
// 		for (j = 0; j < LENGTH; j ++) {

// 			// cout << (int)reply[j] << endl;
// 			// cout <<"this is reply " << j << endl;
// 			}
// 		}
//     catch(cereal::Exception& e)
//     {
//         ROS_FATAL("What's going on here");
//         ROS_BREAK();
//     }
// 	ROS_INFO("I'm trying to write");
// }





int main(int argc, char** argv)
{

    ros::init(argc, argv, "axon_link_node");
    ros::NodeHandle n;
    // ros::Subscriber cmd_vel_sub_;
    // rm.L=AXON_ROBOT_L;
    // rm.r=AXON_ROBOT_R;
    // rc.ts=TS;
    bool oneshot = true;
    int i;
    int baud_rate=0;
    std::string serial_port;

    serial_port = "/dev/ttyUSB0";
    baud_rate = 115200;
    ROS_INFO("I get SerialPort: %s", serial_port.c_str());

 
    ROS_INFO("I get BaudRate: %d", baud_rate);

  
    updateOdometry(0, 0, false);
    getOdometry(); //get the odometry
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

    ros::Timer timer1 = n.createTimer(ros::Duration(0.1), callback1);           //keep calling 1 and 3
    ros::Timer timer2 = n.createTimer(ros::Duration(1.0), callback2);
    ros::spin();

    // while(ros::ok())
    // {	
    // 	commandSend(1, 64, 64);

    //     ros::spinOnce();
    //     r.sleep();
    // }
    // commandSend(3, 0, 0);   
}