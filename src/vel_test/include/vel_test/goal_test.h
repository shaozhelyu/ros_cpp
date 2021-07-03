/*
 * @Author: your name
 * @Date: 2021-07-02 15:58:32
 * @LastEditTime: 2021-07-03 12:07:31
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /src/vel_test/include/vel_test/goal_test.h
 */
#ifndef LFI_GOAL_TEST_H
#define LFI_ROBOT_TEST_H
#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/Bool.h>
class goalTest
{
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

public:
    goalTest(ros::NodeHandle nh);

    void cancelGoal();
    void personDetectCallback(const std_msgs::Bool& ifPerson);
    void publishGoal();

    void periodicUpdate(const ros::TimerEvent& event);
    ~goalTest();

private:
    ros::NodeHandle nh;
    ros::Subscriber peopleSub;
    ros::Subscriber v;

    MoveBaseClient* ac;
    // this one is used to publish cancel command
    ros::Publisher pubCancel;
    ros::Timer periodicUpdateTimer_;
    double* x_goal;
    double* y_goal;
    double* yaw_goal;

    // the number of goals
    int goal_num;

    // index of current goal
    int goal_count;

    // status of car
    bool car_running;

    // if there is a person
    bool peopleDetected;

};

#endif