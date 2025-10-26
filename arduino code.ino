#include "TFT.h"
#include "SPI.h"
#include <AD9833.h>
 
AD9833 AD(5,6,7);  //HW SPI (FNC:pin10, DAT:pin11, CLK:pin13)
 
//int WaveTable[3] = {{AD9833_SINE, AD9833_SQUARE1, AD9833_TRIANGLE};
int Freq = 25; // 10Hz

#define CS 10 // broche pour la connexion CS
#define DC 9  // broche pour la connexion DC
#define RST 8 // broche pour la connexion RST

#define voltagePin A0  // Entree analogique lecture tension
#define currentPin A1  // Entree analogique lecture courant

#define modePin 3      // entrée (lecture du Mode de fonctionnement)
#define relayPin 4     // sortie commande relai CH A/B

bool Mode;  // Variable qui Memorise le mode:  LOW = CHA seul HIGH =CH A/B selon Status of modePin

const unsigned int numReadings = 126;   // Nombre de points par periode. pas besoin de plus. la résolation de l'ecran va limiter l'affichage

//#define TFT_YELLOW  screen.color565(255, 255, 0)
#define BLACK 0x0000 

 TFT screen = TFT(CS, DC, RST);

//------------expirience----------------------------------

// Déclaration des variables

int currentState1 = 0; // Variable pour suivre l'état actuel
const int numStates1 = 3; // Nombre total d'états

int currentState2 = 0; // Variable pour suivre l'état actuel
const int numStates2 = 4; // Nombre total d'états

int p_etat = 0 ;

//----------------------------------------------------------

unsigned int X_A[numReadings];  // display pixels for CH A (de 0 à 65535) ((2^16) - 1).
unsigned int Y_A[numReadings];


unsigned int X_B[numReadings];  // display pixels for CH B
unsigned int Y_B[numReadings];


unsigned int Read_X;
unsigned int Read_Y;

unsigned int i = 0;   // used to read analog values
unsigned int j = 0;  // used to erase screen data



void setup() {
    //Serial.begin(115200);
  SPI.begin();
  AD.begin();
  AD.setFrequency(Freq, 0); // 10HzSZZZZZX
  AD.setWave(AD9833_SINE);

  pinMode(voltagePin, INPUT) ;
  pinMode(currentPin, INPUT) ;
  pinMode(modePin, INPUT_PULLUP);
  pinMode(relayPin, OUTPUT);
  

  Serial.begin(115200) ;
  screen.begin();

  // couleur de l'écran ( r , g , b )

  screen.background(0, 0, 0);

  // couleur du texte de l'écran ( r , g , b )

  dessiner_graphique () ; // dessiner axe x et y   

  // affiche le manuel 

 screen.noStroke();
  // dessiner un rectangle en bleu

 screen.fill(25, 25, 25);
 screen.rect(128, 0, 32, 128);

//            coordonné  tol-x     3ard-Y
//screen.rect(128, 0,     30     ,  50    );

// CH1 et CH2 rectangle 
 screen.fill (0, 0 , 255);
 screen.rect(130, 1, 13, 9);
 
 screen.fill(0, 255 , 255);
 screen.rect(145, 1, 13, 9);
// CH1 et CH2 texte 


//------
 screen.fill(88, 28 , 25);
 screen.rect(128, 12, 32, 9);

 screen.fill(184, 167 , 35);
 screen.rect(132, 24, 25, 10);

 screen.fill(184, 167 , 35);
 screen.rect(132, 37, 25, 10);

 screen.fill(184, 167 , 35);
 screen.rect(132, 50, 25, 10);

 screen.fill(88, 25 , 25);
 screen.rect(128, 63, 32, 10);

 screen.fill(255, 131 , 128);
 screen.rect(132, 76, 25, 10);

 screen.fill(255, 131 , 128);
 screen.rect(132, 89, 25, 10);

 screen.fill(255, 131 , 128);
 screen.rect(132, 102, 25, 10);

 screen.fill(255, 131 , 128);
 screen.rect(132, 115, 25, 10);
 
   screen.setTextSize(1);
   screen.stroke(25, 25, 25); //color de texte 
   screen.text("CHA", 131, 2);
   screen.text("CHB", 146, 2);

   screen.stroke(255, 255, 255); //color de texte 
   screen.text("AMPL", 132, 13);

  screen.stroke(0, 0, 0); //set the stroke color to black
  screen.text("6V", 139, 26);
  screen.text("12V", 136, 39);
  screen.text("24V", 136, 52);

  screen.stroke(255, 255, 255);    // set the stroke color to white
  screen.text("FREQ", 132, 65);

  screen.stroke(0, 0, 0); 
  screen.text("100H", 133, 78);
  screen.text("200H", 133, 91);
  screen.text("500H", 133, 104);
  screen.text("1kHz", 133, 117);
 
  //delay(5000);
//------------------------expirience---------------------------
  pinMode(2, INPUT); // Configuration du bouton en entrée avec résistance de pull-up
  pinMode(3, INPUT); // Configuration du bouton en entrée avec résistance de pull-up
   // Serial.begin(1200);


}

void loop() {
  // SET RELAY to 0 (read CH_A)
  digitalWrite(relayPin, LOW);

  // Lire et afficher CH_A
  for (int i = 0; i < numReadings; i++) {
    Read_X = analogRead(voltagePin);  // lire la tension
    Read_Y = analogRead(currentPin);  // lire le courant
    X_A[i] = map(Read_X, 0, 1023, 2, 126);
    Y_A[i] = map(Read_Y, 0, 1023, 126, 2);
    
    if (i > 0) {
      screen.drawLine(X_A[i-1], Y_A[i-1], X_A[i], Y_A[i], ST7735_BLUE);
    }
     
    delayMicroseconds(50);  // délai entre les lectures d'échantillons
  }

  Mode = digitalRead(modePin);  // Lire modePin pour le mode de fonctionnement

  if (Mode == HIGH) {
    // positionner le relais en position B
    digitalWrite(relayPin, HIGH);
    // lire ch_B
    for (int i = 0; i < numReadings; i++) {
      Read_X = analogRead(voltagePin);  // lire la tension
      Read_Y = analogRead(currentPin);  // lire le courant
      X_B[i] = map(Read_X, 0, 1023, 2, 126);
      Y_B[i] = map(Read_Y, 0, 1023, 126, 2);
      
      if (i > 15) {
        screen.drawLine(X_B[i-1], Y_B[i-1], X_B[i], Y_B[i], ST7735_CYAN);
      }
      
      delayMicroseconds(50);  // délai entre les lectures d'échantillons
    }

    // repositionner le relais en position A
    digitalWrite(relayPin, LOW);
  }

  delay(1500);  // délai pour garder la trace sur TFT avant d'effacer

  // Procédure pour effacer l'écran
  for (int i = 0; i < numReadings; i++) {
    if (i > 0) {
      screen.drawLine(X_A[i-1], Y_A[i-1], X_A[i], Y_A[i], ST7735_BLACK);
    }
  }

  if (Mode == HIGH) {  // effacer ch_B
    for (int i = 0; i < numReadings; i++) {
      if (i > 0) {
        screen.drawLine(X_B[i-1], Y_B[i-1], X_B[i], Y_B[i], ST7735_BLACK);
      }
    }
    Mode = LOW;
  }

  // commande pour redessiner les axes
  dessiner_graphique();
}  
  // screen.drawPixel(Y, P, ST7735_BLUE); 
 //Allumer les pixel d'apres leurs position  if courant et tesion sont positive
  


/*
  if(potValue1 == 0 && potValue2 == 0 && p_etat == 0 ) { 
    //p_etat éviter bouclage de supression. si p_etat = 1 alors il est déja suppimer pas l'appele de resupprimer
    //cela cause une 
     delate_curve() ; //appele au fonction chargée par suppression de courbe
     p_etat = 1 ; //est une variable represente l'etat presédent de graphe 
                  // p_etat = 0 >> courbe dessiner |  p_etat = 1 >> courbe supprimer
   }
  else if (potValue1 != 0 || potValue2 != 0) {
    screen.drawPixel(P, Y, ST7735_BLUE); 
    p_etat =  0 ;
   }
  */




// }
 //Allumer les pixel d'apres leurs position  if courant negative et tesion positive

 //int P = voltage1*8.2+64 ;
 //int Y = current*100000+64 ;
 //screen.drawPixel(Y, P, ST7735_BLUE); 

 // Allumer les pixel d'apres leurs position  if courant et tesion sont negative

 //screen.drawPixel(P, Y, ST7735_BLUE);

 // affichage lesx valeurs de tension et courant sur serial monitor

 // Serial.print(potValue1) ;
 //Serial.print("\ten volte : ") ;
 //Serial.println(voltage1) ;
//**  Serial.print(potValue1) ;
 //** Serial.print("\t \t ") ;
 //** Serial.println(potValue2) ;
//---------------------expirience-----------------------------
/*  screen.noFill();
  drew_rect1();
  delay(2000); // Attend 2 secondes
  delete_rect1();
  delay(2000); // Attend 2 secondes avant de recommencer
  */
/*
//-------------------LE BOUTTONE--------------------------------
  Serial.println(digitalRead(3));

  if (digitalRead(2) == LOW) { // Si le bouton est pressé
    delay(300); // Anti-rebond
    currentState1++; // Passe à l'état suivant
    if (currentState1 >= numStates1) { // Si on dépasse le nombre total d'états, retour à 0
      currentState1 = 0;
    }
  }

  // Exécute la fonction appropriée en fonction de l'état actuel
  switch (currentState1) {
      case 0:
        drew_rect1();
        delete_rect2();
        delete_rect3();
        break;
      case 1:
        drew_rect2();
        delete_rect1();
        delete_rect3();
        break;
      case 2:
        drew_rect3();
        delete_rect1();
        delete_rect2();
        break;
  }


if (digitalRead(3) == LOW) { // Si le bouton est pressé
    delay(300); // Anti-rebond
    currentState2++; // Passe à l'état suivant
    if (currentState2 >= numStates2) { // Si on dépasse le nombre total d'états, retour à 0
      currentState2 = 0;
    }
  }

  // Exécute la fonction appropriée en fonction de l'état actuel
  switch (currentState2) {
      case 0:
        drew_rect4();
        delete_rect5();
        delete_rect6();
        delete_rect7();
        break;
      case 1:
        drew_rect5();
        delete_rect4();
        delete_rect6();
        delete_rect7();
        break;
      case 2:
        drew_rect6();
        delete_rect4();
        delete_rect5();
        delete_rect7();
        break;
      case 3:
        drew_rect7();
        delete_rect4();
        delete_rect5();
        delete_rect6();
        break;
  }

//------------------------------------------------------------

 // delayMicroseconds(10);        // Attendre 10 microseconde
  */





//_________________________________________LES FONCTION__________________________________________________

// Définition des fonctions

//-------------------fonction qui dessiner le graphique X-Y--------------------------- 
 void dessiner_graphique () {

  screen.stroke(0, 0, 0);

  // tracer quatre lignes noires

  screen.fill(0, 0, 0);
  screen.line(0, 0, 128, 0);
  screen.line(0, 0, 0, 128);
  screen.line(0, 128, 128, 128);
  screen.line(128, 0, 128, 128);

  screen.stroke(116, 124, 169);

  // tracer l'axe des X et Y 

    screen.line(64, 2, 64, 126);
    screen.line(2, 64, 126, 64);

  // tracer echelle de axe X (tension)

    screen.line(2, 60, 2, 70);
    screen.line(126, 60, 126, 70);
    screen.line(22.66, 60, 22.66, 70);
    screen.line(43.32, 60, 43.32, 70);
    screen.line(84.64, 60, 84.64, 70);
    screen.line(105.3, 60, 105.3, 70);

  // tracer echelle de axe Y (courant)

    screen.line(60, 2, 70, 2);
    screen.line(60, 126, 70, 126);
    screen.line(60, 22.66, 70, 22.66);
    screen.line(60, 43.32, 70, 43.32);
    screen.line(60, 84.64, 70, 84.64);
    screen.line(60, 105.3, 70, 105.3);
}



//-----la fonction qui suprime la courbe dessiner a chaque fois on lever les main sur le composant tester-----
void delete_curve() {
  // dessiner un rectangle en noire 
 screen.noStroke();
 screen.fill(0, 0, 0);
 screen.rect(0, 0, 128, 128);
  //appele au fonction pour dessiner le graphe
 dessiner_graphique () ;

}
/*
//-----------------------dessiner le cardre de chaque rect (qui mouve) de AMPL---------------------------------------
void drew_rect1() {
  // Code pour la fonction 1
  screen.noFill();
  screen.stroke(255, 255, 255); // Couleur du trait : blanc
  drawRectangle(132-1, 24-1, 25+2, 10+2);
}
void drew_rect2() {
  // Code pour la fonction 2
  screen.noFill();
  screen.stroke(255, 255, 255); // Couleur du trait : blanc
  drawRectangle(132-1, 37-1, 25+2, 10+2);
}
void drew_rect3() {
  // Code pour la fonction 3
  screen.noFill();
  screen.stroke(255, 255, 255); // Couleur du trait : blanc
  drawRectangle(132-1, 50-1, 25+2, 10+2);
}

//----------suprimer le cadre de chauqe rectangle (qui mouve) de AMPL---------------------------
void delete_rect1() {
  // Code pour la fonction 1
  screen.noFill();
  screen.stroke(255, 255, 255); // Couleur du trait : blanc
  clearRectangle(132-1, 24-1, 25+2, 10+2);
}
void delete_rect2() {
  // Code pour la fonction 2
  screen.noFill();
  screen.stroke(255, 255, 255); // Couleur du trait : blanc
  clearRectangle(132-1, 37-1, 25+2, 10+2);
}
void delete_rect3() {
  // Code pour la fonction 3
  screen.noFill();
  screen.stroke(255, 255, 255); // Couleur du trait : blanc
  clearRectangle(132-1, 50-1, 25+2, 10+2);
}

//-----------------------dessiner le cardre de chaque rect (qui mouve) de FREQ---------------------------------------

void drew_rect4() {
  // Code pour la fonction 1
  screen.noFill();
  screen.stroke(255, 255, 255); // Couleur du trait : blanc
  drawRectangle(132-1, 76-1, 25+2, 10+2);
}
void drew_rect5() {
  // Code pour la fonction 1
  screen.noFill();
  screen.stroke(255, 255, 255); // Couleur du trait : blanc
  drawRectangle(132-1, 89-1, 25+2, 10+2);
}
void drew_rect6() {
  // Code pour la fonction 1
  screen.noFill();
  screen.stroke(255, 255, 255); // Couleur du trait : blanc
  drawRectangle(132-1, 102-1, 25+2, 10+2);
}
void drew_rect7() {
  // Code pour la fonction 1
  screen.noFill();
  screen.stroke(255, 255, 255); // Couleur du trait : blanc
  drawRectangle(132-1, 115-1, 25+2, 10+2);
}

//-----------------------Suprimer le cardre de chaque rect (qui mouve) de FREQ---------------------------------------
void delete_rect4() {
  // Code pour la fonction 2
  screen.noFill();
  screen.stroke(255, 255, 255); // Couleur du trait : blanc
  clearRectangle(132-1, 76-1, 25+2, 10+2);
}
void delete_rect5() {
  // Code pour la fonction 2
  screen.noFill();
  screen.stroke(255, 255, 255); // Couleur du trait : blanc
  clearRectangle(132-1, 89-1, 25+2, 10+2);
}
void delete_rect6() {
  // Code pour la fonction 2
  screen.noFill();
  screen.stroke(255, 255, 255); // Couleur du trait : blanc
  clearRectangle(132-1, 102-1, 25+2, 10+2);
}
void delete_rect7() {
  // Code pour la fonction 2
  screen.noFill();
  screen.stroke(255, 255, 255); // Couleur du trait : blanc
  clearRectangle(132-1, 115-1, 25+2, 10+2);
}
//-------------------------------------------------------------
/*
void draw_rect(int M) {
  // Code pour la fonction 3
  screen.stroke(255, 255, 0); 
  screen.line(132, M, 157, M);
 // screen.line(xStart, yStart, xEnd, yEnd);
  screen.line(132, M+10, 157, M+10);
}

void clear_rect(int M) {
  // Code pour la fonction 3
  screen.stroke(255, 255, 255); 
  screen.line(132, M, 157, M);
 // screen.line(xStart, yStart, xEnd, yEnd);
  screen.line(132, M+10, 157, M+10);
}
*/

//--------------------------expirience------------------------------------------------
// Fonction pour dessiner un rectangle aux coordonnées spécifiées avec une largeur et une hauteur
void drawRectangle(int x, int y, int width, int height) {
  screen.rect(x, y, width, height);
}

// Fonction pour effacer un rectangle aux coordonnées spécifiées avec une largeur et une hauteur
void clearRectangle(int x, int y, int width, int height) {
  screen.stroke(25,25,25); // Couleur du trait : couleur de fond
  screen.rect(x, y, width, height); // Redessine le rectangle avec la couleur de fond pour effacer le trait
  screen.stroke(255, 255, 255); // Réinitialise la couleur du trait à blanc
}