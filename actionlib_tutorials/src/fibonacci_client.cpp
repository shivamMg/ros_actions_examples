#include <string>

#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <actionlib_tutorials/FibonacciAction.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "test_fibonacci", ros::init_options::AnonymousName);

    std::string name = "fibonacci";
    if (argc >= 2)  // add namespace prefix
        name = std::string(argv[1]) + "/" + name;
    const std::string full_name = name;

    actionlib::SimpleActionClient<actionlib_tutorials::FibonacciAction> ac(full_name, true);

    ROS_INFO("Waiting for action server to start.");
    ac.waitForServer(ros::Duration(30));

    ROS_INFO("Action server started, sending goal.");
    actionlib_tutorials::FibonacciGoal goal;
    goal.order = 20;
    ac.sendGoal(goal);

    bool finished_before_timeout = ac.waitForResult(ros::Duration(30.0));

    if (finished_before_timeout)
    {
        actionlib::SimpleClientGoalState state = ac.getState();
        ROS_INFO("Action finished: %s",state.toString().c_str());
    }
    else
    {
        ROS_INFO("Action did not finish before the time out.");
    }
    return 0;
}
