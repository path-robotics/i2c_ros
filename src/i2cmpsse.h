#ifndef I2CMPSSE_H
#define I2CMPSSE_H

#include "i2cabstract.h"

struct mpsse_context;


class I2Cmpsse : public I2Cabstract
{
public:
    I2Cmpsse();
protected:
    struct mpsse_context * i2c;

};

#endif // I2CMPSSE_H
