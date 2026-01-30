#include <Arduino.h>

#include <WiFi.h>
#include <esp_now.h>

esp_now_peer_info_t peerInfo;
uint8_t broadcastAddress[] = {0xE8, 0xF6, 0x0A, 0x38, 0xD5, 0xD4};

struct Vector3
{
    int16_t x, y, z;
};

struct payload
{
    Vector3 A, G;
};

payload recvData;

uint8_t sendData;

void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(&recvData, incomingData, sizeof(recvData));
    Serial.write((uint8_t*)&recvData.A, sizeof(recvData.A));
}

void onDataSent(const uint8_t *mac, esp_now_send_status_t status)
{
    Serial.print("\r\nLast Packet Send Status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void espnow_send(uint8_t data)
{
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &data, sizeof(data));
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

void setup()
{
    Serial.begin(115200);
    wifiSetup();
}

void loop()
{
}
