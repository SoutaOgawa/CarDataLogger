#ifndef MPU6050_H
#define MPU6050_H

#define MPU6050_ADDRESS_L 0x68
#define MPU6050_ADDRESS_H 0x69
#define MPU6050_ADDRESS MPU6050_ADDRESS_L

// 0x1A
#define MPU6050_DLPF_260 0b00000000
#define MPU6050_DLPF_184 0b00000001
#define MPU6050_DLPF_94 0b00000010
#define MPU6050_DLPF_44 0b00000011
#define MPU6050_DLPF_21 0b00000100
#define MPU6050_DLPF_10 0b00000101
#define MPU6050_DLPF_5 0b00000110

// 0x1B
#define MPU6050_AFS_SEL_2G 0b00000000
#define MPU6050_AFS_SEL_4G 0b00001000
#define MPU6050_AFS_SEL_8G 0b00010000
#define MPU6050_AFS_SEL_16G 0b00011000

// 0x1C
#define MPU6050_FS_SEL_G250DPS 0b00000000
#define MPU6050_FS_SEL_G500DPS 0b00001000
#define MPU6050_FS_SEL_G1000DPS 0b00010000
#define MPU6050_FS_SEL_G2000DPS 0b00011000

// 0x6B
#define MPU6050_RESET 0b10000000

enum class A_RANGE
{
    A2G,
    A4G,
    A8G,
    A16G
};

enum class G_RANGE
{
    G250DPS,
    G500DPS,
    G1000DPS,
    G2000DPS
};

enum class F_RANGE
{
    F260HZ,
    F184HZ,
    F94HZ,
    F44HZ,
    F21HZ,
    F10HZ,
    F5HZ
};

class MPU6050
{
public:
    void begin();
    void reset();
    void setAccelerationRange(int accelerationRange);
    void setGyroRange(int gyroRange);
    void setDLPF(int DLPF);

    void getAcceleration(int16_t *x, int16_t *y, int16_t *z);
    int16_t getAccelerationX();
    int16_t getAccelerationY();
    int16_t getAccelerationZ();

    void getGyro(int16_t *x, int16_t *y, int16_t *z);
    int16_t getGyroX();
    int16_t getGyroY();
    int16_t getGyroZ();

    void sendWire(uint8_t Register, uint8_t value);
    uint16_t readWire(uint8_t Register);
};

#endif
