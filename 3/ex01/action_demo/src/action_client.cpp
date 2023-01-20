   #include <action_demo/message_turtle_commandsAction.h> // Note: "Action" is appended
   #include <actionlib/client/simple_action_client.h>
   #include <ros/ros.h>

   typedef actionlib::SimpleActionClient<action_demo::message_turtle_commandsAction> Client;

    void doneCb(const actionlib::SimpleClientGoalState& state,
        const action_demo::message_turtle_commandsResultConstPtr& result)
    {
        ROS_INFO("Done");
    }

    void activeCb()
    {
        ROS_INFO("active");
    }

    void feedbackCb(const action_demo::message_turtle_commandsFeedbackConstPtr& feedback)
    {
        ROS_INFO(" odom is  : %d ", feedback->odom);
    }


   int main(int argc, char** argv)
   {
    ros::init(argc, argv, "action_Client");
    Client client("commands", true);
    client.waitForServer();
    action_demo::message_turtle_commandsGoal goal;

  // Fill in goal here
    goal.command = "forward";
    goal.s = 2;
    goal.angle = 0;
    client.sendGoal(goal, &doneCb, &activeCb, &feedbackCb);
    client.waitForResult(ros::Duration(2.0));
    if (client.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
      ros::spinOnce();
    }

    goal.command = "turn_right";
    goal.s = 0;
    goal.angle = 90;
    client.sendGoal(goal, &doneCb, &activeCb, &feedbackCb);
    client.waitForResult(ros::Duration(2.0));
    if (client.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
      ros::spinOnce();
      
    }

    goal.command = "forward";
    goal.s = 1;
    goal.angle = 0;
    client.sendGoal(goal, &doneCb, &activeCb, &feedbackCb);
    client.waitForResult(ros::Duration(2.0));
    if (client.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
      ros::spinOnce();
      
    }
      return 0;
   }
