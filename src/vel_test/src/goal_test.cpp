/*
 * @Author: your name
 * @Date: 2021-07-02 13:24:51
 * @LastEditTime: 2021-07-03 12:32:20
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
// typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;


goalTest::goalTest(ros::NodeHandle nh){
    pubCancel = nh.advertise<actionlib_msgs::GoalID>("/move_base/cancel",10);
    goal_num = 9;
    double square_length_x = 1;
    double square_length_y = 1;
    x_goal = new double[goal_num]{0.0, 0.0, 0.0, square_length_x, square_length_x, square_length_x, square_length_x, 0.0, 0.0};
    y_goal = new double[goal_num]{0.0, square_length_y, square_length_y, square_length_y, square_length_y,0.0, 0.0, 0.0, 0.0};
    // cout << "x " << x_goal[0] << " y " <<
    yaw_goal = new double[goal_num]{0.0, 0.0, -M_PI/2, -M_PI/2,M_PI, M_PI, M_PI/2, M_PI/2, 0.0};
    goal_count = 0;
    car_running = true;

    // move_base goal
    ac = new MoveBaseClient("move_base",true);
    while(!ac -> waitForServer(ros::Duration(5.0))){
        ROS_INFO("Waiting for the move_base action server to come up");
    }
    peopleDetected = false;    
    peopleSub = nh.subscribe("/people",1,&goalTest::personDetectCallback,this);
    periodicUpdateTimer_ = nh.createTimer(ros::Duration(1./10.0), &goalTest::periodicUpdate, this);
    
    
    // periodicUpdateTimer_ = nh.createTimer(ros::Duration(1./10.0), [&]());
    
    // while(1){
    //   if(goal_count < goal_num){
    //     if(peopleDetected == false){
    //       publishGoal();
    //       ROS_INFO("Finish one goal");
    //     } else {
    //       // if(car_running){
    //       ROS_INFO("Cancel the goal");
    //       goalTest::cancelGoal();
    //       // }          
    //       car_running = false;
    //     }
    //   } else {
    //     ROS_INFO("Whole trajectory finished");
    //     break;
    //   }
    // }
    // ros::shutdown();    
}

void goalTest::periodicUpdate(const ros::TimerEvent& event){
    if(goal_count < goal_num){
      if(car_running){
        publishGoal();
      }
    } else {
      ROS_INFO("Whole trajectory finished");
      ros::shutdown(); 
    }
}


void goalTest::personDetectCallback(const std_msgs::Bool& ifPerson){
  if(ifPerson.data == true){
    ROS_INFO("Sending cancel goal");
    cancelGoal();
    car_running = false;
  } else {
    car_running = true;
  }
}

void goalTest::publishGoal(){
    ROS_INFO("Sending goal %f %f %f",x_goal[goal_count], y_goal[goal_count], yaw_goal[goal_count]);

    move_base_msgs::MoveBaseGoal goal;
    goal.target_pose.header.frame_id = "base_link";
    goal.target_pose.header.stamp = ros::Time::now();
    ROS_INFO("Sending goal %f %f %f",x_goal[goal_count], y_goal[goal_count], yaw_goal[goal_count]);
    goal.target_pose.pose.position.x = x_goal[goal_count];
    goal.target_pose.pose.position.y = y_goal[goal_count];      
    tf2::Quaternion quat;
    quat.setRPY(0,0,yaw_goal[goal_count]);
    quat.normalize();
    goal.target_pose.pose.orientation.x = quat[0];
    goal.target_pose.pose.orientation.y = quat[1];
    goal.target_pose.pose.orientation.z = quat[2];
    goal.target_pose.pose.orientation.w = quat[3];
    ac -> sendGoal(goal);

    car_running = false;
    ac -> waitForResult();

    if(ac -> getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
        ROS_INFO("Reach goal %f %f %f",x_goal[goal_count], y_goal[goal_count], yaw_goal[goal_count]);
        goal_count ++;
        car_running = true;
    }
    else{
      ROS_INFO("The base failed to move forward 1 meter for some reason");
      // car_running = false;
    }

}

void goalTest::cancelGoal(){
    actionlib_msgs::GoalID msg;
    msg.id = "";
    ros::Rate loop_rate(10);
    int count = 0;
    while(ros::ok() && count < 10){
        pubCancel.publish(msg);
        loop_rate.sleep();
        count ++;
    }
    ROS_INFO("cancel finished");
}


goalTest::~goalTest(){}
int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals");
  ros::NodeHandle nh;  
  goalTest goal(nh);
  ros::spin();
  // usleep(10000);
  // this part is send a goal

  


  return 0;

}

  // this part is cancel a goal
//   ros::NodeHandle n;  
//   ros::Publisher pubCancel = n.advertise<actionlib_msgs::GoalID>("/move_base/cancel",10);
//   actionlib_msgs::GoalID msg;
//   msg.id="";
//   ros::Rate loop_rate(10);
//   int count = 0;
//   while(ros::ok() && count < 10){
//     pubCancel.publish(msg);
//     ros::spinOnce();
//     loop_rate.sleep();
//     count ++;
//   }
