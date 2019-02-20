#include "mgm.hpp"

Magnetometer::Magnetometer() {

    wiringPiSetup();
    mpu = new MPU9250_Master_I2C(MPU9250_Master_I2C::AFS_2G,
        MPU9250_Master_I2C::GFS_250DPS, 
        MPU9250_Master_I2C::MFS_16BITS, 
        MPU9250_Master_I2C::M_8Hz);
    // Start the MPU9250
    switch (mpu->begin()) {

        case MPUIMU::ERROR_IMU_ID:
            printf("Bad IMU device ID!\n");
            break;
        case MPUIMU::ERROR_MAG_ID:
            printf("Bad magnetometer device ID!\n");
            break;
        case MPUIMU::ERROR_SELFTEST:
            printf("Failed self test!\n");
            break;
        default:
            printf("MPU9250 online!\n");
            ok = true;
            break;
    }

}

Magnetometer::~Magnetometer() {
    delete mpu; 
}

void Magnetometer::calibrateMagnetometer() {
    mpu->calibrateMagnetometer();
}

void Magnetometer::GetMagnetValues(float& mx, float& my, float& mz) {
    mpu->readMagnetometer(mx, my, mz);
    args[0][0] = mx;
    args[0][1] = my;
    args[0][2] = mz;
}

void Magnetometer::GetGyroValues(float& gx, float& gy, float& gz) {
    mpu->readGyrometer(gx, gy, gz);
    args[1][0] = gx;
    args[1][1] = gy;
    args[1][2] = gz;
}

void Magnetometer::GetAccelValues(float& ax, float& ay, float& az) {
    mpu->readAccelerometer(ax, ay, az);
    args[2][0] = ax;
    args[2][1] = ay;
    args[2][2] = az;
}