#include <mpsse.h>
#include "i2cmpsse.h"
#include "i2cabstract.h"
#include <ros/ros.h>


void I2Cmpsse::open(i2c_paramaters& parameters){

    if (parameters.fast){

        if((i2c = Open(parameters.vid,parameters.pid,I2C, FOUR_HUNDRED_KHZ,MSB,parameters.interface,parameters.description,parameters.serial)) != NULL && i2c->open)
        {
            ROS_INFO("I2C_ROS - %s - %s initialized at %dHz (I2C)", __FUNCTION__, GetDescription(i2c), GetClock(i2c));
        }else{
            ROS_FATAL("I2C_ROS - %s - Failed to initialize MPSSE: %s", __FUNCTION__,ErrorString(i2c));
            Close(i2c);
            ROS_BREAK();
        }
    }
    else{
        if((i2c = Open(parameters.vid,parameters.pid,I2C, ONE_HUNDRED_KHZ,MSB,parameters.interface,parameters.description,parameters.serial)) != NULL && i2c->open)
        {
            ROS_INFO("I2C_ROS - %s - %s initialized at %dHz (I2C)", __FUNCTION__, GetDescription(i2c), GetClock(i2c));
        }else{
            ROS_FATAL("I2C_ROS - %s - Failed to initialize MPSSE: %s", __FUNCTION__,ErrorString(i2c));
            Close(i2c);
            ROS_BREAK();
        }
    }

}

void I2Cmpsse::close(){
    Close(i2c);
}

bool I2Cmpsse::read(char address, char* bytes, int numBytes){

    Start(i2c);

    address=(address<<1)|1; //shift to 7bit address and add read bit

    Write(i2c,&address,1);

    ROS_DEBUG("I2C_ROS - %s - GetACK= %d", __FUNCTION__,GetAck(i2c));

    char * buffer = NULL;
    buffer=Read(i2c,numBytes);
    memcpy(bytes,buffer,numBytes);
    free(buffer);
    Stop(i2c);

    //TODO: check GetACK use
    return true;

}


bool I2Cmpsse::write(char address, char* bytes, int numBytes){


    address<<=1;  //shift to 7bit address
    Start(i2c);
    Write(i2c,&address,1);

    ROS_DEBUG("I2C_ROS - %s - GetACK= %d", __FUNCTION__,GetAck(i2c));

    Write(i2c,bytes,numBytes);
    Stop(i2c);

    //TODO: check GetACK use
    return true;


}
