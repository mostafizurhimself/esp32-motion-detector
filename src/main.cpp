#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

#define PIR_PIN 14

uint8_t receiverMAC[] = {0xC0, 0x5D, 0x89, 0xDD, 0x4E, 0x24}; // Replace with your receiver's MAC address

typedef struct Message
{
  bool motionDetected;
} Message;

void sendMotion(bool motion)
{
  Message data = {motion};
  esp_now_send(receiverMAC, (uint8_t *)&data, sizeof(data));
}

void onSent(const uint8_t *mac, esp_now_send_status_t status)
{
  Serial.print("Send status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void setup()
{
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("ESP-NOW init failed!");
    return;
  }

  esp_now_register_send_cb(onSent);
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverMAC, 6);
  peerInfo.channel = 1;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop()
{
  bool motion = digitalRead(PIR_PIN);
  sendMotion(motion);
  Serial.println(motion ? "🚨 Motion Detected" : "✅ No motion");
  delay(1000);
}
