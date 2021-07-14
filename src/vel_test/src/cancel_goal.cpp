/*
 * @Author: your name
 * @Date: 2021-07-02 13:24:51
 * @LastEditTime: 2021-07-06 12:40:26
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /src/vel_test/src/goal_test.cpp
 */
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib_msgs/GoalID.h>
#include <actionlib/client/simple_action_client.h>
#include <vel_test/cancel_goal.h>
#include <std_msgs/Bool.h>
#include <unistd.h>
#include <math.h>
#include <iostream>
#include <tf2/LinearMath/Quaternion.h>
// typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;


cancelGoal::cancelGoal(ros::NodeHandle nh,ros::NodeHandle nh_priv):
restart_delay(5.0)
{
    nh_priv.param("restart_delay",restart_delay,1.0);
    std::cout << restart_delay << std::endl;
    pubCancel = nh.advertise<actionlib_msgs::GoalID>("/move_base/cancel",10);
    peopleSub = nh.subscribe("/people",1,&cancelGoal::personDetectCallback,this);
}

void cancelGoal::personDetectCallback(const std_msgs::Bool& ifPerson){
  if(ifPerson.data == true){
    actionlib_msgs::GoalID msg;
    msg.id = "";
    ros::Rate loop_rate(10);
    int count = 0;
    while(ros::ok() && count < 10){
        pubCancel.publish(msg);
        loop_rate.sleep();
        count ++;
    }
    ROS_INFO("cancel finishe %f",restart_delay);
  }
}

cancelGoal::~cancelGoal(){}
int main(int argc, char** argv){
  ros::init(argc, argv, "goals_cancel_node");
  ros::NodeHandle nh;
  ros::NodeHandle nh_priv("~");
  cancelGoal cg(nh,nh_priv);
  ros::spin();
  return 0;
}
