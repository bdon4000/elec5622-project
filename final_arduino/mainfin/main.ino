#include "all.h"
 //TN屏可使用的变量有 BPM(int型)    Save_Data.UTCTime(char型)  Save_Data.altitude(char型)  f1(double型)   f2(double型)
unsigned long time_limit1=0;
unsigned long time_limit2=0;
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
void setup() 
{
  hall_Init();
  Pulse_Init();
  GPS_Init();
  SD_Init();
  tft.reset();
  uint16_t identifier = tft.readID();
  if(identifier==0x0101)
  identifier=0x9341;
  identifier=0x9481;
  tft.begin(identifier);
  tft.fillScreen(WHITE);
  tft.setCursor(0, 0);
  tft.setTextColor(BLUE);
  tft.setTextSize(3);
  tft.println("capdenc");
  tft.setCursor(0, 60);
  tft.println("speed");
  tft.setCursor(0,125);
  tft.print("Heart rate");
  tft.setCursor(0,190);
  tft.print("Altituade");
  tft.setCursor(0,255);
  tft.print("Current time");
  tft.setCursor(174,40);
  tft.println("Rad/min");
  tft.setCursor(174,101);
  tft.println("Km/h");
  tft.setCursor(174,163);
  tft.print("BPM");
  tft.setCursor(174,230);
}

void loop() 
{
  Pulse_Allot();
  GPS_Allot();
  if(millis()-time_limit1>5000)
  {
    GPS_SD_Write();
    PulseSensor_SD_Write();
    hall_SD_Write();
    time_limit1 = millis();
  }
  if(millis()-time_limit2>1000)
  {
  String capdence = String(f1);
  String speed1 = String(f2);
  String BPMs= String(BPM);
  //String altituade = String(Save_Data.altitude);
  tft.setTextColor(GREEN);  tft.setTextSize(6);
  tft.setCursor(0, 21);
  tft.fillRect(0,20,174,43,WHITE);
  tft.fillRect(0,84,174,43,WHITE);
  tft.fillRect(0,150,174,43,WHITE);
  tft.fillRect(0,215,174,43,WHITE);
  tft.fillRect(0,280,174,43,WHITE);
  tft.print(capdence);
  tft.setCursor(0,84);
  tft.println(speed1);
  tft.setCursor(0,150);
  tft.print(BPMs);
  tft.setCursor(0,215);
  tft.print('Save_Data.altitude');
  tft.setCursor(0,280);
  tft.print('Save_Data.UTCTime');
  time_limit2 = millis();
}
  if((millis()-time_count0)>3000)
  {f1=0;}
    if((millis()-time_count1)>3000)
  {f2=0;}
}
