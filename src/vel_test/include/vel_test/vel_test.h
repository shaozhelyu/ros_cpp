/*
 * @Author: your name
 * @Date: 2021-06-30 15:55:27
 * @LastEditTime: 2021-06-30 17:41:38
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /src/vel_test/include/test.h
 */
#ifndef LFI_ROBOT_TEST_H
#define LFI_ROBOT_TEST_H
#include <ros/ros.h>

class velTest
{
public:
    velTest(ros::NodeHandle vnh);

    ~velTest();
private:
    ros::NodeHandle vnh;
    ros::Subscriber vOdom;
    ros::Subscriber vTwist;
    ros::Publisher vError;
    ros::Timer periodicUpdateTimer_;

    double real_x;
    double real_y;
    double cmd_x;
    double cmd_y;
};

#endif