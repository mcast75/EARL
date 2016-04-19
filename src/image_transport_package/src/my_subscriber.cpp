#include "ros/ros.h"            //ROS
#include <stdio.h>
#include <iostream>
#include <sensor_msgs/Image.h> 
#include <sensor_msgs/image_encodings.h>    //Converting ROS to OpenCV images
#include <cv_bridge/cv_bridge.h>            //Converting ROS to OpenCV images
#include <image_transport/image_transport.h>//Publishing and subscribing to images in ROS
#include <opencv2/imgproc/imgproc.hpp>      //Converting ROS to OpenCV images
#include "opencv2/core/core.hpp"            //OpenCV Stitching
#include "opencv2/features2d/features2d.hpp"//OpenCV Stitching
#include "opencv2/highgui/highgui.hpp"      //OpenCV Stitching 
#include "opencv2/calib3d/calib3d.hpp"      //OpenCV Stitching
#include "opencv2/imgproc/imgproc.hpp"      //OpenCV Stitching

using namespace cv;

  bool captured = false;
  sensor_msgs::ImageConstPtr cam1, cam2;
  cv_bridge::CvImagePtr ptrJ1, ptrJ2;
  Mat jetson1, jetson2;

void imageCallbackJ1(const sensor_msgs::ImageConstPtr& msg)
{

  
  cam1=msg;

  try
  {

    //cv::imshow("view", cv_bridge::toCvShare(msg, "bgr8")->image);
    captured = true;


  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}

void imageCallbackJ2(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {
    //cv::imshow("view", cv_bridge::toCvShare(msg, "bgr8")->image);
    //ptrJ1 = cv_bridge::toCvCopy(msg, "bgr8");

  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}


int main(int argc, char **argv)
{

ros::Rate loop_rate(1);

 ros::init(argc, argv, "image_listener");
  ros::NodeHandle nh;
  cv::namedWindow("view");
  cv::startWindowThread();
  image_transport::ImageTransport it(nh);

  image_transport::Subscriber sub_j1 = it.subscribe("videoJ1", 1, imageCallbackJ1);
  image_transport::Subscriber sub_j2 = it.subscribe("videoJ2", 1, imageCallbackJ2);

  while(ros::ok){


 if(captured ){

    cv::imshow("view", cv_bridge::toCvShare(cam1, "bgr8")->image);
}
 // imshow("J2_sub", jetson2);

ptrJ1.reset();

  ros::spinOnce();
 // cv::destroyWindow("J1_sub");
  //cv::destroyWindow("J2_sub");

 ros::spinOnce();

    loop_rate.sleep();


 }
}
