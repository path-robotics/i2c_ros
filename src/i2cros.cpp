#include "i2c_ros/i2cros.h"
#include "i2cabstract.h"
#include "i2cmpsse.h"
#include "i2ckernel.h"

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

void I2Cros::read(char address, char* bytes, int numBytes){
    i2c->read(address, bytes, numBytes);
}

void I2Cros::write(char address, char* bytes, int numBytes){
    i2c->write(address, bytes, numBytes);
}
