#include <iostream>
#include "../MPU-master/src/MPU9250_Master_I2C.h"
#include <vector>

using std::vector;

class Magnetometer {
public:
    Magnetometer();
    ~Magnetometer();
    void ConfigMag(uint8_t);
    void ConfigGyro(uint8_t);
    void ConfigAccel(uint8_t);
    void GetMagnetValues(float&, float&, float&);
    void GetGyroValues(float&, float&, float&);
    void GetAccelValues(float&, float&, float&);
    void calibrateMagnetometer();
    bool ok = false;
private:
    MPU9250_Master_I2C* mpu;
    float args[3][3]; // args[0] = mag, args[1] = gyro, args[2] = accel
    void CurrectValues();
    float LowPassFilter();
    float HighPassFilter();
};