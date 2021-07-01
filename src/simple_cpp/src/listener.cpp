/*
 * @Author: your name
 * @Date: 2021-06-29 16:28:32
 * @LastEditTime: 2021-06-30 16:35:12
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Editcoid cha
 * @FilePath: /simple_cpp/src/listenser.cpp
 */
#include "ros/ros.h"
#include "std_msgs/String.h"

void chatterCallback(const std_msgs::String::ConstPtr& msg){
    ROS_INFO("I heard:[%s]", msg->data.c_str());
}

int main(int argc, char** argv){
    ros::init(argc,argv,"listener");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("chatter",1000,chatterCallback);

    ros::spin();

    return 0;
}

