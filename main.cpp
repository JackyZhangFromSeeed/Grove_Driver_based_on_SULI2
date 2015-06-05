#include "mbed.h"
#include "suli2.h"

#include "grove_barometer_class.h"
#include "grove_digital_light_class.h"
#include "grove_accelerometer_class.h"
#include "grove_compass_class.h"
#include "grove_gyroscope_class.h"
#include "grove_fingerprint_class.h"
#include "grove_heartrate_class.h"
#include "grove_temp_hum_class.h"
#include "grove_moisture_class.h"

//only one MACRO can be set once time
#define GYROSCOPE
#define BAROMETER
#define TEMP_HUM
#define FINGER_PRINT
#define DIGITAL_LIGHT
#define ACCELERMETER
#define HEART_RATE
#define MOISTURE
#define COMPASS


Serial pc(USBTX, USBRX);


int main(void)
{
	pc.baud(115200);
	printf("\r\nhello\r\n\r\n");
	

#ifdef DIGITAL_LIGHT
	GroveDigitalLight digitallight(P0_27, P0_28);
	uint32_t lux;
	digitallight.write_setup();
	while(1)
	{
		suli_delay_ms(300);
		digitallight.read_lux(&lux);
		printf("lux = %d\r\n", lux);
	}
#endif

#ifdef GYROSCOPE
	GroveGyroscope gyroscope(P0_27, P0_28);
	float gx, gy, gz;
	gyroscope.write_setup();
	suli_delay_ms(10);
	gyroscope.write_zerocalibrate();
	while(1)
	{
		suli_delay_ms(300);
		gyroscope.read_gyroscope(&gx, &gy, &gz);
		printf("gx = %f, gy = %f, gz = %f\r\n", gx, gy, gz);
	}
#endif
	
#ifdef BAROMETER
	GroveBarometer barometer(P0_27, P0_28);
	float temperature1;
	long pressure;
	float altitude;
	barometer.write_setup();
	while(1)
	{
		suli_delay_ms(300);
		barometer.read_temperature(&temperature1);
		barometer.read_pressure(&pressure);
		barometer.read_altitude(&altitude);
		printf("temperature = %f, pressure = %ld, altitude = %f\r\n", temperature1, pressure, altitude);
	}
#endif

#ifdef TEMP_HUM
	GroveTempHum temphum(P2_3);
	float temperature2, humidity;
	temphum.write_setup(DHT11, 13);
	while(1)
	{
		suli_delay_ms(300);
		temphum.read_temperature(false, &temperature2);
		temphum.read_humidity(&humidity);
		printf("temperature = %f, humidity = %f\r\n", temperature2, humidity);
	}
#endif

#ifdef FINGER_PRINT
	GroveFingerprint fingerprint(P4_28, P4_29);
	bool rst;
	uint8_t res;
	fingerprint.write_setup();
	rst = fingerprint.verifyPassword();
	if (rst)
		printf("Found fingerprint sensor!\r\n");
	else
		printf("Did not find fingerprint sensor :(\r\n");
	while(1)
	{
		rst = fingerprint.getImage(&res);
		switch (res)
		{
			case FINGERPRINT_OK:
				printf("Image taken\r\n");
				break;
			case FINGERPRINT_NOFINGER:
				printf(".\r\n");
				break;
			case FINGERPRINT_PACKETRECIEVEERR:
				printf("Communication error\r\n");
				break;
			case FINGERPRINT_IMAGEFAIL:
				printf("Imaging error\r\n");
				break;
			default:
				printf("Unknown error\r\n");
				break;
		}
	}
#endif

#ifdef ACCELERMETER
	GroveAccelerometer accelermeter(P0_27, P0_28);
	float ax, ay, az;
	accelermeter.write_setup();
	while(1)
	{
		suli_delay_ms(300);
		accelermeter.read_accelerometer(&ax, &ay, &az);
		printf("ax = %f, ay = %f, az = %f\r\n", ax, ay, az);
	}
#endif

#ifdef HEART_RATE
	GroveHeartrate heartrate(P0_27, P0_28);
	uint8_t hrate;
	heartrate.write_setup();
	while(1)
	{
		suli_delay_ms(300);
		heartrate.read_heartrate(&hrate);
		printf("heartrate = %d\r\n", hrate);
	}
#endif

#ifdef MOISTURE
	GroveMoisture moisture(P0_23);
	uint16_t moi;
	moisture.write_setup();
	while(1)
	{
		suli_delay_ms(300);
		moisture.read_moisture(&moi);
		printf("moisture = %d\r\n", moi);
	}
#endif

#ifdef COMPASS
	GroveCompass compass(P0_27, P0_28);
	float cx, cy, cz, heading;
	compass.write_setup();
	while(1)
	{
		suli_delay_ms(300);
		compass.read_compass_xyz(&cx, &cy, &cz);
		compass.read_compass_heading(&heading);
		printf("cx = %f, cy = %f, cz = %f, heading = %f\r\n", cx, cy, cz, heading);
	}
#endif

	wait(1);
	for (;;)
	{

		wait(0.2);
	}
	
	return 0;
}
