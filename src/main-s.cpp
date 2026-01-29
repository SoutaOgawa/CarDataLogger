#include <Arduino.h>

#include <WiFi.h>
#include <esp_now.h>

#include <MPU6050.h>
#include <Wire.h>

MPU6050 mpu;

esp_now_peer_info_t peerInfo;
uint8_t broadcastAddress[] = {0xE8, 0xF6, 0x0A, 0x37, 0x03, 0x08};

/*
void wifiSetup()
{
    WiFi.mode(WIFI_STA);
    esp_now_init();

    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    esp_now_add_peer(&peerInfo);

    esp_now_register_recv_cb(esp_now_recv_cb_t(onDataRecv));
    esp_now_register_send_cb(esp_now_send_cb_t(onDataSent));
}



void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    //memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
    Serial.print("Bytes received: ");
    Serial.println(len);
}

void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    Serial.print("\r\nLast Packet Send Status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
*/

void mpuSetup() {
    mpu.begin();
    mpu.setAccelerationRange(MPU6050_AFS_SEL_2G);
    mpu.setGyroRange(MPU6050_FS_SEL_G250DPS);
    mpu.setDLPF(MPU6050_DLPF_10);

}

void setup()
{
    Wire.begin(6,7);
    Serial.begin(115200);
    delay(1000);
    mpuSetup();
}

void loop()
{
    Serial.print(mpu.getAccelerationX());
}
