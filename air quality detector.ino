#include "MQ135.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

MQ135 gasSensor = MQ135(A0);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int val;
int sensorPin = A1;

int button = 5;
bool lastButton = LOW;
bool currentButton = LOW;

int green_led = 6;
int yellow_led = 8;
int red_led = 7;

bool debounce(bool last){
  bool current = digitalRead(button);
  if(last != current){
    delay(5);
    current = digitalRead(button);
  }
  return current;
}

void setup(){
  Serial.begin(9600);
  Wire.begin();
  pinMode(sensorPin, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADRESS);
  display.clearDisplay();

  pinMode(button, OUTPUT);

  pinMode(green_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(red_led, OUTPUT);

  display.setTextSize(2);
  display.setTextColor(WHITE);

  display.setCursor(20,5);
  display.println("Welcome!");
  display.setCursor(30,43);
  display.println("Pasko");
  display.display();
  display.clearDisplay();

  digitalWrite(green_led, HIGH);
  delay(300);
  digitalWrite(green_led, LOW);
  
  digitalWrite(yellow_led, HIGH);
  delay(300);
  digitalWrite(yellow_led, LOW);

  digitalWrite(red_led, HIGH);
  delay(300);
  digitalWrite(red_led, LOW);

  delay(3000);
}

void loop(){
  val = analogRead(A0);
  Serial.print("analog value = ");
  Serial.println(val);
  float ppm = gasSensor.getPPM();
  Serial.print("ppm: ");
  Serial.println(ppm);

  display.setTextSize(2);
  display.setTextColor(WHITE);

  display.setCursor(20,43);
  display.println("CO2");
  display.setCursor(63,43);
  display.println("(PPM)");
  display.setTextSize(2);
  display.setCursor(28,5);
  display.println(ppm);

  display.display();
  display.clearDisplay();

  if (ppm <= 5000){
    digitalWrite(green_led, HIGH);
    digitalWrite(yellow_led, LOW);
    digitalWrite(red_led, LOW);
  } else if (ppm > 5000 && ppm < 10000){
    digitalWrite(yellow_led, HIGH);
    digitalWrite(green_led, LOW);
    digitalWrite(red_led, LOW);
  } else if (ppm > 10000){
    digitalWrite(red_led, HIGH);
    digitalWrite(green_led, LOW);
    digitalWrite(yellow_led, LOW);
  }
  delay(2500);
}