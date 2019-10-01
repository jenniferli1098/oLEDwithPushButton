#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(10, 9, 12, 11, 13); //oled psi connection
//arduino connection :10-D0,9-D1,12-RST,11-DC, 13-CS

static int tempSensor = A0;
static int lightSensor = A1;
int tsensorValue = 0;
float outValue;
int lsensorValue = 0;

void setup() {
  // assign default color value
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
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

void tempPage(){
  u8g.drawRFrame(2,2,124,60,3);
  u8g.drawRFrame(4,4,120,56,2);
  u8g.setFont(u8g_font_6x10);
  u8g.drawRFrame(8,8,51,33,2);
  u8g.drawStr(16,18,"Temp: ");
  u8g.drawStr(46,30,"C");
  u8g.setFont(u8g_font_4x6);
  u8g.drawCircle(42,22,1);
  u8g.setFont(u8g_font_4x6);
  u8g.drawStr(40,50+5,"C Jennifer Liang");
  u8g.drawCircle(41,47+5,4.5);
}

void lightPage(){
  u8g.drawRFrame(61,8,60,33,2);
  u8g.drawStr(64,18,"Lighting:");
}
void lsensorRead(){
  lsensorValue = analogRead(lightSensor);
  outValue = lsensorValue/256;
  u8g.setFont(u8g_font_6x10);
  u8g.setPrintPos(65,33);
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
      u8g.print("Bright");  
      break;
    default:
      break;
  }
}
void tsensorRead(){
  tsensorValue = analogRead(tempSensor);
  outValue = tsensorValue * 0.48876;
  u8g.setFont(u8g_font_6x10);
  u8g.setPrintPos(11,30);
  u8g.print(outValue);
}



void loop() {
  // picture loop
  
  while(1==1){
  u8g.firstPage();
  do{
    tempPage();
    tsensorRead();
    lightPage();
    lsensorRead();
    
  } while(u8g.nextPage());
  delay(100);
  }
  }

