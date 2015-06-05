


#ifndef __GROVE_ACCELERMETER_CLASS_H__
#define __GROVE_ACCELERMETER_CLASS_H__

#include "grove_accelerometer.h"

//GROVE_NAME        "Grove_Accelerometer"
//IF_TYPE           I2C

class GroveAccelerometer
{
public:
    GroveAccelerometer(int pinsda, int pinscl);
    bool write_setup(void);
    bool read_accelerometer(float *ax, float *ay, float *az);
    

private:
    I2C_T *i2c;
};

#endif
