#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(10, 9, 12, 11, 13); //oled psi connection
//arduino connection :10-D0,9-D1,12-RST,11-DC, 13-CS

static int tempSensor = A0;
static int lightSensor = A1;
static int trigger = A2;
static int echo = A3;
static int button = 3;

int tsensorValue = 0;
int lsensorValue = 0;
float distance;
int duration;
float outValue;
int draw_state = 0;

void setup() {
  // assign default color value
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo,INPUT);
  pinMode(button,INPUT_PULLUP);
  
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

//hello world
void startPage(){
  u8g.setFont(u8g_font_10x20);
  u8g.drawStr(8,38,"Hello World!");
  u8g.drawDisc(0,0,10);
  u8g.drawDisc(128,0,10);
  u8g.drawDisc(0,64,10);
  u8g.drawDisc(128,64,10);
}

//goodbye
void endPage(){
  u8g.setFont(u8g_font_10x20);
  u8g.drawStr(25,38,"Goodbye!");
  u8g.drawDisc(0,0,10);
  u8g.drawDisc(128,0,10);
  u8g.drawDisc(0,64,10);
  u8g.drawDisc(128,64,10);
}

//this is the template for the other pages
int x = 5;
void normPage(){
  
  u8g.drawRFrame(2,2,124,60,3);
  u8g.drawRFrame(4,4,120,56,2);
  u8g.drawRFrame(40-x,20,60,22,2);
  u8g.drawRFrame(38-x,18,64,26,3);
  u8g.setFont(u8g_font_4x6);
  u8g.drawStr(40-x-3,50+5,"C Jennifer Liang");
  u8g.drawCircle(41-x-3,47+5,4.5);
}


//temperature page and sensor
void tempPage(){
  u8g.setFont(u8g_font_6x10);
  u8g.drawStr(8,13,"Current Temperature");
  u8g.setFont(u8g_font_10x20);
  u8g.drawStr(110-x,38,"C");
  u8g.setFont(u8g_font_5x7);
  u8g.drawStr(105-x,28,"o");
}
void tsensorRead(){
  tsensorValue = analogRead(tempSensor);
  outValue = tsensorValue * 0.48876;
  u8g.setFont(u8g_font_10x20);
  u8g.setPrintPos(40,37);
  u8g.print(outValue);
}



//light page and sensor
void lightPage(){
  u8g.setFont(u8g_font_6x10);
  u8g.drawStr(45,14,"Lighting");
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

//ultrasonic page and sensor
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
  u8g.setPrintPos(102,37);
  u8g.print("cm");
}
void disPage(){
  u8g.setFont(u8g_font_6x10);
  u8g.drawStr(42,14,"Distance");
}

//different pages
void draw(){
  switch(draw_state){
    case 0:
      startPage();
      break;
    case 1:
      normPage();
      tempPage();
      tsensorRead();
      break;
    case 2:
      normPage();
      lightPage();
      lsensorRead();
      break;
    case 3:
      normPage();
      disPage();
      disRead();
      break;
    case 4:
      endPage();
      break;
    case 5:
      break;
    default:
      break;
  }
}


void loop() {

  u8g.firstPage();
     do{
         draw();
     } while(u8g.nextPage());
  delay(100);
  
  if(digitalRead(button) == LOW){
    draw_state++;
    delay(100);
  }
  draw_state%=6;
}
