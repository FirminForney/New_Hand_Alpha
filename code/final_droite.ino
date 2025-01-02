#include <Servo.h>

// Angle maximal des servomoteurs
int angleMax = 180;  

// Variables pour stocker l'état des boutons poussoirs
int bp1;  
int bp2;

// État de la main : true = ouverte, false = fermée
bool etatMain = true;  

// Mode de la main : false = normal, true = pince
bool modePince = false;  

// Déclaration des servomoteurs//
Servo doigt2;  
Servo doigt1;
Servo servo3;  // Base de la main ? 
Servo doigt3;

void setup() {
  // Attacher les servomoteurs aux broches correspondantes
  doigt2.attach(10);  
  doigt1.attach(9);
  servo3.attach(6);
  doigt3.attach(5);

  // Initialiser la communication série
  Serial.begin(9600);  

  // Configurer les broches des boutons poussoirs en entrée avec résistance pull-up
  pinMode(A0, INPUT_PULLUP);  
  pinMode(A1, INPUT_PULLUP);

  // Configurer les broches 7 et 8 en sortie 
  pinMode(8, OUTPUT);  
  pinMode(7, OUTPUT);
  digitalWrite(8, HIGH);
  digitalWrite(7, HIGH);

  // Ouvrir la main au démarrage
  ouvre();  
  delay(500); 
}

void loop() {
  // Lecture de l'état du bouton poussoir 2
  bp2 = digitalRead(A1);  

  // Changer de mode (normal/pince)
  if (bp2 == 0 && modePince == false) { 
    modePince = true;
    fpince();
    delay(500);
    opince();
    bp2 = 1;  // Réinitialiser la variable pour éviter les changements de mode intempestifs
  }

  if (bp2 == 0 && modePince == true) {
    modePince = false;
    ouvre();
    bp2 = 1;  // Réinitialiser la variable
  }

  // Lecture de l'état du bouton poussoir 1
  bp1 = digitalRead(A0);  
  delay(50);

  // Fermer ou ouvrir la main en fonction du mode
  if (bp1 == 0 && etatMain == true) {  
    delay(1500);
    if (modePince == false) {
      ferme();
    } else {
      fpince();
    }
    etatMain = false;
    delay(1000);
    bp1 = 1;  // Réinitialiser la variable
  }

  delay(50);

  if (bp1 == 0 && etatMain == false) {
    delay(1500);
    if (modePince == false) {
      ouvre();
    } else {
      opince();
    }
    etatMain = true;
    delay(1000);
    bp1 = 1;  // Réinitialiser la variable
  }
}

// Fonction pour fermer la main
void ferme() {  
  servo3.write(96);
  delay(50);
  doigt2.write(0);
  doigt1.write(0);
  doigt3.write(0);
}

// Fonction pour ouvrir la main
void ouvre() {  
  servo3.write(0);
  doigt2.write(angleMax);
  doigt1.write(angleMax);
  doigt3.write(angleMax);
  delay(500);
}

// Fonction pour fermer la main en mode pince
void fpince() {  
  servo3.write(96);
  delay(50);
  doigt2.write(0);
  doigt1.write(0);
  doigt3.write(0);
  delay(500);
}

// Fonction pour ouvrir la main en mode pince
void opince() {  
  servo3.write(96);
  doigt2.write(0);
  doigt1.write(angleMax);
  doigt3.write(0);
}