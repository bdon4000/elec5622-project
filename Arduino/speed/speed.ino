int pin = 2; //D2
unsigned long duration=0; 
int i = 0;
void setup()
{
Serial.begin(9600); 
pinMode(pin, INPUT); 
delay(5000);
Serial.println("begin"); 
}


void loop()
{
  duration=0;
  for(i=0;i<5;i++){
  duration += pulseIn(pin, HIGH); 
  duration += pulseIn(pin, LOW); 
  }
  Serial.println(duration);
  duration = duration/5;
  Serial.println(duration);
  duration=1000000/duration;
  Serial.print(" f is "); 
  Serial.print(duration); 
  Serial.println(" HZ"); 
  duration = duration*60*3.14*70/(3600*100000);
  Serial.print(" v is "); 
  Serial.print(duration); 
  Serial.println(" kph"); 
  
  delay(2000);
}
