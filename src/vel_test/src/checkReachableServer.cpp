/*
 * @Author: your name
 * @Date: 2021-07-14 14:00:25
 * @LastEditTime: 2021-07-14 16:22:45
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /src/vel_test/src/checkValid.cpp
 */

#include <iostream>
#include <vel_test/checkReachableServer.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/Float32MultiArray.h>

checkReachable::checkReachable(ros::NodeHandle nh, ros::NodeHandle nh_priv):
_nh(nh),
_nh_priv(nh_priv)
{
    server = _nh.advertiseService("CheckValid",checkReachable::checkReach,this);
    odomSub = _nh.subscribe("/odom",1,&checkReachable::currPosCallback,this);
    contourSub = _nh.subscribe("/grass_contour",1,&checkReachable::contourCallback,this);
}

void checkReachable::currPosCallback(const nav_msgs::Odometry& odom){
    curr_x = odom.pose.pose.position.x;
    curr_y = odom.pose.pose.position.y;
}

void checkReachable::contourCallback(const std_msgs::Float32MultiArray& arrays){
    contourArray = arrays.data;
}

checkReachable::~checkReachable(){}

bool checkReachable::checkReach(vel_test::CheckValid::Request &req,
            vel_test::CheckValid::Response &res
){
    double x = req.x;
    double y = req.y;
    std::cout << req.x << " " << req.y << std::endl;
    if(x*x + y*y < 1){
        res.valid = true;
    } else {
        res.valid = false;
    }
    return true;
}

int main(int argc, char** argv){
    ros::init(argc,argv,"check_point_reachable");
    ros::NodeHandle nh;
    ros::NodeHandle nh_priv;
    checkReachable reachServer(nh,nh_priv);
    ROS_INFO("Check Reachable Service start. ");
    ros::spin();
    return 0;
}