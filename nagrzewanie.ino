/* Piotr Graczyk Łukasz Aniszewski Dominik Domagalski 2019*/
#include<LiquidCrystal.h>
#include<stdlib.h>

LiquidCrystal lcd(16,17,23,25,27,29);

#define TEMP_0_PIN         13 //13-glowica lub 14-blat
int temp;
int i=0;
int u;
String a;
#define a -6.62901117834894e-07
#define b 0.00116735597539696
#define c -0.755618410394386
#define d 265.588180534288

  #define RAMPS_D10_PIN    10
#define HEATER_0_PIN       RAMPS_D10_PIN
  #define RAMPS_D8_PIN    8
  #define HEATER_BED_PIN   RAMPS_D8_PIN


double x;
double y;
double e;
double calka=0;


void setup() {
  // put your setup code here, to run once:
lcd.begin(20,4);
pinMode(HEATER_0_PIN,OUTPUT);
//pinMode(HEATER_BED_PIN,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
/*
if(i<50)
{
digitalWrite(HEATER_0_PIN,HIGH);
i++;

}
else
{
digitalWrite(HEATER_0_PIN,LOW);

}
*/


delay(100);
temp=analogRead(TEMP_0_PIN);
x=(double)temp;
y=a*x*x*x+b*x*x+c*x+d;
lcd.setCursor(0,0);
lcd.print(y,a);
e=200-y;
if(y<200)
{
calka=calka+e*0.1;
}
if(calka>50)
{
  calka=50;
  }
u=round(255/80*e+calka);
if(u>255)
{
  u=255;
  }
  if(u<0)
  {
    u=0;
    }
    analogWrite(RAMPS_D10_PIN,u);
    lcd.setCursor(0,1);
    lcd.print(255/80*e);
       lcd.setCursor(0,2);
    lcd.print(calka);
     lcd.setCursor(0,3);
    lcd.print(u);
}
