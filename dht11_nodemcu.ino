#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>        // library NodeMCU/ESP8266
#include <BlynkSimpleEsp8266.h> // library Blynk
#include <DHT.h>                // library sensor DHT

#define DHTPIN 2          // Digital Pin yang digunakan; DHTPIN 2 = D4
#define DHTTYPE DHT11     // Sensor DHT 11
DHT dht(DHTPIN, DHTTYPE); 

// Dapatkan Auth Token dari email yang dikirimkan ke Blynk
char auth[] = "X3KHAOicAcc99a4rv3NhLVMDMpfDGubd";

// Masukkan nama Wifi dan Password
// Jika WiFi bersifat Open Network, set password menjadi ""
char ssid[] = "ZTEF660";
char pass[] = "N1kolaus";

BlynkTimer timer;

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  
  dht.begin();
  // Siapkan fungsi untuk dipanggil setiap detik
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
void sendSensor()
{
  float h = dht.readHumidity(); // membaca kelembapan udara
  float t = dht.readTemperature();  // membaca suhu dalam celcius
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Gagal membaca data dari sensor DHT!");
    return;
  }
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}
