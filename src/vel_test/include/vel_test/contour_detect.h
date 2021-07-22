/*
 * @Author: your name
 * @Date: 2021-07-13 18:02:55
 * @LastEditTime: 2021-07-22 16:06:02
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /vel_test/include/vel_test/contour_detect.h
 */
#ifndef LFI_CONTOUR_DETECT_H
#define LFI_CONTOUR_DETECT_H
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/Bool.h>


class contourDetect{

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

public:
    contourDetect(ros::NodeHandle nh,ros::NodeHandle nh_priv);
    ~contourDetect();
    void publishGoal();
    bool checkValid(double x, double y);
    bool generateRotate(move_base_msgs::MoveBaseGoal& goal);
    void periodicPublishGoal(const ros::TimerEvent& event);
private:
    ros::NodeHandle _nh;
    ros::NodeHandle _nh_priv;

    MoveBaseClient* ac;
    ros::Publisher pubCancel;
    ros::Timer periodicUpdateTimer_;
    ros::ServiceClient checkValidClient;
    
    double *x_goal;
    double *y_goal;
    // double* yaw_goal;

    double square_length_x;
    double square_length_y;

    int goal_num;
    int goal_count;

    bool car_running;

    bool rotate2NextGoal;
    double goal_x;
    double goal_y;
    double pos_x;
    double pos_y;
    double last_rotate;
    
};


#endif