#include <Arduino.h>

#include <WiFi.h>
#include <esp_now.h>

#include <MPU6050.h>
#include <Wire.h>

MPU6050 mpu;

esp_now_peer_info_t peerInfo;
uint8_t broadcastAddress[] = {0xE8, 0xF6, 0x0A, 0x37, 0x03, 0x08};

struct Vector3
{
    int16_t x, y, z;
};

struct payload
{
    Vector3 A, G;
};

payload sendData;

uint8_t recvData;

void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(&recvData, incomingData, sizeof(recvData));
    Serial.print("Bytes received: ");
    Serial.println(len);
}

void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    Serial.print("\r\nLast Packet Send Status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void transmit(payload todata)
{
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&todata, sizeof(todata));

    if (result == ESP_OK)
    {
        Serial.println("Sent with success");
    }
    else
    {
        Serial.println("Error sending the data");
    }
}

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

void mpuSetup()
{
    mpu.begin();
    mpu.setAccelerationRange(MPU6050_AFS_SEL_2G);
    mpu.setGyroRange(MPU6050_FS_SEL_G250DPS);
    mpu.setDLPF(MPU6050_DLPF_184);
}

void setup()
{
    Wire.begin(6, 7);
    Serial.begin(115200);
    delay(1000);
    mpuSetup();
    wifiSetup();
}

void loop()
{
    mpu.getAcceleration(&sendData.A.x, &sendData.A.y, &sendData.A.z);
    transmit(sendData);
    Serial.println(sendData.A.x);
    delay(1000);
}
