/*
 * @Author: your name
 * @Date: 2021-06-29 15:10:59
 * @LastEditTime: 2021-06-29 16:46:51
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /src/talker.cpp
 */
#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

int main(int argc, char** argv){
    ros::init(argc,argv,"talker");

    ros::NodeHandle n;
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter",1000);
    ros::Rate loop_rate(10);

    int count = 0;
    while(ros::ok()){
        std_msgs::String msg;
        std::stringstream ss;
        ss << "hello world" << count;
        msg.data = ss.str();

        ROS_INFO("%s", msg.data.c_str());

        chatter_pub.publish(msg);
        ros::spinOnce();

        loop_rate.sleep();
        ++ count;
    }
    return 0;
}