#include <iostream>
#include "ros/ros.h"
#include "dinosrv/dinoName.h"
#include "std_msgs/String.h"

ros::ServiceServer service;
ros::Publisher publisher;
ros::Subscriber subscriber;

std::string suffixies[10] = {
    "saurus", "raptor", "pteryx", "stacator",
    " Rex", "ceratops", "gnathus", "roides", "draco", "dromeus"
};

bool generateDinoName(dinosrv::dinoName::Request &req, dinosrv::dinoName::Response &res) {

    res.derived_dino_name = req.word + suffixies[4];
    ROS_INFO("New species of dinosaur : %s!\n", res.derived_dino_name.c_str());

    std_msgs::String message;
    message.data = res.derived_dino_name;
    publisher.publish(message);

    ros::spinOnce();

    return true;
}

void generateDinoFact(const std_msgs::String & message) {
    ROS_INFO("%s belonged to the Brachiosauridae family and lived in the Lower Triassic!", message.data.c_str());
}

int main(int argc, char** argv) {

    ros::init(argc, argv, "dinoserver");
    ros::NodeHandle nodeService;
    ros::NodeHandle nodePublisher;
    ros::NodeHandle nodeSubscriber;

    service = nodeService.advertiseService("generate_dino_name", generateDinoName); // cоздали сервис у сервера
    ROS_INFO("Servise to generate new species of dinosaur is ready!");

    publisher = nodePublisher.advertise<std_msgs::String>("DinoSpecies", 10);
    ROS_INFO("Publisher is ready!");

    subscriber = nodeSubscriber.subscribe("DinoSpecies", 10, generateDinoFact);
    ROS_INFO("Subscriber is ready!");

    ros::spin();
}
