
// include the library code:
#include <Wire.h>
#include <utility/Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>

// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

#define ON HIGH
#define OFF LOW

boolean b_Prechauffage;
boolean b_ObturateurOuvert;
boolean b_VideActif;
boolean b_LampeAllumee;
boolean b_ChassisPresent;
boolean b_Arret;
boolean b_DebutCycle;

#define pinBTNSTART         A0

#define pinCHASSIS          A2
#define pinOBTURATEUROUVERT 12
#define pinOBTURATEURFERME  13
#define pinPRECHAUFFAGEFINI 11

#define pinMARCHEPOMPE      7
#define pinPRECHAUFFAGE     8
#define pinALLUMAGE         9
#define pinROTATION         10

#define pinVOYANTPRECHAUFFE 3
#define pinVOYANTLAMPE      2
#define pinVOYANTPOMPE      4
#define pinPRESENCECHASSIS  5
#define pinCYCLEENCOURS     6

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
      Serial.write("Fin action debut cycle");
  }
}

void doBlink(int pin, int times, String message)
{
  Serial.println ("test " + message);
  for (int i = 0; i < times; i++)
  {
    lcd.clear();
    lcd.print(message);
    digitalWrite(pin, HIGH);
    delay(500);
    lcd.clear();

    digitalWrite(pin, LOW);
    delay(500);
  }

}
void controleVoyants()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print ("Contrôle voyants");
  lcd.setCursor(1, 0);

  doBlink( pinVOYANTPRECHAUFFE , 3, "Prechauffage");
  doBlink( pinVOYANTLAMPE     , 3, "Lampe allumee");
  doBlink(  pinVOYANTPOMPE     , 3, "Pompe marche");
  doBlink(  pinPRESENCECHASSIS , 3, "Chassis ferme");
  doBlink( pinCYCLEENCOURS    , 3, "Cycle en cours");



}

void setup() {

  Serial.begin(9600);
  Serial.write ("setup !!");

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print("Salut les gars !!" );

  lcd.setBacklight(ON);

  pinMode ( pinCHASSIS , INPUT);
  pinMode ( pinOBTURATEUROUVERT , INPUT);
  pinMode ( pinOBTURATEURFERME  , INPUT);
  pinMode ( pinPRECHAUFFAGEFINI , INPUT);

  pinMode ( pinDEBUTCYCLE, INPUT);
  pinMode ( pinBTNSTART, INPUT);

  pinMode ( pinMARCHEPOMPE      , OUTPUT);
  pinMode ( pinPRECHAUFFAGE     , OUTPUT);
  pinMode ( pinALLUMAGE         , OUTPUT);
  pinMode ( pinROTATION         , OUTPUT);

  pinMode ( pinVOYANTPRECHAUFFE , OUTPUT);
  pinMode ( pinVOYANTLAMPE      , OUTPUT);
  pinMode ( pinVOYANTPOMPE      , OUTPUT);
  pinMode ( pinPRESENCECHASSIS  , OUTPUT);
  pinMode ( pinCYCLEENCOURS     , OUTPUT);

  pinMode ( pinBTNSTART         , INPUT);

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

  //
  //  StopperVide();
  //  EteindreLampe();
  //
  //  LireDebutCycle();
  //
  //  b_ObturateurOuvert = digitalRead (pinOBTURATEUROUVERT);
  //  if ( b_ObturateurOuvert)
  //  {
  //    Serial.write ("Fermeture !!");
  //    FermerObturateur();
  //    b_ObturateurOuvert = digitalRead (pinOBTURATEUROUVERT);
  //    if (digitalRead(pinOBTURATEURFERME) != ! b_ObturateurOuvert)
  //    {
  //      Serial.write("Arret");
  //      b_Arret = true;
  //    }
  //    else
  //      b_Arret = false;
  //  }
  //

  controleVoyants();

  b_ChassisPresent = digitalRead(pinCHASSIS);
  digitalWrite(pinPRESENCECHASSIS, b_ChassisPresent);

  b_DebutCycle = digitalRead(pinBTNSTART);
  if (b_DebutCycle) Serial.write("START"); else Serial.write("STOP");
  digitalWrite(pinCYCLEENCOURS, b_DebutCycle);

}

void loop() {

  //LireObturateur();

  //  LireBoutons();

  //LireDebutCycle();

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

  b_ChassisPresent = digitalRead(pinCHASSIS);
  digitalWrite(pinPRESENCECHASSIS, b_ChassisPresent);

  b_DebutCycle = digitalRead(pinBTNSTART);
  digitalWrite(pinCYCLEENCOURS, b_DebutCycle);

}
