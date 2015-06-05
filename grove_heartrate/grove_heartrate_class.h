


#ifndef __GROVE_HEARTRATE_CLASS_H__
#define __GROVE_HEARTRATE_CLASS_H__

#include "grove_heartrate.h"

//GROVE_NAME        "Grove_Heartrate"
//IF_TYPE           I2C

class GroveHeartrate
{
public:
    GroveHeartrate(int pinsda, int pinscl);
	bool write_setup(void);
	bool read_heartrate(uint8_t *lux);
    
    

private:
    I2C_T *i2c;
};

#endif
