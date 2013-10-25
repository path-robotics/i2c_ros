#ifndef I2CROS_H
#define I2CROS_H

class I2Cabstract;

class I2Cros
{
public:
    I2Cros(bool fast,char * linuxdevice);
    I2Cros(bool fast,int vid,int pid,int interface=0,char * description=0,char * serial=0,int index=-1);
    ~I2Cros();
    void read(char address, char* bytes, int numBytes);
    void write(char address, char* bytes, int numBytes);

private:
    I2Cabstract * i2c;
};

#endif // I2CROS_H
