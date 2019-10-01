#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(10, 9, 12, 11, 13); //oled psi connection
//arduino connection :10-D0,9-D1,12-RST,11-DC, 13-CS

static int tempSensor = A0;
static int lightSensor = A1;
static int trigger = A2;
static int echo = A3;

int tsensorValue = 0;
int lsensorValue = 0;
float distance;
int duration;
float outValue;

void setup() {
  // assign default color value
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo,INPUT);
  
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);       // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
}

void startPage(){
  u8g.setFont(u8g_font_10x20);
  u8g.drawStr(8,32,"Hello World!");
}
void endPage(){
  u8g.setFont(u8g_font_10x20);
  u8g.drawStr(20,32,"Goodbye!");
}
int x = 5;
//NORMPAGE is the template for all the pages
void normPage(){
  
  u8g.drawRFrame(2,2,124,60,3);
  u8g.drawRFrame(4,4,120,56,2);
  u8g.drawRFrame(40-x,20,60,20,2);
  u8g.drawRFrame(38-x,18,64,24,3);
  u8g.setFont(u8g_font_4x6);
  u8g.drawStr(40-x-7,50+5,"C Jennifer Liang");
  u8g.drawCircle(41-x-7,47+5,4.5);
}

void tempPage(){
  u8g.setFont(u8g_font_6x10);
  u8g.drawStr(10,13,"Current Temperature");
  u8g.setFont(u8g_font_10x20);
  u8g.drawStr(110-x,38,"C");
  u8g.setFont(u8g_font_5x7);
  u8g.drawStr(105-x,28,"o");
}
void lightPage(){
  u8g.setFont(u8g_font_6x10);
  u8g.drawStr(45,13,"Lighting");
}
void lsensorRead(){
  lsensorValue = analogRead(lightSensor);
  outValue = lsensorValue/256;
  u8g.setFont(u8g_font_10x20);
  u8g.setPrintPos(40,37);
  switch((int)(outValue)){
    case 3:
      u8g.print("Dark");
      break;
    case 2:
      u8g.print("Shady");
      break;
    case 1:
      u8g.print("Good");
      break;
    case 0:
      u8g.print("Light");  
      break;
    default:
      break;
  }
}
void tsensorRead(){
  tsensorValue = analogRead(tempSensor);
  outValue = tsensorValue * 0.48876;
  u8g.setFont(u8g_font_10x20);
  u8g.setPrintPos(40,37);
  u8g.print(outValue);
}

void disRead(){
  digitalWrite(trigger,LOW);
  delay(2);
  digitalWrite(trigger,HIGH);
  delay(10);
  digitalWrite(trigger,LOW);

  duration = pulseIn(echo,HIGH);
  distance = duration/5.8/10;
  u8g.setFont(u8g_font_10x20);
  u8g.setPrintPos(40,37);
  u8g.print(distance);
  u8g.setPrintPos(105,37);
  u8g.print("cm");
}
void disPage(){
  u8g.setFont(u8g_font_6x10);
  u8g.drawStr(40,13,"Distance");
}

int bbtn = 0;
void loop() {
        int i = 40;
        while(i > 3){       //discs shrink
          u8g.firstPage();
        do{
          u8g.drawDisc(64,32,i);
          u8g.drawDisc(0,0,i);
          u8g.drawDisc(0,64,i);
          u8g.drawDisc(128,0,i);
          u8g.drawDisc(128,64,i);
        } while(u8g.nextPage());
        delay(50);
        i-=3;
        }
        
        u8g.firstPage();
        do{
        startPage();
         
        } while(u8g.nextPage());
        delay(1000);
        u8g.firstPage();
        do{
          normPage();
          tempPage();
          tsensorRead();
         
        } while(u8g.nextPage());
        delay(2000);
        u8g.firstPage();
        do{
          normPage();
          lightPage();
          lsensorRead();
         
        } while(u8g.nextPage());
        delay(2000);
        u8g.firstPage();
        do{
          normPage();
          disPage();
          disRead();
        } while(u8g.nextPage());
        delay(2000);
        
        u8g.firstPage();
        do{
          endPage();
        } while(u8g.nextPage());
        delay(1000);
        
        i = 2;
        while(i < 50){          //discs grow
          u8g.firstPage();
        do{
          u8g.drawDisc(64,32,i);
          u8g.drawDisc(0,0,i);
          u8g.drawDisc(0,64,i);
          u8g.drawDisc(128,0,i);
          u8g.drawDisc(128,64,i);
        } while(u8g.nextPage());
        delay(50);
        i+=3;
        }
    }
  

  
  

