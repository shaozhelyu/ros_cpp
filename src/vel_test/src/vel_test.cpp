/*
 * @Author: your name
 * @Date: 2021-06-30 15:25:38
 * @LastEditTime: 2021-07-01 11:21:03
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /vel_test/src/vel_test.cpp
 */
#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3.h>
#include <cmath>
#include "vel_test/vel_test.h"

typedef nav_msgs::Odometry::ConstPtr odomPtr;
typedef geometry_msgs::Twist::ConstPtr twistPtr;
velTest::velTest(ros::NodeHandle vnh):
real_x(0.0),
real_y(0.0),
cmd_x(0.0),
cmd_y(0.0)
{

    vError = vnh.advertise<geometry_msgs::Vector3>("odometry/error",10);
    vOdom = vnh.subscribe<nav_msgs::Odometry>("odom",1,[&](const odomPtr& odom){
        real_x = odom->twist.twist.linear.x;
        real_y = odom->twist.twist.linear.y;
        ROS_INFO("real odom x: %f y: %f",real_x, real_y);
    });

    vTwist = vnh.subscribe<geometry_msgs::Twist>("twist",1,[&](const twistPtr& twist){
        cmd_x = twist->linear.x;
        cmd_y = twist->linear.y;
        ROS_INFO("cmd odom x: %f y: %f",cmd_x, cmd_y);
    }); 

    ros::Duration start_delay(0.0);
    start_delay.sleep();

    periodicUpdateTimer_ =  vnh.createTimer(ros::Duration(1./10.0),[&](const ros::TimerEvent&){
        geometry_msgs::Vector3 v;
        v.x = cmd_x - real_x;
        v.y = cmd_y - real_y;
        v.z = std::sqrt(std::pow(real_x-cmd_x,2) + std::pow(real_y,cmd_y));
        vError.publish(v);
    });
};

velTest::~velTest(){};
int main(int argc, char** argv){
    ros::init(argc,argv,"vel_err_check");
    ros::NodeHandle n;
    velTest test(n);
    ros::spin();

    return 0;
}