#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(10, 9, 12, 11, 13); //oled psi connection
//arduino connection :10-D0,9-D1,12-RST,11-DC, 13-CS

static int btn = 3;
static int tempSensor = A0;
int sensorValue = 0;
float outValue;

void setup() {
  // assign default color value
  pinMode(A0,INPUT);
  pinMode(btn,INPUT_PULLUP);
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
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
  u8g.drawStr(10,32,"Hello World!");
}
void endPage(){
  u8g.setFont(u8g_font_10x20);
  u8g.drawStr(10,32,"Goodbye World!");
}
int x = 5;
void tempPage(){
  
  u8g.drawRFrame(2,2,124,60,3);
  u8g.drawRFrame(4,4,120,56,2);
  u8g.drawRFrame(40-x,20,60,20,2);
  u8g.drawRFrame(38-x,18,64,24,3);
  u8g.setFont(u8g_font_6x10);
  u8g.drawStr(10,13,"Current Temperature");
  u8g.setFont(u8g_font_10x20);
  u8g.drawStr(110-x,38,"C");
  u8g.setFont(u8g_font_5x7);
  u8g.drawStr(105-x,28,"o");
  u8g.setFont(u8g_font_4x6);
  u8g.drawStr(40-x-7,50+5,"C Jennifer Liang");
  u8g.drawCircle(41-x-7,47+5,4.5);
}

void sensorRead(){
  sensorValue = analogRead(tempSensor);
  outValue = sensorValue * 0.48876;
  u8g.setFont(u8g_font_10x20);
  u8g.setPrintPos(44,37);
  u8g.print(outValue);
}

int btnState = 0;
void bttn(){
  btnState = digitalRead(btn);
}

void loop() {
  // picture loop
  int btnState = digitalRead(btn);
  
  u8g.firstPage();
  do{
    bttn();
    if(btnState == 1){
      btnState++;
      btnState = btnState%3;
    }
    switch(btnState){
      case 0:
        startPage();
        break;
      case 1:
        tempPage();
        sensorRead();
        break;
      case 3:
        endPage();
        break;
      default:
        break;
    }
    
  } while(u8g.nextPage());
  delay(100);  
  
  }

