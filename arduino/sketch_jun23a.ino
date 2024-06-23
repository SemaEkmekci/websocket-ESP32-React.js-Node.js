#include <WiFi.h>
#include <WebSocketsClient.h>

// Wi-Fi bilgileri
const char* ssid = "TURKSAT-KABLONET-A41A-2.4G";
const char* password = "dce35953";

// WebSocket sunucu bilgileri
const char* websocket_server_host = "192.168.0.22"; // Örneğin: "192.168.1.100"
const uint16_t websocket_server_port = 8080;

WebSocketsClient webSocket;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi!");

  webSocket.begin(websocket_server_host, websocket_server_port, "/");

  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();

  // Her 5 saniyede bir mesaj gönder
  static unsigned long lastTime = 0;
  if (millis() - lastTime > 5000) {
    lastTime = millis();
    webSocket.sendTXT("Hello from ESP32");
  }
}

void webSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.println("WebSocket Disconnected!");
      break;
    case WStype_CONNECTED:
      Serial.println("WebSocket Connected!");
      break;
    case WStype_TEXT:
      Serial.printf("Received: %s\n", payload);
      break;
  }
}
