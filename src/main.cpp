#include <ros/ros.h>
extern "C"{
#include <mpsse.h>
}
#include "i2cros.h"
#include "i2c_ros/i2c.h"


bool i2c_operation(i2c_ros::i2c::Request &req,i2c_ros::i2c::Response &res)
{
  /*res.sum = req.a + req.b;
  ROS_INFO("request: x=%ld, y=%ld", (long int)req.a, (long int)req.b);
  ROS_INFO("sending back response: [%ld]", (long int)res.sum);*/

  return true;
}


int main(int argc, char **argv){

    ros::init(argc, argv, "i2c_ros");

    ros::NodeHandle pn("~");

    cereal_comm::I2Cros * i2c;

    /****
        * Hardware Parameters
        ****/

    //linux device parameter
    std::string devicename;

    //ftdi parameters
    int vid;
    int pid;
    int ftdi_interface;
    std::string usb_description;
    std::string usb_serial;
    int adapter_index;

    //using linux module for i2c
    if (pn.getParam("devicename", devicename))
    {
        i2c = new cereal_comm::I2Cros(true,(char*)devicename.c_str());
        ROS_INFO("i2c_ros node - %s - Successfully connected using %s !",__FUNCTION__,devicename.c_str());
    }
    else //using ftdi
    {

        pn.param<int>("usb_vid", vid,0x0403);
        pn.param<int>("usb_pid", pid ,0x6014);
        pn.param<int>("ftdi_interface", ftdi_interface,IFACE_ANY);
        pn.param<std::string>("usb_descriprequesttion",usb_description,"");
        pn.param<std::string>("usb_serial",usb_serial,"");
        pn.param<int>("adapter_index",adapter_index ,-1);

        char * c_usb_description = (usb_description.size()>0)?(char*)usb_description.c_str():NULL;
        char * c_usb_serial = (usb_serial.size()>0)?(char*)usb_serial.c_str():NULL;

        i2c = new cereal_comm::I2Cros(true,vid,pid,ftdi_interface,c_usb_description,c_usb_serial,adapter_index);

        ROS_INFO("i2c_ros node - %s - Successfully connected using FTDI !",__FUNCTION__);

    }

    ros::ServiceServer service = pn.advertiseService("i2c_operation", i2c_operation);
    ros::spin();
    return 0;


}
