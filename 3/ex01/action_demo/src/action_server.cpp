   #include <action_demo/message_turtle_commandsAction.h>  
   #include <actionlib/server/simple_action_server.h>
   #include <geometry_msgs/Twist.h>
   #include <ros/ros.h>

   typedef actionlib::SimpleActionServer<action_demo::message_turtle_commandsAction> Server;
   geometry_msgs::Twist msg;
   int total_dis = 0;
   bool flag = false;

   void execute(const action_demo::message_turtle_commandsGoalConstPtr& goal, Server* as)
   {
     flag = true;
     ROS_INFO("command is %s", goal->command.c_str());
     if(goal->command == "forward"){
       msg.linear.x = goal->s;
       total_dis = total_dis + msg.linear.x;
     }
     if(goal->command == "turn_left"){
       msg.angular.z = goal->angle / 180 * 3.14;
     }
     if(goal->command == "turn_right"){
       msg.angular.z = -(float)goal->angle / 180.0 * 3.14;
     }
    
    ros::Duration(2.5).sleep();
     as->setSucceeded();
   }

  int main(int argc, char** argv)
   {
    ros::init(argc, argv, "action_Server");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1);
    action_demo::message_turtle_commandsFeedback feedback;
    Server server(n, "commands", boost::bind(&execute, _1, &server), false);
    server.start();

    while(ros::ok()){
      ros::spinOnce();

      if(flag == true){
        ros::Duration(0.5).sleep();
        ROS_INFO("msg is :%f  %f", msg.linear.x, msg.angular.z);
        pub.publish(msg);
        
        feedback.odom = total_dis;
        server.publishFeedback(feedback);
        ros::Duration(1).sleep();
        msg.linear.x = 0;
        msg.angular.z = 0;
        flag = false;
      }
    }
    ros::spin();
    return 0;
   }
