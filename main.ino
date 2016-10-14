/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>
#include <IRremote.h>

// LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int input_pin = 13; //set D10 as input signal pin
IRrecv irrecv(input_pin);
decode_results signals;

// PERSO
int count = 0;
long currentTime;
long savedTime = 0;

enum sonarStatus {
  INIT
  , DISTANT
  , CLOSE
};

sonarStatus sonarSavedState = INIT;
sonarStatus sonarCurrentState = INIT;

void setup() {
  Serial.begin(9600);
  
  // LCD
  lcd.begin(16, 2);
  lcd.print("Distance :");

  // IR
  irrecv.enableIRIn();
  
  initSonar();
}



void loop() {
  char digit = 0;
  long distance = 0;

  currentTime = millis();
  
  if (savedTime + 100 <= currentTime) {
    distance = getDistance();

    sonarCurrentState = (distance < 30) ? CLOSE : DISTANT;

    lcd.setCursor(11, 0);
    lcd.print("   ");

    if ((distance / 100) > 0) digit++;
    if ((distance / 10) > 0) digit++;

    lcd.setCursor(13 - digit, 0);
    lcd.println(distance);

    
    lcd.setCursor(14, 0);
    lcd.print("cm");

    if (sonarSavedState == INIT || (sonarSavedState == DISTANT && sonarCurrentState == CLOSE)) {
      count++;
      lcd.setCursor(0, 1);
      lcd.print("count :");
      
      lcd.setCursor(8, 1);
      lcd.print(count);
    }
    sonarSavedState = sonarCurrentState;

    savedTime = currentTime;
  }
}

