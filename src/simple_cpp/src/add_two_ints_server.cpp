/*
 * @Author: your name
 * @Date: 2021-06-29 17:28:25
 * @LastEditTime: 2021-06-29 17:43:34
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /simple_cpp/src/add_two_ints_server.cpp
 */

#include "ros/ros.h"
#include "simple_cpp/AddTwoInts.h"

bool add(simple_cpp::AddTwoInts::Request &req,
        simple_cpp::AddTwoInts::Response &res)
{
    res.sum = req.a + req.b;
    ROS_INFO("request: x=%ld, y=%ld", (long int)req.a, (long int)req.b);
    ROS_INFO("sending back response: [%ld]", (long int)res.sum);
    return true;
}

int main(int argc, char**argv){
    ros::init(argc,argv,"add_two_ints_server");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("add_two_ints", add);
    ROS_INFO("Ready to add two ints.");
    ros::spin();

    return 0;
}