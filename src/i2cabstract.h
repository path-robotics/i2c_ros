#ifndef I2CABSTRACT_H
#define I2CABSTRACT_H

class I2Cabstract
{
public:
    virtual void open()=0;
    virtual void close()=0;

    virtual void read()=0;
    virtual void write()=0;
};

#endif // I2CABSTRACT_H
