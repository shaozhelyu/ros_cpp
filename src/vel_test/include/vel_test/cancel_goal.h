/*
 * @Author: your name
 * @Date: 2021-07-03 12:36:13
 * @LastEditTime: 2021-07-05 16:18:55
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /src/vel_test/include/vel_test/cancel_goal.h
 */
#ifndef LFI_CANCEL_GOAL_H
#define LFI_CANCEL_GOAL_H
#include <ros/ros.h>
#include <std_msgs/Bool.h>
class cancelGoal
{
public:
    cancelGoal(ros::NodeHandle nh,ros::NodeHandle nh_priv);
    ~cancelGoal();
    void personDetectCallback(const std_msgs::Bool& ifPerson);
private:
    ros::Publisher pubCancel;
    ros::Subscriber peopleSub;
    double restart_delay;    
};

#endif