
/* Fill in information from your Blynk Template here */
/* Read more: https://bit.ly/BlynkInject */

#include "DHT.h"
#define DHTPIN 23  //pin DHT 23
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#define LDR_Pin 34
#define Buzzer_Pin 18
#define L_LED 16
#define R_LED 17

#define BLYNK_TEMPLATE_ID "TMPL6d8YMByw3"
#define BLYNK_TEMPLATE_NAME "Sensor"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_ESP32_DEV_MODULE
//#define USE_ESP32C3_DEV_MODULE
//#define USE_ESP32S2_DEV_KIT
//#define USE_WROVER_BOARD
//#define USE_TTGO_T7
//#define USE_TTGO_T_OI

int sw_led  = 0;
int sw_buzzer = 0;
int ldr = 0;
int LDR_value = 0;
float temp, humi;

#include "BlynkEdgent.h"

void setup()
{
  Serial.begin(115200);
  delay(100);
  pinMode(LDR_Pin, INPUT);
  pinMode(Buzzer_Pin, OUTPUT);
  pinMode(L_LED, OUTPUT);
  pinMode(R_LED, OUTPUT);

  dht.begin();
  BlynkEdgent.begin();
}

BLYNK_WRITE(V3) {
  sw_led = param.asInt();
}
BLYNK_WRITE(V4) {
  sw_buzzer = param.asInt();
}

void loop() {
  BlynkEdgent.run();
  LDR_value = analogRead(LDR_Pin);
  ldr = map(LDR_value, 0, 4095, 0, 500);
  Serial.print("LDR_value = "); 
  Serial.println(ldr);
  Blynk.virtualWrite(V0, ldr);

  ////// รับค่า  Sensor DHT
  humi = dht.readHumidity();     //รับค่าความชื้น
  temp = dht.readTemperature();  //รับค่าอุณหภูมิ
  Serial.print("Humidity :"); 
  Serial.println(humi);
  Serial.print("Temperature := "); 
  Serial.println(temp);
  Blynk.virtualWrite(V1, temp);
  Blynk.virtualWrite(V2, humi);
  
  if (sw_buzzer == 1) {
    digitalWrite(Buzzer_Pin, HIGH);
  } else if (sw_buzzer == 0) {
    digitalWrite(Buzzer_Pin, LOW);
  }
  if (sw_led == 1) {
    digitalWrite(L_LED, HIGH);
    digitalWrite(R_LED, HIGH);
  } else if (sw_led == 0) {
    digitalWrite(L_LED, LOW);
    digitalWrite(R_LED, LOW);
  }

  delay(1000);

}

