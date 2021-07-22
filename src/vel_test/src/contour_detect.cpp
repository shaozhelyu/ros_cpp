/*
 * @Author: your name
 * @Date: 2021-07-13 18:00:05
 * @LastEditTime: 2021-07-22 16:28:04
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
_nh_priv(nh_priv),
goal_count(0),
goal_num(9),
pos_x(0.0),
pos_y(0.0),
last_rotate(0.0),
rotate2NextGoal(true)
{
    // initialize all the parameter we need
    double square_length_x = 3.0;
    double square_length_y = 0.3;

    // hard code initializa goals
    x_goal = new double[goal_num]{0,square_length_x/3, square_length_x*2/3, square_length_x,square_length_x,square_length_x*2/3, square_length_x/3,0,0};
    y_goal = new double[goal_num]{0, 0, 0, 0, square_length_y, square_length_y, square_length_y, square_length_y, 0};
    
    // boost::shared_ptr<nav_msgs::Odometry const> sharedOdom = ros::topic::waitForMessage<nav_msgs::Odometry>("/odom",ros::Duration(2));
    // if(sharedOdom != nullptr){
    //   pos_x = sharedOdom->pose.pose.position.x;
    //   pos_y = sharedOdom->pose.pose.position.y;
    // }
    
    // initialize the move_base client
    ac = new MoveBaseClient("move_base",true);
    while(!ac -> waitForServer(ros::Duration(5.0))){
        ROS_INFO("Waiting for the move_base action server to come up");
    }

    // initialize the timer for periodic publish the goal
    periodicUpdateTimer_ = _nh.createTimer(ros::Duration(1./2.0), &contourDetect::periodicPublishGoal,this);
    
    // initialize checkValid client
    checkValidClient = _nh.serviceClient<vel_test::CheckValid>("CheckValid");
}


/*
periodic publish goal
*/
void contourDetect::periodicPublishGoal(const ros::TimerEvent& event){
    
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


/*
publish goal point to move_base server
*/ 
void contourDetect::publishGoal(){
    move_base_msgs::MoveBaseGoal goal;
    if(!contourDetect::generateRotate(goal)){
        return;
    }
    ac -> sendGoal(goal);  
    ac -> waitForResult();
    if(ac -> getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
        ROS_INFO("Reach goal %f %f", goal.target_pose.pose.position.x, goal.target_pose.pose.position.y);
        // goal_count ++;
    }
    else{
      ROS_INFO("The base failed to move to goal, maybe the goal is canceled");
      car_running = false;
    }

    
}

/*
generate rotate from current goal to next goal
return is if this goal is a rotate or move
*/ 
bool contourDetect::generateRotate(move_base_msgs::MoveBaseGoal& goal){  

    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();
    bool rotate = false;
    // double last_rotate = 0;
    while(goal_count < goal_num){
        if(rotate2NextGoal){
            goal_x = pos_x;
            goal_y = pos_y;
            rotate = true;
            if(goal_count < goal_num){
                double angle = atan2((y_goal[goal_count] - pos_y),(x_goal[goal_count] - pos_x));   
                // if last_rotate is the same as this one
                if(fabs(last_rotate - angle) < 0.1 ){                    
                    rotate2NextGoal = !rotate2NextGoal;
                    continue;
                }                
                last_rotate = angle;                
            } else {
                last_rotate = 0;
            }
            break;
        } else {
            // if it need to go to next goal
            goal_x = x_goal[goal_count];
            goal_y = y_goal[goal_count];
            // if this goal is valid then continue
            // else if it is invalid, then check next goal
            if(!checkValid(goal_x,goal_y)){
                goal_count ++;
                rotate2NextGoal = !rotate2NextGoal;
                continue;
            }
            goal_count ++;
            break;
        }
        
    }
    rotate2NextGoal = !rotate2NextGoal;
    goal.target_pose.pose.position.x = goal_x;
    goal.target_pose.pose.position.y = goal_y;      
    tf2::Quaternion quat;
    quat.setRPY(0,0,last_rotate);
    quat.normalize();
    geometry_msgs::Quaternion q = tf2::toMsg(quat); 
    goal.target_pose.pose.orientation = q;
    ROS_INFO("Sending goal %.2f %.2f %.2f",pos_x, pos_y, last_rotate);  
    
    return true;
}


/*
check if a goal is valid
*/
bool contourDetect::checkValid(double x, double y){
    bool valid = false;
    int nonSensorCount = 0;
    vel_test::CheckValid srv;
    srv.request.x = x;
    srv.request.y = y;
    while(!valid){
        if(checkValidClient.call(srv)){
            if(srv.response.status == REACHABLE){
                // ROS_INFO("Goal %.2f %.2f reachable. ",x, y);
                pos_x = goal_x;
                pos_y = goal_y;
                return true;
            } else if(srv.response.status == UNREACHABLE){
                // ROS_INFO("Goal %.2f %.2f unreachable. ",x, y);
                nonSensorCount = 0;
                return false;
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
    
    return false;
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