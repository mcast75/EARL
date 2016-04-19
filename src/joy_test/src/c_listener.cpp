#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float32.h"
#include <sensor_msgs/Joy.h>
#include <sstream>


using namespace ros;

int i = 0;
int c;

/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
// %Tag(CALLBACK)%
void chatterCallback(const sensor_msgs::Joy::ConstPtr& msg)
{


  if(msg->axes[4] == -1.0){
    i = 4;
    ROS_INFO("Right Trigger Pressed [RT]: Axis %d", i);
  

      if(msg->axes[0] == 1.0){
        i = 0;
        ROS_INFO("Left Analog Stick Right [L-Stick]: Axis %d", i);
        c = 6;
      }else if(msg->axes[0] == -1.0){
        i = 0;
        ROS_INFO("Left Analog Stick Left [L-Stick]: Axis %d", i);
        c = 4;
      }else{
        i = 3;
        ROS_INFO("Right Analog Stick: Axis %f", msg->axes[3]);
        c = msg->axes[3];

      }
   }

/*Button Commands*/
  /*A-Button*/
  if(msg->buttons[0] == 1){
    i = 0;
    ROS_INFO("A-Button Pressed Down [Green]: Button %d", i);
    c = 0;
  }
  /*B-Button*/
  if(msg->buttons[1] == 1){
    i = 1;
    ROS_INFO("B-Button Pressed Down [RED]: Button %d", i);
    c = 0;
  }
  /*X-Button*/
  if(msg->buttons[2] == 1){
    i = 2;
    ROS_INFO("X-Button Pressed Down [Blue]: Button %d", i);
   c = 0;
  }
  /*Y-Button*/
  if(msg->buttons[3] == 1){
    i = 3;
    ROS_INFO("Y-Button Pressed Down [Yellow]: Button %d", i);
   c = 0;
  }

}

int main(int argc, char **argv)
{


  init(argc, argv, "c_listener");
  NodeHandle n;//subscriber
  NodeHandle out; //publisher

  Publisher chatter_pub = out.advertise<std_msgs::Float32>("Direction", 1000);

  ros::Subscriber sub = n.subscribe("joy", 1000, chatterCallback);


  while (ros::ok())
  {

  

    //std_msgs::String msg;

    std_msgs::Float32 msg;
    std::stringstream ss;

    ss << c;

    msg.data = c;//ss.str();

    //ROS_INFO("%s", msg.data.c_str());

    chatter_pub.publish(msg);

    ros::spinOnce();
}

  return 0;
}
// %EndTag(FULLTEXT)%

