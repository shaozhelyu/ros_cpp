/*
 * @Author: your name
 * @Date: 2021-07-14 14:00:25
 * @LastEditTime: 2021-07-21 17:48:14
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /src/vel_test/src/checkValid.cpp
 */

#include <iostream>
#include <vel_test/checkReachableServer.h>


checkReachable::checkReachable(ros::NodeHandle nh, ros::NodeHandle nh_priv):
_nh(nh),
_nh_priv(nh_priv)
{
    server = _nh.advertiseService("CheckValid",&checkReachable::checkReach,this);
    // odomSub = _nh.subscribe("/odom",1,&checkReachable::currPosCallback,this);
    // contourSub = _nh.subscribe("/grass_contour",1,&checkReachable::contourCallback,this);
}

void checkReachable::currPosCallback(const nav_msgs::Odometry::ConstPtr& odom){
    curr_x = odom->pose.pose.position.x;
    curr_y = odom->pose.pose.position.y;
}

void checkReachable::contourCallback(const std_msgs::Float32MultiArray& arrays){
    contourArray = arrays.data;
}

checkReachable::~checkReachable(){}

bool checkReachable::checkReach(vel_test::CheckValid::Request &req,
            vel_test::CheckValid::Response &res)
{
    // boost::shared_ptr<nav_msgs::Odometry const> sharedOdom;
    // nav_msgs::Odometry odom; 
    // sharedOdom = ros::topic::waitForMessage<nav_msgs::Odometry>("/odom",ros::Duration(2));
    // if(sharedOdom != nullptr){
    //     odom = *sharedOdom;
    // } else {
    //     res.status = NOODOM;
    //     return true;
    // }

    // boost::shared_ptr<std_msgs::Float32MultiArray const> sharedArrays;
    // std_msgs::Float32MultiArray arrays;
    // sharedArrays = ros::topic::waitForMessage<std_msgs::Float32MultiArray>("/grass_contour",ros::Duration(2));
    // if(sharedArrays != nullptr){
    //     arrays = *sharedArrays;
    // } else {
    //     res.status = NODETECT;
    //     return true;
    // }
    // curr_x = odom.pose.pose.position.x;
    // curr_y = odom.pose.pose.position.y;
    double x = req.x;
    double y = req.y;
    if(x*x + y*y < 3){
        ROS_INFO("distance %f reachable", x*x + y*y);
        res.status = REACHABLE;
    } else {
        ROS_INFO("distance %f unreachable", x*x + y*y);
        res.status = UNREACHABLE;
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