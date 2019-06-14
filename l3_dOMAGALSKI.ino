/* Piotr Graczyk Łukasz Aniszewski Dominik Domagalski 2019*/
#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#define X_MIN_PIN           3
#ifndef X_MAX_PIN
#define X_MAX_PIN         2
#endif
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19

#include<stdlib.h>

bool odpowiedz=0;         //czy mam odpowiedziec do matlaba
int liczba_krokow = 0;
bool kieruneka = 1,kierunekb=1,kierunekc=1;
String a;
int kroka = 0, krokb = 0, krokc = 0;
void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  pinMode(X_ENABLE_PIN, OUTPUT);
  digitalWrite(X_ENABLE_PIN, 0);
  pinMode(X_DIR_PIN, OUTPUT);
  digitalWrite(X_DIR_PIN, LOW);
  pinMode(X_STEP_PIN, OUTPUT);

  pinMode(Y_ENABLE_PIN, OUTPUT);
  digitalWrite(Y_ENABLE_PIN, 0);
  pinMode(Y_DIR_PIN, OUTPUT);
  digitalWrite(Y_DIR_PIN, LOW);
  pinMode(Y_STEP_PIN, OUTPUT);

  pinMode(Z_ENABLE_PIN, OUTPUT);
  digitalWrite(Z_ENABLE_PIN, 0);
  pinMode(Z_DIR_PIN, OUTPUT);
  digitalWrite(Z_DIR_PIN, LOW);
  pinMode(Z_STEP_PIN, OUTPUT);

  pinMode(X_MAX_PIN, INPUT_PULLUP);
  pinMode(Y_MAX_PIN, INPUT_PULLUP);
  pinMode(Z_MAX_PIN, INPUT_PULLUP);

}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0)
  {
    a = Serial.readStringUntil('\n');                                 //czytanie z klawiatury
    sscanf(a.c_str(), "a %d b %d c %d", &kroka, &krokb, &krokc);
    odpowiedz=1;
   // Serial.println(kroka);
  //  Serial.println(krokb);
  //  Serial.println(krokc);
    kieruneka=kroka<0;
  digitalWrite(X_DIR_PIN, kieruneka);
kroka=abs(kroka);

kierunekb=krokb<0;
  digitalWrite(Y_DIR_PIN, kierunekb);
krokb=abs(krokb);

kierunekc=krokc<0;
  digitalWrite(Z_DIR_PIN, kierunekc);
krokc=abs(krokc);


  }





  if ((digitalRead(X_MAX_PIN) == 0 or kieruneka == 1)&&kroka>0)             //oblsuga krancowek i wlaczenie 
  {
    digitalWrite(X_STEP_PIN, HIGH);
    kroka--;
  }
  if ((digitalRead(Y_MAX_PIN) == 0 or kierunekb == 1)&&krokb>0)
  {
    digitalWrite(Y_STEP_PIN, HIGH);
    krokb--;
  }
  if ((digitalRead(Z_MAX_PIN) == 0 or kierunekc == 1)&&krokc>0)
  {
    digitalWrite(Z_STEP_PIN, HIGH);
    krokc--;
  }

  delay(1);
  digitalWrite(X_STEP_PIN, LOW);
  digitalWrite(Y_STEP_PIN, LOW);
  digitalWrite(Z_STEP_PIN, LOW);
  delay(1);

  if (kroka==0 && krokb==0 && krokc==0 && odpowiedz==1)
{
  Serial.println("ok");
  odpowiedz=0;
  }
  /*if (liczba_krokow > 300) {
    kierunek = !kierunek;           //zmiana kierunku
    digitalWrite(X_DIR_PIN, kierunek);
    digitalWrite(Y_DIR_PIN, kierunek);
    digitalWrite(Z_DIR_PIN, kierunek);
    liczba_krokow = 0;
    //Serial.println(digitalRead(X_MAX_PIN));
  }
*/
  
}
