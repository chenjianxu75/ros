// This is the C++ version server file of the service demo
//

// 加载必要文件，注意Service_demo的加载方式
# include "ros/ros.h"
# include "service_full_name/summ_full_name.h"
# include "string"

// 定义请求处理函数
bool handle_function(service_full_name::summ_full_name::Request &req,
					service_full_name::summ_full_name::Response &res)
{
	// 此处我们对请求直接输出
	ROS_INFO("input names are  %s , %s, %s ", req.first_name.c_str(), req.second_name.c_str(), req.third_name.c_str());
	// 返回一个反馈，将response设置为"..."
	res.full_name = req.first_name + req.second_name + req.third_name;
	return true;
}

int main(int argc, char **argv)
{
	
	ros::init(argc, argv, "service_name");
	
	// 定义service的server端，service名称为“summ_full_name”，收到request请求之后传递给handle_function进行处理
	ros::NodeHandle nh;
	ros::ServiceServer service = nh.advertiseService("summ_full_name", handle_function);
	
	ros::spin();

	return 0;
}

