#include <Arduino.h>
#include <Wire.h>

#include <MPU6050.h>

void MPU6050::begin()
{
    MPU6050::reset();
}

void MPU6050::reset()
{
    MPU6050::sendWire(0x68, MPU6050_RESET);
}

void MPU6050::setDLPF(int DLPF)
{
    MPU6050::sendWire(0x1B, DLPF);
}

void MPU6050::setAccelerationRange(int accelerationRange)
{

    MPU6050::sendWire(0x1B, accelerationRange);
}
void MPU6050::setGyroRange(int gyroRange)
{
    MPU6050::sendWire(0x1C, gyroRange);
}

void MPU6050::getAcceleration(int16_t *x, int16_t *y, int16_t *z)
{
    *x = MPU6050::getAccelerationX();
    *y = MPU6050::getAccelerationY();
    *z = MPU6050::getAccelerationZ();
}

int16_t MPU6050::getAccelerationX()
{
    return MPU6050::readWire(0x3B);
}
int16_t MPU6050::getAccelerationY()
{
    return MPU6050::readWire(0x3D);
}
int16_t MPU6050::getAccelerationZ()
{
    return MPU6050::readWire(0x3F);
}

void MPU6050::getGyro(int16_t *x, int16_t *y, int16_t *z)
{
    *x = MPU6050::getGyroX();
    *y = MPU6050::getGyroY();
    *z = MPU6050::getGyroZ();
}

int16_t MPU6050::getGyroX()
{
    return MPU6050::readWire(0x43);
}
int16_t MPU6050::getGyroY()
{
    return MPU6050::readWire(0x45);
}
int16_t MPU6050::getGyroZ()
{
    return MPU6050::readWire(0x47);
}

void MPU6050::sendWire(uint8_t Register, uint8_t value)
{
    Wire.beginTransmission(MPU6050_ADDRESS);
    Wire.write(Register);
    Wire.write(value);
    Wire.endTransmission();
}

uint16_t MPU6050::readWire(uint8_t Register)
{
    Wire.beginTransmission(MPU6050_ADDRESS);
    Wire.write(Register);
    Wire.endTransmission();
    Wire.requestFrom(MPU6050_ADDRESS, 2);

    while (Wire.available() < 2);

    return Wire.read() << 8 | Wire.read();
}