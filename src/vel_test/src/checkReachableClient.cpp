/*
 * @Author: your name
 * @Date: 2021-07-14 14:13:48
 * @LastEditTime: 2021-07-14 17:38:19
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /src/vel_test/src/checkReachableClient.cpp
 */
#include <ros/ros.h>
#include <vel_test/CheckValid.h>
#include <cstdlib>
#include <vel_test/checkReachableServer.h>
int main(int argc, char ** argv){
    ros::init(argc,argv,"Check_reachable_client");
    if(argc != 3){
        ROS_INFO("usage: Check valid client X Y");
        return 1;
    }

    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<vel_test::CheckValid>("CheckValid");
    vel_test::CheckValid srv;
    srv.request.x = atoll(argv[1]);
    srv.request.y = atoll(argv[2]);

    if(client.call(srv)){
        ROS_INFO("Sum: %d", srv.response.status);
    } else {
        ROS_ERROR("Failed to call service checkvalid");
        return 1;
    }
    return 0;
}