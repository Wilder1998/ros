#include"include/pathplanfsm.h"
#include<ros/ros.h>
#include<geometry_msgs/PoseStamped.h>
#include<mavros_msgs/CommandBool.h>
#include<mavros_msgs/SetMode.h>
#include<mavros_msgs/State.h>

mavros_msgs::State current_state;
void state_cb(const mavros_msgs::State::ConstPtr& msg){
    current_state = *msg;
}

static Eigen::Vector3d pos_t;
void poseCallback(const geometry_msgs::PoseStampedConstPtr& msg){
pos_t(0) = msg->pose.position.x, pos_t(1) = msg->pose.position.y, pos_t(2) = msg->pose.position.z;
}

int main (int argc, char **argv){
    ros::init(argc, argv, "PathPlanFSM");
    ros::NodeHandle nh;
    ros::Subscriber current_pose_sub = nh.subscribe<geometry_msgs::PoseStamped>("mavros/local_position/pose", 10, poseCallback);
    ros::Subscriber state_sub = nh.subscribe<mavros_msgs::State>("mavros/state", 10, state_cb);
    ros::Publisher local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local", 10);
    ros::ServiceClient arming_client = nh.serviceClient<mavros_msgs::CommandBool>("mavros/cmd/arming");   
    ros::ServiceClient set_mode_client = nh.serviceClient<mavros_msgs::SetMode>("mavros/set_mode");
    
    ros::Rate rate(20.0);

    while(ros::ok() && !current_state.connected){
            ros::spinOnce();
            rate.sleep();
        }

}