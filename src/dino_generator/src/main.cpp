#include <iostream>
#include "ros/ros.h"
#include "dino_srv/dino_name.h"
#include "std_msgs/String.h"

const int NUM_SUFFIXIES = 10;
const int NUM_FACTS = 6;

ros::ServiceServer g_service;
ros::Publisher g_publisher;
ros::Subscriber g_subscriber;

std::string g_suffixies[NUM_SUFFIXIES] =
{
    "saurus", "raptor", "pteryx", "stacator",
    " Rex", "ceratops", "gnathus", "roides", "draco", "dromeus"
};

std::string g_facts[NUM_FACTS] =
{
    "belonged to the Brachiosauridae family and lived in the Lower Triassic!",
    "had two rows of teeth!", "could sleep during the flight!",
    "are the slowest dino in the world!", "see the world in the blue and yellow spectrum!",
    "died from cringe"
};

bool generateDinoName(dino_srv::dino_name::Request &req, dino_srv::dino_name::Response &res)
{

    // check the word and capitalize the first letter
    std::string dino_name = req.word.c_str();
    if(dino_name[0] >= 'a' && dino_name[0] <= 'z')
    {
        dino_name[0] = dino_name[0] - 32;
    }
    else if(dino_name[0] < 'A' || (dino_name[0] > 'Z' && dino_name[0] < 'a'))
    {
        ROS_ERROR("-- (!) Word to generate new species of dinosaur should start from a letter. Please try again.");
        return false;
    }

    // make random dino name
    int secs = ros::Time::now().toSec();
    srand(secs);
    int num_suf = rand() % NUM_SUFFIXIES;
    res.derived_dino_name = dino_name + g_suffixies[num_suf];
    ROS_INFO("New species of dinosaur : %s!", res.derived_dino_name.c_str());

    // publish to the topic
    std_msgs::String message;
    message.data = res.derived_dino_name;
    g_publisher.publish(message);
    return true;
}

void generateDinoFact(const std_msgs::String & message)
{
    int secs = ros::Time::now().toSec();
    srand(secs);
    int num_fact = rand() % NUM_FACTS;
    ROS_INFO("%s %s", message.data.c_str(), g_facts[num_fact].c_str());
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "dino_server");
    ros::NodeHandle nh;

    g_service = nh.advertiseService("generate_dino_name", generateDinoName); // cоздали сервис у сервера
    ROS_INFO("Servise to generate new species of dinosaur is ready! Write :"
            "\nrosservice call /generate_dino_name # (+ TAB)\n"
            "Then enter the word to generate dino species.");

    std::string topic_name;
    if(ros::param::get("/topic_name", topic_name))
    {
        g_publisher = nh.advertise<std_msgs::String>(topic_name, 10);
        g_subscriber = nh.subscribe(topic_name, 10, generateDinoFact);
    }
    else
    {
        ROS_ERROR("-- (!) Can't find parameter for topic_name in the launch file. Please try again.");
    }


    ros::spin();
}
