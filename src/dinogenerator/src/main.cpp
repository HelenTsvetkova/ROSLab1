#include <iostream>
#include "ros/ros.h"
#include "dinosrv/dinoName.h"
#include "std_msgs/String.h"

#define NUMSUFFIXIES 10
#define NUMFACTS 6

ros::ServiceServer service;
ros::Publisher publisher;
ros::Subscriber subscriber;

std::string suffixies[NUMSUFFIXIES] = {
    "saurus", "raptor", "pteryx", "stacator",
    " Rex", "ceratops", "gnathus", "roides", "draco", "dromeus"
};

std::string facts[NUMFACTS] = {
    "belonged to the Brachiosauridae family and lived in the Lower Triassic!",
    "had two rows of teeth!", "could sleep during the flight!",
    "are the slowest dino in the world!", "see the world in the blue and yellow spectrum!",
    "died from cringe"
};

bool generateDinoName(dinosrv::dinoName::Request &req, dinosrv::dinoName::Response &res) {

    // check the word and capitalize the first letter
    std::string dinoName = req.word.c_str();
    if(dinoName[0] >= 'a' && dinoName[0] <= 'z') {
        dinoName[0] = dinoName[0] - 32;
    } else if(dinoName[0] < 'A' || (dinoName[0] > 'Z' && dinoName[0] < 'a')) {
        ROS_ERROR("-- (!) Word to generate new species of dinosaur should start from a letter. Please try again.");
        return false;
    }

    // make random dino name
    int secs = ros::Time::now().toSec();
    srand(secs);
    int numSuf = rand() % NUMSUFFIXIES;
    res.derived_dino_name = dinoName + suffixies[numSuf];
    ROS_INFO("New species of dinosaur : %s!", res.derived_dino_name.c_str());

    // publish to the topic
    std_msgs::String message;
    message.data = res.derived_dino_name;
    publisher.publish(message);
    return true;
}

void generateDinoFact(const std_msgs::String & message) {
    int secs = ros::Time::now().toSec();
    srand(secs);
    int numFact = rand() % NUMFACTS;
    ROS_INFO("%s %s", message.data.c_str(), facts[numFact].c_str());
}

int main(int argc, char** argv) {

    ros::init(argc, argv, "dinoserver");
    ros::NodeHandle nodeService;

    service = nodeService.advertiseService("generate_dino_name", generateDinoName); // cоздали сервис у сервера
    ROS_INFO("Servise to generate new species of dinosaur is ready! Write :"
            "\nrosservice call /generate_dino_name # (+ TAB)\n"
            "Then enter the word to generate dino species.");

    publisher = nodeService.advertise<std_msgs::String>("DinoSpecies", 10);
    subscriber = nodeService.subscribe("DinoSpecies", 10, generateDinoFact);

    ros::spin();
}
