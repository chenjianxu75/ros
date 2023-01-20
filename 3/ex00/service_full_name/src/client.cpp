// This is client of the service demo
// 包含必要文件，注意Service文件的包含方式，我们定义的srv文件为Greeting.srv,在包含时需要写成Greeting.h
# include "ros/ros.h"
# include "service_full_name/summ_full_name.h"

int main(int argc, char **argv)
{

	if (argc != 4)
	{
		ROS_INFO("usage: add names.");
		return 1;
	}
	
	ros::init(argc, argv, "client_name");
	
	// 定义service客户端，service名字为“summ_full_name”，service类型为Service_demo
	ros::NodeHandle nh;
	ros::ServiceClient client = nh.serviceClient<service_full_name::summ_full_name>("summ_full_name");
	service_full_name::summ_full_name srv;
	srv.request.first_name = argv[1];
	srv.request.second_name = argv[2];
	srv.request.third_name = argv[3];

	if (client.call(srv))
	{
		ROS_INFO("Full name is : %s", srv.response.full_name.c_str());
	}
	else
	{
		ROS_ERROR("Failed to call service Service_demo");
		return 1;
	}
	return 0;
}
