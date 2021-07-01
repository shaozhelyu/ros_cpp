/*
 * @Author: your name
 * @Date: 2021-06-29 17:40:19
 * @LastEditTime: 2021-06-29 17:45:51
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /simple_cpp/src/add_two_int_client.cpp
 */

#include "ros/ros.h"
#include "simple_cpp/AddTwoInts.h"
#include <cstdlib>

int main(int argc, char** argv){
    ros::init(argc,argv,"add_two_init_client");
    if(argc != 3){
        ROS_INFO("usage: add_two_ints_client X Y");
        return 1;
    }

    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<simple_cpp::AddTwoInts>("add_two_ints");

    simple_cpp::AddTwoInts srv;
    srv.request.a = atoll(argv[1]);
    srv.request.b = atoll(argv[2]);

    if(client.call(srv)){
        ROS_INFO("Sum: %ld", (long int)srv.response.sum);
    }
    else{
        ROS_ERROR("Failed to call service add_two_ints");
        return 1;
    }
    return 0;
}