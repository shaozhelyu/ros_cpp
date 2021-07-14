/*
 * @Author: your name
 * @Date: 2021-07-14 16:04:00
 * @LastEditTime: 2021-07-14 17:31:35
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /src/vel_test/include/vel_test/checkReachableServer.h
 */
#ifndef LFI_CHECK_REACHABLE_H
#define LFI_CHECK_REACHABLE_H
#include <ros/ros.h>
#include <vector>
#include <vel_test/CheckValid.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/Float32MultiArray.h>

enum status {REACHABLE, UNREACHABLE, NOODOM, NODETECT};

class checkReachable
{
public:
    checkReachable(ros::NodeHandle nh, ros::NodeHandle nh_priv);
    ~checkReachable();
    bool checkReach(vel_test::CheckValid::Request &req,
            vel_test::CheckValid::Response &res);
    void currPosCallback(const nav_msgs::Odometry::ConstPtr& odom);
    void contourCallback(const std_msgs::Float32MultiArray& arrays);
private:
    ros::NodeHandle _nh;
    ros::NodeHandle _nh_priv;
    ros::ServiceServer server;

    ros::Subscriber odomSub;
    ros::Subscriber contourSub;

    std::vector<float> contourArray;
    double curr_x;
    double curr_y;
    
};


#endif