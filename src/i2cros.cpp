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

#include "i2cros.h"
#include "i2cmpsse.h"
#include "i2ckernel.h"

using namespace cereal_comm;

I2Cros::I2Cros(bool fast,char * linuxdevice){

    i2c_paramaters params;

    params.fast=fast;
    params.devicename=linuxdevice;

    i2c = new I2Ckernel();
    i2c->open(params);
}

I2Cros::I2Cros(bool fast,int vid,int pid,int interface,char * description,char * serial,int index){
    i2c_paramaters params;

    params.fast=fast;
    params.vid=vid;
    params.pid=pid;
    params.interface=interface;
    params.description=description;
    params.serial=serial;
    params.index=index;

    i2c = new I2Cmpsse();
    i2c->open(params);

}

I2Cros::~I2Cros(){
    i2c->close();
}

int I2Cros::read(uint8_t address, uint8_t* bytes, int numBytes){
    //TODO: return bytes read
    i2c->read(address, bytes, numBytes);
}

int I2Cros::write(uint8_t address, uint8_t* bytes, int numBytes){
    //TODO: return bytes written
    i2c->write(address, bytes, numBytes);
}


