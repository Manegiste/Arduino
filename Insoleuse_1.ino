
// include the library code:
#include <Wire.h>
#include <utility/Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>


boolean b_Prechauffage;
boolean b_ObturateurOuvert;
boolean b_VideActif;
boolean b_LampeAllumee;
boolean b_ChassisPresent;
boolean b_Arret;
boolean b_DebutCycle;

#define pinCHASSIS          10
#define pinOBTURATEUROUVERT 12
#define pinOBTURATEURFERME  13
#define pinPRECHAUFFAGEFINI 11

#define pinMARCHEPOMPE      3
#define pinPRECHAUFFAGE     4
#define pinALLUMAGE         5
#define pinROTATION         6

#define pinDEBUTCYCLE       9

void StopperVide() {
  Serial.write("Arret pompe \n");
  digitalWrite(pinMARCHEPOMPE, LOW);
}

void EteindreLampe() {


  digitalWrite(pinPRECHAUFFAGE, LOW);
  digitalWrite(pinALLUMAGE, LOW);

}

void FermerObturateur() {

}

void LireObturateur()
{
  boolean tmp = digitalRead (pinOBTURATEUROUVERT);
  if ( b_ObturateurOuvert != tmp)
  {
    Serial.write("NOUVEAU STATUT: Obturateur ouvert \n");
    b_ObturateurOuvert = tmp;
  }

  tmp = digitalRead (pinOBTURATEURFERME);
  if ( b_ObturateurOuvert == tmp)
  {
    Serial.write("ERREUR: Obturateur fermé \n");
  }
}

void LireDebutCycle() {
  boolean tmp = digitalRead(pinDEBUTCYCLE);
  if (b_DebutCycle != tmp)
  {
    b_DebutCycle = tmp;
    if (b_DebutCycle)
      Serial.write("Lancement cycle");
    else
      Serial.write("Fin actiodebut cycle");
  }
}

void setup() {

  Serial.begin(9600);
  Serial.write ("setup !!");

  pinMode ( pinCHASSIS , INPUT);
  pinMode ( pinOBTURATEUROUVERT , INPUT);
  pinMode ( pinOBTURATEURFERME  , INPUT);
  pinMode ( pinPRECHAUFFAGEFINI , INPUT);

  pinMode ( pinDEBUTCYCLE, INPUT);

  pinMode ( pinMARCHEPOMPE      , OUTPUT);
  pinMode ( pinPRECHAUFFAGE     , OUTPUT);
  pinMode ( pinALLUMAGE         , OUTPUT);
  pinMode ( pinROTATION         , OUTPUT);

  // Statut initial:
  //      - Lampe éteinte
  //      - Obturateur fermé
  //      - Timer à 2 minutes
  //      - Pompe arrêtée
  //      - Circuit vide ouvert
  b_Prechauffage = false;
  b_ObturateurOuvert = false;
  b_VideActif = false;
  b_LampeAllumee = false;
  b_ChassisPresent = false;
  b_Arret = true;
  b_DebutCycle = false;

  StopperVide();
  EteindreLampe();

  LireDebutCycle();

  b_ObturateurOuvert = digitalRead (pinOBTURATEUROUVERT);
  if ( b_ObturateurOuvert)
  {
    Serial.write ("Fermeture !!");
    FermerObturateur();
    b_ObturateurOuvert = digitalRead (pinOBTURATEUROUVERT);
    if (digitalRead(pinOBTURATEURFERME) != ! b_ObturateurOuvert)
    {
      Serial.write("Arret");
      b_Arret = true;
    }
    else
      b_Arret = false;
  }

  b_ChassisPresent = digitalRead(pinCHASSIS);

}

void loop() {

  LireObturateur();

//  LireBoutons();

  LireDebutCycle();

  // Vérifier le statut des boutons
  // Si préchauffage sélectionné
  //      Vérifier obturateur fermé
  //      Si OK
  //           Préchauffer
  //           Préchauffage actif TRUE
  // Si vide sélectionné
  //      Si vide non activé
  //            Fermer circuit vide
  //            Marche pompe
  //            Vide actif TRUE
  // Si allumage sélectionné
  //      Si préchauffage fini
  //         && vide actif
  //         && chassis présent
  //              Allumage
  //              Décompte
  //      Sinon
  //              Bip
  //              Message erreur
  // Si ARU
  //      Couper vide préchauffage lampe
  //      Fermer obturateur
  // Si Arrêt
  //      Fermer obturateur
  //      Eteindre lampe

}
