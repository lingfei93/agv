#!/bin/bash 
# Author: Chen, Chun-Lin 
# Date:  2015-01-27 
# Update:2016-02-19
# This program setting ROS environment 
# Please keyin {ROS_BUILDWS_NAME}, {USER_NAME} and {ROS_CATKINWS_NAME} string, then edit .bashrc add one line "source ~/myros.sh" 
# 
#PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin 
#export PATH 
USER_NAME='eee' 
ROS_USE_ROSBUILD='0'
ROS_INFO_TIME='0'
ROS_BUILDWS_NAME='kinetic_workspace' 
ROS_CATKINWS_NAME='catkin_ws'

#ROS_REMOTE_IP='192.168.1.148'
AUTO_REMOTE_RELINK='1'
#AUTO_ROS_LAUNCH='camera test_camera.launch'
AUTO_ROS_LAUNCH=''
AUTO_RESTART='1'

WLAN_SSID=`iwgetid -r`
if [ $WLAN_SSID  = "ntu_eee_uav" ]; then
ROS_REMOTE_IP='192.168.1.148'
#ROS_REMOTE_IP=''
else
ROS_REMOTE_IP='192.168.1.114'
#ROS_REMOTE_IP=''
fi


 
#==Do not edit below========================================================  
if [ "$ROS_USE_ROSBUILD" = "1" ]; then 
#Setting ROS rosbuild workspace 
echo -e "\E[1;34mROS_PACKAGE_PATH (ROSBUILD) is setting.\E[0m" 
source ~/${ROS_BUILDWS_NAME}/setup.bash 
export ROS_PACKAGE_PATH=/home/${USER_NAME}/${ROS_BUILDWS_NAME}:${ROS_PACKAGE_PATH} 
 
#Add the NTU_Research_Group_ROS workspace 
#export ROS_PACKAGE_PATH=/home/chencl/NTU_Research_Group_ROS:${ROS_PACKAGE_PATH} 
else 
#Setting ROS catkin workspace 
echo -e "\E[1;34mROS_PACKAGE_PATH (CATKIN) is setting.\E[0m" 
source ~/${ROS_CATKINWS_NAME}/devel_isolated/setup.bash 
fi 
echo $ROS_PACKAGE_PATH 

#Setting ROS INFO Time in Display
if [ "$ROS_INFO_TIME" = "1" ]; then
export ROSCONSOLE_FORMAT='[${severity}] [${time}]: ${message}'
echo -e "ROS_INFO_TIME: \E[1;36mVISIBLE\E[0m" 
else
export ROSCONSOLE_FORMAT='[${severity}]: ${message}'
echo -e "ROS_INFO_TIME: \E[1;36mINVISIBLE\E[0m" 
fi
 
#Get current using all active local IP information 
LOCAL_IP=`ifconfig | grep 'inet addr:192.168' | sed 's/^.*addr://g' | sed 's/Bcast:.*$//g'` 
if [ "$LOCAL_IP" = "" ]; then 
echo -e "\E[1;31;47m!!!!!No Local Network connect!!!!!\E[0m" 
export ROS_MASTER_URI=http://localhost:11311 
echo -e "ROS_MASTER_URI: \E[1;36m$ROS_MASTER_URI\E[0m"	 
else 
echo -e "Active Local IP Address: \E[1;36m$LOCAL_IP\E[0m" 

echo -e "Wi-Fi AP SSID: \E[1;36m$WLAN_SSID\E[0m"  

#Print ROS IP Setting 
HOST_IP=`ifconfig | grep 'inet addr:192.168' | sed 's/^.*addr://g' | sed 's/Bcast:.*$//g' | sed -n 2p`
if [ "$HOST_IP" = "" ]; then
HOST_IP=`ifconfig | grep 'inet addr:192.168' | sed 's/^.*addr://g' | sed 's/Bcast:.*$//g' | sed -n 1p`
fi
export ROS_HOSTNAME=${HOST_IP} 
export ROS_IP=${HOST_IP}
 
if [ "$ROS_REMOTE_IP" = "" ]; then 
export ROS_MASTER_URI=http://localhost:11311	 
else 
export ROS_MASTER_URI=http://${ROS_REMOTE_IP}:11311 
fi 
 
#echo "ROS_HOSTNAME: $ROS_HOSTNAME"  
echo -e "ROS_IP: \E[1;36m$ROS_IP\E[0m" 
echo -e "ROS_MASTER_URI: \E[1;36m$ROS_MASTER_URI\E[0m" 
fi 

if [ "$AUTO_ROS_LAUNCH" != "" ]; then  
echo -e "AUTO_ROS_LAUNCH: \E[1;36m$AUTO_ROS_LAUNCH\E[0m"
fi
 
#Print all ROS Environment Variable 
#env | grep ROS 

if [ "$AUTO_RESTART" = "1" ]; then
#--loop--
while [ "$AUTO_ROS_LAUNCH" != "" ]; do
if [ "$AUTO_REMOTE_RELINK" = "1" ]; then
if [ "$ROS_REMOTE_IP" != "" ]; then
ROS_CORE_STATE=`rosnode list | grep '/rosout'`
while [ "$ROS_CORE_STATE" = "" ]; do
echo -e "\E[1;36mUse remote IP, Now waitting ROS Core to ready start !!\E[0m"
sleep 1
ROS_CORE_STATE=`rosnode list | grep '/rosout'`
done
fi
fi

if [ "$AUTO_ROS_LAUNCH" != "" ]; then  
roslaunch ${AUTO_ROS_LAUNCH}
fi
done
#--loop--
else
#--one time---
if [ "$AUTO_REMOTE_RELINK" = "1" ]; then
if [ "$ROS_REMOTE_IP" != "" ]; then
ROS_CORE_STATE=`rosnode list | grep '/rosout'`
while [ "$ROS_CORE_STATE" = "" ]; do
echo -e "\E[1;36mUse remote IP, Now waitting ROS Core to ready start !!\E[0m"
sleep 1
ROS_CORE_STATE=`rosnode list | grep '/rosout'`
done
fi
fi

if [ "$AUTO_ROS_LAUNCH" != "" ]; then  
roslaunch ${AUTO_ROS_LAUNCH}
fi
#--one time---
fi
