#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "WIFI ADI";          // Wi-Fi adı
const char* password = "WIFI SIFRE";    // Wi-Fi şifresi
const char* serverUrl = "http://IPV4 ADRESS/post_temperature.php"; // Sunucu URL'si

float temperature;

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("WiFi'ye bağlanılıyor...");
  }
  Serial.println("WiFi bağlantısı başarılı!");
}

void loop() {
  temperature = dht.readTemperature();
  if (isnan(temperature)) {
    Serial.println("Sıcaklık ölçülemiyor!");
    return;
  }

  Serial.print("Sıcaklık: ");
  Serial.print(temperature);
  Serial.println(" °C");

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);

    String postData = "temperature=" + String(temperature);
    int httpResponseCode = http.POST(postData);

    if (httpResponseCode > 0) {
      Serial.print("HTTP Yanıt Kodu: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("HTTP Hatası: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi'a yeniden bağlanılıyor...");
    WiFi.begin(ssid, password);
  }

  delay(5000);
}
