#include <ros/ros.h>
#include "i2cros.h"
#include "i2c_ros/i2c.h"

#if LIBFTDI1 == 1
#include <libftdi1/ftdi.h>
#else
#include <ftdi.h>
#endif

cereal_comm::I2Cros * i2c;

bool i2c_operation(i2c_ros::i2c::Request &req,i2c_ros::i2c::Response &res)
{

    switch(req.operation){

    case i2c_ros::i2cRequest::READ:


        break;
    case i2c_ros::i2cRequest::WRITE:
        //i2c->write(req.address,req.data.)

        break;

    default:
        ROS_INFO("I2C_ROS - %s - unknown operation", __FUNCTION__);
        return false;

    }

    return false;
}


int main(int argc, char **argv){

    ros::init(argc, argv, "i2c_ros");

    ros::NodeHandle pn("~");

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
        pn.param<int>("ftdi_interface", ftdi_interface,INTERFACE_ANY);
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
