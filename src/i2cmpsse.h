#ifndef I2CMPSSE_H
#define I2CMPSSE_H

#include "i2cabstract.h"

struct mpsse_context;


class I2Cmpsse : public I2Cabstract
{
public:

    void open(i2c_paramaters& parameters);
    void close();

    bool read(char address, char *bytes, int numBytes);
    bool write(char address, char* bytes, int numBytes);


protected:
    struct mpsse_context * i2c;

};

#endif // I2CMPSSE_H
