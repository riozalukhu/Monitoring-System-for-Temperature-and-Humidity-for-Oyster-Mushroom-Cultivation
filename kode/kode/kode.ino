#define BLYNK_PRINT Serial  
//#define BLYNK_TEMPLATE_ID   "YourTemplateID"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h> // Library untuk Sensor DHT11
DHT dht(0, DHT11); // Inisialisasi pin dht 11 dan jenis sensor yang  digunakan (DHT11)
char auth[] = "l4nxHbtCxgN8Fn6s4Wj--gLTlN_xNCqS";  // Kode Authentikasi yang didapatkan dari email
char ssid[] = "Galaxy A10s"; // Wifi / hotspot yang digunakan untuk esp8266
char pass[] = "1sampai7"; // password untuk wifi/hotspot yang digunakan
int lamp = 13; // deklarasi pin untuk lampu
int fan = 12; // deklarasi pin untuk kipas
int pompa = 14 ; // deklarasi pin untuk pompa

void suhu(float suhu1){    // void untuk mengecek suhu    
  if(suhu1 < 25.00 ){
    digitalWrite(lamp,LOW);
    delay(200000);
    if(suhu1 >= 25.00 && suhu1 <= 29.00){
       digitalWrite(lamp, HIGH);
    }
  }
  else if(suhu1 > 29.00){
    digitalWrite(fan,LOW);
    delay(100000);
    if(suhu1 <= 29.00){
       digitalWrite(fan,HIGH);
    }
  }
}
void kelembapan(float kelembapan1){ // void untuk mengecek kelembapan
    if(kelembapan1 < 60.00){
      digitalWrite(pompa,LOW);
      if(kelembapan1 >= 60.00 && kelembapan1 <= 90.00){
       digitalWrite(pompa,HIGH);
      }
    }
    else if(kelembapan1 > 90.00){
      digitalWrite(fan,LOW);
      if(kelembapan1 <=  90.00){
       digitalWrite(fan,HIGH);
      }
    }
}
void setup()
{
  // Debug console
  Serial.begin(9600);
  dht.begin(); // inisialisasi sensor dht 11 berjalan
  pinMode(lamp,OUTPUT); // set lampu sebagai output
  pinMode(fan,OUTPUT); // set kipas sebagai output
  pinMode(pompa,OUTPUT); // set pompa sebagai output
  Blynk.begin(auth, ssid, pass); // mengkoneksikan esp8266 ke aplikasi blynk
}
 
void loop()
{
  float s = dht.readTemperature(); // sensor dht 11 membaca suhu
  delay(10); // delay sebesar 10 milisecond
  float h = dht.readHumidity(); // sensor dht 11 membaca kelembapan
  Serial.print("Suhu: "); 
  Serial.print(s);   // menampilkan suhu yang dibaca ke terminal
  Serial.print("Kelembapan: ");
  Serial.print(h); // menampilkan kelembapan yang dibaca ke terminal
  Blynk.virtualWrite(V3, s); // menset pin virtual (V3) agar dapat menampilkan suhu ke aplikasi blynk
  Blynk.virtualWrite(V4, h); // menset pin Virtual (V4) agar dapat menampilkan kelembapan ke aplikasi blynk

  suhu(s); // memanggil void suhu
  kelembapan(h); // memanggil void kelembapan
  
  
  Blynk.run(); // inisialisasi blynk langsung berjalan
}

