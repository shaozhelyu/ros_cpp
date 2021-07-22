/*
 * @Author: your name
 * @Date: 2021-07-02 15:58:32
 * @LastEditTime: 2021-07-21 17:05:09
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
    goalTest(ros::NodeHandle nh,ros::NodeHandle nh_priv);

    void personDetectCallback(const std_msgs::Bool& ifPerson);
    void publishGoal();

    void periodicUpdate(const ros::TimerEvent& event);
    
    void generateRotate(move_base_msgs::MoveBaseGoal& goal);
    ~goalTest();

private:
    ros::NodeHandle nh;
    ros::Subscriber peopleSub;

    MoveBaseClient* ac;
    // this one is used to publish cancel command
    ros::Publisher pubCancel;
    ros::Timer periodicUpdateTimer_;
    double* x_goal;
    double* y_goal;
    double* yaw_goal;

    double last_x;
    double last_y;
    double curr_x;
    double curr_y;
    // double curr_rotate;
    // double last_rotate;

    double square_length_x;
    double square_length_y;

    // the number of goals
    int goal_num;

    // index of current goal
    int goal_count;

    // status of car
    bool car_running;

    // if there is a person
    bool peopleDetected;

    double stop_time;

    double restart_delay;

};

#endif