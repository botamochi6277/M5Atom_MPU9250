#include "M5Atom.h"
#include "MPU9250.h"

float accX = 0, accY = 0, accZ = 0;
float gyroX = 0, gyroY = 0, gyroZ = 0;
float temp = 0;
bool IMU6886Flag = false;

bool IMU9250Flag = false;
MPU9250 imu0; // 0x68

void setup()
{
    // M5.begin for M5Atom:
    // M5.begin(bool SerialEnable = true, bool I2CEnable = true, bool DisplayEnable = false)

    // M5Atom use pin 25 and 21 to I2C when I2CEnable is true.
    // https://github.com/m5stack/M5Atom/blob/master/src/M5Atom.cpp#L16

    M5.begin(true, false, true);

    if (M5.IMU.Init() != 0)
        IMU6886Flag = false;
    else
        IMU6886Flag = true;

    imu0.setAddress(0x68);
    IMU9250Flag = imu0.init();

    if (!IMU9250Flag)
    {
        // Fail to connect
        // red lamp
        M5.dis.clear();
        M5.dis.drawpix(0, CRGB(255, 0, 0));
        Serial.printf("ERROR: Fail to connect MPU9250");
    }
    else
    {
        M5.dis.drawpix(0, CRGB(0, 255, 0));
    }
}

void loop()
{
    if (IMU9250Flag == true)
    {
        imu0.update(false);
        Serial.printf("%.2f,%.2f,%.2f o/s \r\n", imu0.gx, imu0.gy, imu0.gz);
        Serial.printf("%.2f,%.2f,%.2f mg\r\n", imu0.ax * 1000, imu0.ay * 1000, imu0.az * 1000);
        // Serial.printf("Temperature : %.2f C \r\n", temp);
    }
    M5.update();
    delay(500);
}
