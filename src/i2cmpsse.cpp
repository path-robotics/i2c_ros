/*********************************************************************
*
* Software License Agreement (BSD License)
*
*  Copyright (c) 2013, ISR University of Coimbra.
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the ISR University of Coimbra nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*
* Author: Bruno Gouveia on 10/28/2013
*********************************************************************/
#include <ros/ros.h>
#include "i2cmpsse.h"
extern "C"{
#include <mpsse.h>
}

using namespace cereal_comm;

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

int I2Cmpsse::read(uint8_t address, uint8_t* bytes, int numBytes){

    Start(i2c);

    //ROS_INFO("I2C_ROS - %s - Address : %x", __FUNCTION__,address);

    address=(address<<1)|1; //shift to 7bit address and add read bit

    Write(i2c,(char*)(&address),1);


    //ROS_INFO("I2C_ROS - %s - GetACK= %d", __FUNCTION__,GetAck(i2c));

    char * buffer = NULL;
    buffer=Read(i2c,numBytes);

    /*ROS_INFO("#########buffer######");
    for (int i=0;i<numBytes;i++){
        ROS_INFO("buffer[%d]: %x",i,buffer[i]);
    }
    ROS_INFO("#######################");*/

    memcpy(bytes,buffer,numBytes);
    free(buffer);
    Stop(i2c);

    //TODO: check GetACK use and return bytes read

    return 1;

}


int I2Cmpsse::write(uint8_t address, uint8_t* bytes, int numBytes){


    address<<=1;  //shift to 7bit address
    Start(i2c);
    Write(i2c,(char*)(&address),1);

    //ROS_INFO("I2C_ROS - %s - GetACK= %d", __FUNCTION__,GetAck(i2c));

    Write(i2c,(char*)(bytes),numBytes);
    Stop(i2c);

    //TODO: check GetACK use and return bytes written
    return 1;


}
