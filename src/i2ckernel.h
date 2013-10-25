#ifndef I2CKERNEL_H
#define I2CKERNEL_H

#include "i2cabstract.h"

class I2Ckernel : public I2Cabstract
{
public:
    void open(i2c_paramaters& parameters);
    void close();

    bool read(char address, char* bytes, int numBytes);
    bool write(char address, char* bytes, int numBytes);
};

#endif // I2CKERNEL_H
