//ROS头文件
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include "turtlesim/Pose.h"

float current_x = 0.0;
float current_y = 0.0;

void poseCallback(const turtlesim::Pose::ConstPtr& msg)
{
  current_x = msg->x;
  current_y = msg->y;
    // 将接收到的消息打印出来
    ROS_INFO("Turtle pose: x:%0.6f, y:%0.6f", msg->x, msg->y);
}


int main(int argc, char **argv)
{
  if(argc != 4){
    ROS_INFO("input args is wrong!");
    return 0;
  }
  float x = std::stof(argv[1]);
  float y = std::stof(argv[2]);
  float theta = std::stof(argv[3]);
  
  ros::init(argc, argv, "talker");
  ros::NodeHandle nh;

  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
  ros::Subscriber sub = nh.subscribe("/turtle1/pose", 1, poseCallback);
  ros::spinOnce();

  ros::Rate loop_rate(10.0);
  //循环发布msg
  geometry_msgs::Twist msg;
  while (abs(current_x - x) > 0.5)
  {
    if(x - current_x >= 1){
      msg.linear.x = 1.0;
    }
    if(x - current_x <= -1){
      msg.linear.x = -1.0;
    }
    if(x - current_x >= 0 and x - current_x < 1){
      msg.linear.x = 0.1;
    }
    if(x - current_x > -1 and x - current_x < 0){
      msg.linear.x = -0.1;
    }
    pub.publish(msg);
    loop_rate.sleep();
    ros::spinOnce();
  }
  ros::spinOnce();
  float total_angle = 0;

  if(abs(y - current_y)>0.5){
    if(y - current_y>0.5){
    msg.angular.z = 1.57;
    total_angle = total_angle + msg.angular.z;
    msg.linear.x = 0;
    pub.publish(msg);
    ros::Duration(1).sleep();
    }
    if(y - current_y<-0.5){
      msg.angular.z = -1.57;
      total_angle = total_angle + msg.angular.z;
      msg.linear.x = 0;
      pub.publish(msg);
      ros::Duration(1).sleep();
    }
    while (abs(current_y - y) > 0.5){
      msg.angular.z = 0;
      if(abs(current_y - y) >= 1){
      msg.linear.x = 1.0;
      }
      else{
        msg.linear.x = 0.1;
      }
      pub.publish(msg);
      loop_rate.sleep();
      ros::spinOnce();
    }
  }
  msg.linear.x = 0;
  msg.angular.z = (float)theta / 180.0 * 3.14 - total_angle;
  // ROS_INFO("last msg.angular.z = %f", msg.angular.z);
  pub.publish(msg);
  ros::Duration(1).sleep();
  return 0;
} 

