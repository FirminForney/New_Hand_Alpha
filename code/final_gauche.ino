#include <Servo.h>

// Variables pour stocker l'état des boutons poussoirs
int bp1;  
int bp2; 

// État de la main : 1 = ouverte, 0 = fermée
int etat = 1;  

// Mode de la main : 0 = normal, 1 = pince
int mode = 0;  

// Déclaration des servomoteurs
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
  if (bp2 == 0 && mode == 0) { 
    mode = 1;
    fpince();
    delay(500);
    opince();
    bp2 = 1;  // Réinitialiser la variable pour éviter les changements de mode intempestifs
  }

  if (bp2 == 0 && mode == 1) {
    mode = 0;
    ouvre();
    bp2 = 1;  // Réinitialiser la variable
  }

  // Lecture de l'état du bouton poussoir 1
  bp1 = digitalRead(A0);  
  delay(50);
  Serial.println(bp1); // Afficher l'état du bouton 1 sur le moniteur série

  // Fermer ou ouvrir la main en fonction du mode
  if (bp1 == 0 && etat == 1) {  
    delay(1500);
    if (mode == 0) {
      ferme();
    } else {
      fpince();
    }
    etat = 0;
    delay(1000);
    Serial.println(bp1); // Afficher l'état du bouton 1 sur le moniteur série
    bp1 = 1;  // Réinitialiser la variable
  }

  delay(50);

  if (bp1 == 0 && etat == 0) {
    delay(1500);
    if (mode == 0) {
      ouvre();
    } else {
      opince();
    }
    etat = 1;
    delay(1000);
    Serial.println(bp1); // Afficher l'état du bouton 1 sur le moniteur série
    bp1 = 1;  // Réinitialiser la variable
  }
}

// Fonction pour fermer la main
void ferme() {  
  servo3.write(84);
  delay(50);
  doigt2.write(0);
  doigt1.write(0);
  doigt3.write(0); 
}

// Fonction pour ouvrir la main
void ouvre() { 
  servo3.write(180);
  doigt2.write(180);
  doigt1.write(180);
  doigt3.write(180);
  delay(500);
}

// Fonction pour fermer la main en mode pince
void fpince() {  
  servo3.write(84);
  delay(50);
  doigt2.write(0);
  doigt1.write(0);
  doigt3.write(0);
  delay(500);
}

// Fonction pour ouvrir la main en mode pince
void opince() { 
  servo3.write(84);
  doigt2.write(0);
  doigt1.write(180);
  doigt3.write(0);
}
