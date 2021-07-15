/*
 * @Author: your name
 * @Date: 2021-07-13 18:00:05
 * @LastEditTime: 2021-07-15 13:45:21
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /vel_test/src/contour_detect.cpp
 */

#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib_msgs/GoalID.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/Bool.h>
#include <unistd.h>
#include <math.h>
#include <tf2/LinearMath/Quaternion.h>
#include <geometry_msgs/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <vel_test/checkReachableServer.h>
#include <vel_test/contour_detect.h>
#include <vel_test/CheckValid.h>

contourDetect::contourDetect(ros::NodeHandle nh, ros::NodeHandle nh_priv):
_nh(nh),
_nh_priv(nh_priv)
{
    goal_num = 13;
    goal_count = 0;
    double square_length_x = 3.0;
    double square_length_y = 0.3;
    x_goal = new double[goal_num]{0, square_length_x/3, square_length_x*2/3,square_length_x, square_length_x, square_length_x, square_length_x, square_length_x*2/3, square_length_x/3, 0, 0, 0, 0};
    y_goal = new double[goal_num]{0, 0, 0, 0, 0, square_length_y, square_length_y, square_length_y, square_length_y, square_length_y, square_length_y, 0, 0};
    yaw_goal = new double[goal_num]{0.0, 0, 0, 0.0, M_PI/2, M_PI/2, M_PI, M_PI, M_PI, M_PI, -M_PI/2, -M_PI/2, 0.0}; 
    ac = new MoveBaseClient("move_base",true);
    while(!ac -> waitForServer(ros::Duration(5.0))){
        ROS_INFO("Waiting for the move_base action server to come up");
    }
    periodicUpdateTimer_ = _nh.createTimer(ros::Duration(1./2.0), &contourDetect::periodicUpdate,this);
    checkValidClient = _nh.serviceClient<vel_test::CheckValid>("CheckValid");
}

void contourDetect::periodicUpdate(const ros::TimerEvent& event){
    checkValid();
    if(goal_count < goal_num){
        double time_now = ros::Time::now().toSec();
        if(car_running){
            
            publishGoal();
        }
    } else {
        ROS_INFO("Whole map finished");
        ros::shutdown();
    }
}

void contourDetect::publishGoal(){
    move_base_msgs::MoveBaseGoal goal;
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();    
    goal.target_pose.pose.position.x = x_goal[goal_count];
    goal.target_pose.pose.position.y = y_goal[goal_count];      
    tf2::Quaternion quat;
    quat.setRPY(0,0,yaw_goal[goal_count]);
    quat.normalize();
    geometry_msgs::Quaternion q = tf2::toMsg(quat); 
    goal.target_pose.pose.orientation = q;
    ROS_INFO("Sending goal %f %f %f %f %f %f ",x_goal[goal_count], y_goal[goal_count], quat[0],quat[1],quat[2],quat[3]);
    ac -> sendGoal(goal);    
    ac -> waitForResult();

    if(ac -> getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
        ROS_INFO("Reach goal %f %f %f",x_goal[goal_count], y_goal[goal_count], yaw_goal[goal_count]);
        goal_count ++;
    }
    else{
      ROS_INFO("The base failed to move to goal, maybe the goal is canceled");
      car_running = false;
    //   stop_time = ros::Time::now().toSec();
    }
}
void contourDetect::checkValid(){
    bool valid = false;
    int nonSensorCount = 0;
    while(!valid && goal_count < goal_num){
        vel_test::CheckValid srv;
        srv.request.x = x_goal[goal_count];
        srv.request.y = y_goal[goal_count];
        if(checkValidClient.call(srv)){
            if(srv.response.status == REACHABLE){
                ROS_INFO("Reachable. ");
                break;
            } else if(srv.response.status == UNREACHABLE){
                ROS_INFO("Goal %f %f unreachable. ",x_goal[goal_count], y_goal[goal_count]);
                goal_count ++;
                nonSensorCount = 0;
                continue;
            } else {
                nonSensorCount ++;                
                if(nonSensorCount == 5){
                    if(srv.response.status == NOODOM){
                        ROS_INFO("Cannot get current odom. ");
                    } else {
                        ROS_INFO("Cannot get current contour. ");
                    }
                    goal_count = goal_num;
                    ros::shutdown();
                    break;
                }
            }
        } else {
            ROS_ERROR("Failed to call service checkvalid");
            goal_count = goal_num;            
            ros::shutdown();
            break;
        }
        
    }
}

contourDetect::~contourDetect(){}
int main(int argc,char** argv){
    ros::init(argc, argv, "contour_detection_test");
    ros::NodeHandle nh;
    ros::NodeHandle nh_priv("~");

    contourDetect detect(nh,nh_priv);
    ROS_INFO("Contour start");
    ros::spin();
    return 0;

}