/*
 * @Author: your name
 * @Date: 2021-07-02 13:24:51
 * @LastEditTime: 2021-07-23 17:31:32
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /src/vel_test/src/goal_test.cpp
 */
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib_msgs/GoalID.h>
#include <actionlib/client/simple_action_client.h>
#include <vel_test/goal_test.h>
#include <std_msgs/Bool.h>
#include <unistd.h>
#include <math.h>
#include <tf2/LinearMath/Quaternion.h>
#include <geometry_msgs/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <math.h>
#include <nav_msgs/Odometry.h>


/*
goalTest initialize
given the x and y goal

*/
goalTest::goalTest(ros::NodeHandle nh, ros::NodeHandle nh_priv):
goal_num(5),
restart_delay(3.0),
car_running(true),
peopleDetected(false),
goal_count(0),
last_x(0.0),
last_y(0.0),
curr_x(0.0),
curr_y(0.0)
{
    // nh_priv.param("restart_delay",restart_delay,1.0);
    // nh_priv.param("x_len",square_length_x,3.0);
    // nh_priv.param("y_len",square_length_y,0.3);
    double square_length_x = 3.0;
    double square_length_y = 0.3;
    // x_goal = new double[goal_num]{0, square_length_x, square_length_x, square_length_x, square_length_x, 0, 0, 0, 0};
    // y_goal = new double[goal_num]{0, 0, 0, square_length_y, square_length_y, square_length_y, square_length_y, 0, 0};
    // yaw_goal = new double[goal_num]{0.0, 0.0, M_PI/2, M_PI/2, M_PI, M_PI, -M_PI/2, -M_PI/2, 0.0};   
    x_goal = new double[goal_num]{0,square_length_x,square_length_x,0,0};
    y_goal = new double[goal_num]{0, 0, square_length_y, square_length_y, 0};
    
    boost::shared_ptr<nav_msgs::Odometry const> sharedOdom = ros::topic::waitForMessage<nav_msgs::Odometry>("/odom",ros::Duration(2));
    if(sharedOdom != nullptr){
      last_x = sharedOdom->pose.pose.position.x;
      last_y = sharedOdom->pose.pose.position.y;
      curr_x = sharedOdom->pose.pose.position.x;
      curr_y = sharedOdom->pose.pose.position.y;
    }
    
    // move_base goal
    ac = new MoveBaseClient("move_base",true);
    while(!ac -> waitForServer(ros::Duration(5.0))){
        ROS_INFO("Waiting for the move_base action server to come up");
    }   
    peopleSub = nh.subscribe("/people",1,&goalTest::personDetectCallback,this);
    periodicUpdateTimer_ = nh.createTimer(ros::Duration(1./2.0), &goalTest::periodicUpdate, this); 
}

void goalTest::generateRotate(move_base_msgs::MoveBaseGoal& goal){
  
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();
  double last_rotate = 0;
  
  // if curr goal is equal to last goal
  // then we go to next point
  if(curr_x == last_x && curr_y == last_y){
    last_x = curr_x;
    last_y = curr_y;
    curr_x = x_goal[goal_count];
    curr_y = y_goal[goal_count];
    goal_count ++;
  } else {
    // if curr goal is different from last goal
    // stay at the same point and rotate
    last_x = curr_x;
    last_y = curr_y;
    if(goal_count < goal_num){
      double angle = atan2((y_goal[goal_count] - curr_y),(x_goal[goal_count] - curr_x));
      // double angle = atan2((y_goal[goal_count] - curr_y),(x_goal[goal_count] - curr_x));
      // ROS_INFO("rotate angle: %f", angle);
      last_rotate = angle;
    } else {
      last_rotate = 0;
    }
  }
  goal.target_pose.pose.position.x = curr_x;
  goal.target_pose.pose.position.y = curr_y;      
  tf2::Quaternion quat;
  quat.setRPY(0,0,last_rotate);
  quat.normalize();
  geometry_msgs::Quaternion q = tf2::toMsg(quat); 
  goal.target_pose.pose.orientation = q;
  ROS_INFO("Sending goal %f %f %f",curr_x, curr_y, last_rotate);  
}


void goalTest::publishGoal(){
    move_base_msgs::MoveBaseGoal goal;
    goalTest::generateRotate(goal);
    ac -> sendGoal(goal);    
    ac -> waitForResult();
    if(ac -> getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
        ROS_INFO("Reach goal %f %f", goal.target_pose.pose.position.x, goal.target_pose.pose.position.y);
        // goal_count ++;
    }
    else{
      ROS_INFO("The base failed to move to goal, maybe the goal is canceled");
      car_running = false;
      stop_time = ros::Time::now().toSec();
    }
}


void goalTest::periodicUpdate(const ros::TimerEvent& event){
    if(goal_count < goal_num){
      double time_now =ros::Time::now().toSec();
      if(car_running && (ros::Time::now().toSec() - stop_time) > restart_delay){
        publishGoal();
      }
    } else {
      ROS_INFO("Whole trajectory finished");
      ros::shutdown(); 
    }
}

void goalTest::personDetectCallback(const std_msgs::Bool& ifPerson){
  if(ifPerson.data == false){
    car_running = true;
  }
}

// void goalTest::publishGoal(){
//     move_base_msgs::MoveBaseGoal goal;
//     goal.target_pose.header.frame_id = "map";
//     goal.target_pose.header.stamp = ros::Time::now();    
//     goal.target_pose.pose.position.x = x_goal[goal_count];
//     goal.target_pose.pose.position.y = y_goal[goal_count];      
//     tf2::Quaternion quat;
//     quat.setRPY(0,0,yaw_goal[goal_count]);
//     quat.normalize();
//     geometry_msgs::Quaternion q = tf2::toMsg(quat); 
//     goal.target_pose.pose.orientation = q;
//     ROS_INFO("Sending goal %f %f %f %f %f %f ",x_goal[goal_count], y_goal[goal_count], quat[0],quat[1],quat[2],quat[3]);
//     ac -> sendGoal(goal);    
//     ac -> waitForResult();

//     if(ac -> getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
//         ROS_INFO("Reach goal %f %f %f",x_goal[goal_count], y_goal[goal_count], yaw_goal[goal_count]);
//         goal_count ++;
//     }
//     else{
//       ROS_INFO("The base failed to move to goal, maybe the goal is canceled");
//       car_running = false;
//       stop_time = ros::Time::now().toSec();
//     }
// }

goalTest::~goalTest(){}
int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals");
  ros::NodeHandle nh;
  ros::NodeHandle nh_priv("~");  
  goalTest goal(nh,nh_priv);
  ros::spin();

  return 0;
}