#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>


#define DHTPIN 4          
#define DHTTYPE DHT22
#define PIR_PIN 13        
#define MQ135_PIN 35      
#define LDR_PIN 34        
#define BUZZER_PIN 25     
#define RELAY_PIN 32     


Adafruit_SSD1306 display(128, 64, &Wire, -1);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  
  dht.begin();
  
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED gagal tersambung!"));
    for(;;);
  }
  
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.display();
}

void loop() {
  
  float temp = dht.readTemperature();
  int gasValue = analogRead(MQ135_PIN);
  int ldrValue = analogRead(LDR_PIN);
  int motion = digitalRead(PIR_PIN);

  if (motion == HIGH) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(RELAY_PIN, LOW);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(" MONITORING SAMPAH ");
  display.drawLine(0, 10, 128, 10, WHITE);
  
  display.setCursor(0, 15);
  display.printf("Temp : %.1f C\n", isnan(temp) ? 0 : temp);
  display.printf("Gas  : %d\n", gasValue);
  display.printf("LDR  : %d\n", ldrValue);
  display.printf("PIR  : %s\n", motion ? "TERDETEKSI!" : "AMAN");
  
  display.display();

  delay(1000);
}
