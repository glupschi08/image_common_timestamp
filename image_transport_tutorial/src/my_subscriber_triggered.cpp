#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <iostream>




void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{

/*
  try
  {
    cv::imshow("view", cv_bridge::toCvShare(msg, "bgr8")->image);
    cv::waitKey(10);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }

*/

    cv_bridge::CvImagePtr cv_ptr;
    try {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::MONO8);   //TYPE_16UC1
    }
    catch (cv_bridge::Exception& e) {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }
    //get header info
    std_msgs::Header h = msg->header;
    std::cout<<h<<std::endl; //all at once
    std::cout<<h.stamp<<std::endl; //specific parts of it
    std::cout<<h.stamp.sec<<std::endl;
    std::cout<<h.stamp.nsec<<std::endl;
    std::cout<<h.seq<<std::endl;

}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "image_listener_triggered");
  ros::NodeHandle nh;
  cv::namedWindow("view_triggered", 400);//CV_WINDOW_AUTOSIZE
  //waitKey();
  cv::startWindowThread();
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("avt_camera_img", 1, imageCallback);
  ros::spin();
  cv::destroyWindow("view_triggered");
}
