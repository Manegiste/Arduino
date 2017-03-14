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

#define SET_HOUR 1
#define SET_MINUTE 2
#define SET_SECOND 3

long int hour;

// format strings
String strHour;
String strMinute;
String strSeconde;

// time values
short heure;
short minute;
short seconde;

// setup control
boolean bool_Setup;
boolean bool_blink;
short   item_set; // which item setting ?

void setup() {

  hour = 0;

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // ------------------------------ welcome message
  // Print a message to the LCD. We track how long it takes since
  // this library has been optimized a bit and we're proud of it :)
  int time = millis();
  lcd.begin(2, 16);

  lcd.print("Salut les gars !!" );

  lcd.setBacklight(ON);

  // ------------------------------setup controls
  // initialize setup variables
  bool_Setup = false;
  hour = 0;
  bool_blink = false;
  item_set = SET_HOUR;

  // ---------------------------- reinit time
  heure = minute = seconde = 0;
}

void loop() {

  uint8_t buttons = lcd.readButtons();
  long newMillis = millis();

  if (newMillis - hour >= 1000)
  {

    if (buttons) {
      // lcd.clear();
      lcd.setCursor(0, 0);

      if (buttons & BUTTON_SELECT) {
        if (!bool_Setup) {
          lcd.clear();
          lcd.setCursor(0, 1);
          lcd.print("SET .......... ");
          lcd.setCursor(0, 0);
          bool_Setup = true;
          item_set = SET_HOUR;
        } else bool_Setup = false;
      }

      if (bool_Setup)
      {
        if (buttons & BUTTON_RIGHT) {
          item_set = (item_set + 1);
          if (item_set > SET_SECOND)
            item_set = SET_HOUR;
        }
        if (buttons & BUTTON_LEFT) {
          item_set --;
          if (item_set < SET_HOUR)
            item_set = SET_SECOND;
        }

        if (buttons & BUTTON_UP)
        {
          if (item_set == SET_HOUR)
          {
            heure++;
            if (hour == 24) hour = 0;
          }
          if (item_set == SET_MINUTE)
          {
            minute++;
            if (minute == 60) minute = 0;
          }
          if (item_set == SET_SECOND)
          {
            seconde++;
            if (seconde == 60) seconde = 0;
          }
        }

        if (buttons & BUTTON_DOWN)
        {
          if (item_set == SET_HOUR)
          {
            heure--;
            if (heure < 0 ) heure  = 23;
          }
          if (item_set == SET_MINUTE)
          {
            minute--;
            if (minute < 0) minute = 59;
          }
          if (item_set == SET_SECOND)
          {
            seconde--;
            if (seconde < 0) seconde = 59;
          }
        }
      }
    }


    hour = newMillis;

    lcd.clear();

    seconde = seconde + 1;
    if (seconde == 60)
    {
      seconde = 0;
      minute++;
    }
    if (minute == 60)
    {
      minute = 0;
      heure++;
    }
    if (heure == 24)
    {
      heure = 0;
    }


    if (heure <= 9) strHour = "0" + String(heure); else strHour = String(heure);
    if (minute <= 9) strMinute = "0" + String(minute); else strMinute = String(minute);
    if (seconde <= 9) strSeconde = "0" + String(seconde); else strSeconde = String(seconde);



    if ( ! bool_Setup   )
    {
      if (hour) {
        lcd.setCursor(0, 0);
        lcd.print (strHour + ":" +  strMinute + ":" + strSeconde);
      }
    }
    else
    {
      lcd.setCursor(0, 1);
      if (!bool_blink)
      {
        bool_blink = true;
        lcd.print ("SET " + strHour + ":" +  strMinute + ":" + strSeconde);
      }
      else {
        String strTmp = String(item_set);
        bool_blink = false;
        if (item_set == SET_HOUR) strHour = "--";
        if (item_set == SET_MINUTE) strMinute = "--";
        if (item_set == SET_SECOND) strSeconde = "--";
        lcd.print ("SET " + strHour + ":" +  strMinute + ":" + strSeconde + " " + strTmp);
      }
    }

  }
}
