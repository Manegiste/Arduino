/*********************

Example code for the Adafruit RGB Character LCD Shield and Library

This code displays text on the shield, and also reads the buttons on the keypad.
When a button is pressed, the backlight changes color.

**********************/

// include the library code:
#include <Wire.h>
#include <utility/Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>

// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// These #defines make it easy to set the backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

#define ON HIGH
#define OFF LOW

long int hour;
void setup() {

  hour = 0;
  // Debugging output
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Print a message to the LCD. We track how long it takes since
  // this library has been optimized a bit and we're proud of it :)
  int time = millis();
  lcd.begin(2, 16);
  // lcd.autoscroll();
  lcd.print("Salut les gars !!" );
  time = millis() - time;
  //  Serial.print("Took "); Serial.print(time); Serial.println(" ms");
  lcd.print ( String("Took ") +  String (time) );
  lcd.setBacklight(ON);
}

uint8_t i = 0;

void loop() {

  uint8_t buttons = lcd.readButtons();
  long newMillis = millis();
  short heure = 0;
  short minute = 0;
  short seconde = 0;
  short tmp = 0;
  if (newMillis - hour >= 1000)
  {
    hour = newMillis;
    tmp = hour / 1000;

    lcd.clear();


    heure = tmp / 3600;
    minute = ((tmp - (heure * 3600)) / 60) ;
    seconde = (tmp - (heure * 3600) - (minute * 60)) % 60;
    heure = heure % 24;
    minute = minute % 60;

    // format strings
    String strHour;
    String strMinute;
    String strSeconde;
    if (heure <= 9) strHour = "0" + String(heure); else strHour = String(heure);
    if (minute <= 9) strMinute = "0" + String(minute); else strMinute = String(minute);
    if (seconde <= 9) strSeconde = "0" + String(seconde); else strSeconde = String(seconde);

   // lcd.print ( String (heure ) + ":" +  String ( minute  ) +  ":" +  String ( seconde));
   lcd.print (strHour + ":" +  strMinute + ":" + strSeconde);
  }

  if (buttons) {
    lcd.clear();
    lcd.setCursor(0, 0);
    if (buttons & BUTTON_UP) {
      lcd.print("UP ");
      lcd.setBacklight(ON);
    }
    if (buttons & BUTTON_DOWN) {
      lcd.print("DOWN ");
      lcd.setBacklight(OFF);
    }
  }
}
