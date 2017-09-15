#include <LiquidCrystal.h>
int sensorPin = 2; //hall effect
int counter = 0;
int ledpin = 13;
float start, finished;
float elapsed, time;
float revs;
float revolution;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
/*
* LCD RS pin to digital pin 8
* LCD Enable pin to digital pin 9
* LCD D0 pin to digital pin 1
* LCD D1 pin to digital pin 10
* LCD D2 pin to digital pin 11
* LCD D3 pin to digital pin 12
* LCD D4 pin to digital pin 4
* LCD D5 pin to digital pin 5
* LCD D6 pin to digital pin 6
* LCD D7 pin to digital pin 7
* LCD R/W pin to ground
* 10K resistor:
* ends to +5V and ground
* wiper to LCD VO pin (pin 3)
*/
void setup() 
{
  //setup lcd 
  lcd.begin(16, 2);
  lcd.print("  DRILL  SPEED");
  lcd.setCursor(9, 1);
  lcd.print(" RPM");
  
  // setup serial - diagnostics - port
  Serial.begin(115200);
  // setup pins
  pinMode(sensorPin, INPUT);
  pinMode(ledpin, OUTPUT);
  // setup interript
  attachInterrupt(0, RPM, RISING);
  start=millis();
  
}

void RPM()
{
  elapsed=millis()-start;
  start=millis();
} 

void loop() 
{
  int sensorValue = digitalRead(sensorPin);
  
  float revs = 60000/elapsed;
  float revolution = elapsed/1000;
  Serial.print(elapsed);
  Serial.print(" mS ");
  Serial.print(revolution);
  Serial.print(" SEC ");
  Serial.print(revs);
  Serial.print(" RPM ");
  Serial.print(millis() );
  Serial.print(" ");
  Serial.println(start);
  lcd.setCursor(3, 1);
  if (elapsed < 1200) {lcd.print(revs,0);}
    else {lcd.print(" 0    ");}
  if (sensorValue == 0) {digitalWrite (ledpin, HIGH);}
  else {digitalWrite(ledpin, LOW);  }
  
}
