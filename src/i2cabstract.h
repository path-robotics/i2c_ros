#ifndef I2CABSTRACT_H
#define I2CABSTRACT_H


typedef struct _parameters{
    bool fast;

    //libmpsse specific
    int vid;
    int pid;
    int interface;
    char * description;
    char * serial;
    int index;

    //linux I2CDEV specific
    char * devicename;

}i2c_paramaters;


class I2Cabstract
{
public:
    virtual void open(i2c_paramaters& parameters)=0;
    virtual void close()=0;

    virtual void read(unsigned char address, unsigned char* bytes, int numBytes)=0;
    virtual void write(unsigned char address, unsigned char* bytes, int numBytes)=0;
};

#endif // I2CABSTRACT_H
