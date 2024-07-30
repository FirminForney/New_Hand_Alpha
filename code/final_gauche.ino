/*Ce projet est sous licence [Creative Commons Attribution-NonCommercial 4.0 International](https://creativecommons.org/licenses/by-nc/4.0/).*/

#include <Servo.h>


int angle = 180;
int bp1;
int bp2;

int etat = 1;
int mode = 0;

Servo doigt2;
Servo doigt1;
Servo servo3;
Servo doigt3;

void setup() {
 doigt2.attach(10);
 doigt1.attach(9);
 servo3.attach(6);
 doigt3.attach(5);
 Serial.begin(9600);
 pinMode(A0, INPUT_PULLUP);
 pinMode(A1, INPUT_PULLUP);
 ouvre();
 delay(500);


}

void loop() {

bp2 = digitalRead(A1);

if(bp2 == 0 && mode == 0 ){

  mode = 1;
  fpince();
  delay(500);
  opince();
  bp2 = 1;

}

if(bp2 == 0 && mode == 1 ){

  mode = 0;
  ouvre();
  bp2 = 1;

}


bp1 = digitalRead(A0);
delay(50);
Serial.println(bp1);

if(bp1 == 0 && etat == 1){
 delay(1500);
 if (mode == 0) {
 ferme();
 }
 else{
  fpince();
 }
 etat = 0;
delay(1000);
 Serial.println(bp1);
 bp1 = 1;
 
}

delay(50);


if(bp1 == 0 && etat == 0){
 delay(1500);
 if(mode == 0){
 ouvre();
 }
 else{
  opince();
 }
 etat = 1;
 delay(1000);
 Serial.println(bp1);
 bp1 = 1;

}

}



void ferme(){
servo3.write(84);
delay(50);
doigt2.write(0);
doigt1.write(0);
doigt3.write(0);


  
}

void ouvre(){
servo3.write(180);
doigt2.write(180);
doigt1.write(180);
doigt3.write(180);
delay(500);


  
}

void fpince(){
servo3.write(84);
delay(50);
doigt2.write(0);
doigt1.write(0);
doigt3.write(0);
delay(500);


  
}

void opince(){
servo3.write(84);
doigt2.write(0);
doigt1.write(180);
doigt3.write(0);


  
}
