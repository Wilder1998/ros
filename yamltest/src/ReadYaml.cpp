#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PointStamped.h>
#include "yaml-cpp/yaml.h"
#include <Eigen/Core>
#include <iostream>
#include <tf/tf.h>

std::vector<geometry_msgs::PoseStamped> PointsMap;

tf2::Quaternion myQuaternion;
void readyaml ( std::string filename){
    YAML::Node config = YAML::LoadFile(filename);
    std::vector<geometry_msgs::PoseStamped> PointsMap;
    if (config["waypoints"].IsSequence()){
        for (const auto& waypointNode : config["waypoints"]){
        geometry_msgs::PoseStamped PM;

        PM.pose.position.x = waypointNode["x"].as<double>();
        PM.pose.position.y = waypointNode["y"].as<double>();
        PM.pose.position.z = waypointNode["z"].as<double>();
        myQuaternion.setRPY(waypointNode["roll"].as<double>(), waypointNode["pitch"].as<double>(), waypointNode["yaw"].as<double>());
        PM.pose.orientation.w = myQuaternion.getW();
        PM.pose.orientation.x = myQuaternion.getX();
        PM.pose.orientation.y = myQuaternion.getY();
        PM.pose.orientation.z = myQuaternion.getZ();

        PointsMap.push_back(PM);
    }
    for (const auto& PM : PointsMap) {
            std::cout<< PM<< std::endl;
     }
   }
    else  {
        std::cerr << "Error: 'waypoints' is not a sequence in the YAML file." << std::endl;
    }
}

  int main(int argc, char **argv){
    ros::init(argc, argv ,"ReadYaml");
    ros::NodeHandle nh ;
   
    

    readyaml("/home/huqidi/catkin_ws/src/yamltest/test.yaml");

  }
