#include "hal/hal.h"
#include <MPU6050_tockn.h>
#include "hal/HAL_Def.h"
#include "Wire.h"
#include "app/Accounts/Account_Master.h"

static MPU6050 mpu(Wire);;

void HAL::imu_init(void)
{
    Wire.begin(CONFIG_MPU_SDA, CONFIG_MPU_SCL, uint32_t(4000000));// Set I2C frequency to 400kHz
    mpu.begin();
    mpu.calcGyroOffsets(true);

    Serial.printf("imu init yaw offset : %0.2f\n", imu_get_yaw());
}

/*
 * roll --- x
 * yaw  --- y
 * pitch -- z
*/
void HAL::imu_update(void)
{
    // imu_info_t imuInfo;
    mpu.update();

    // imuInfo.ax = mpu.getAccX();
    // imuInfo.ay = mpu.getAccY();
    // imuInfo.az = mpu.getAccZ();
    // imuInfo.gx = mpu.getGyroX();
    // imuInfo.gy = mpu.getGyroY();
    // imuInfo.gz = mpu.getGyroZ();
    // imuInfo.mx = mpu.getMagX();
    // imuInfo.my = mpu.getMagY();
    // imuInfo.mz = mpu.getMagZ();
    // imuInfo.roll = mpu.getAngleX();
    // imuInfo.yaw = mpu.getAngleY();
    // imuInfo.pitch = mpu.getAngleZ();
    // log_d("yaw: %f\n", imuInfo.yaw);
    // AccountSystem::imu_commit(&imuInfo);
}

float HAL::imu_get_yaw(void)
{
    return mpu.getAngleY();
}
