#include <LiquidCrystal.h>
#include <Glue.h>
#include <Scissors.h>

int boo = 0;

Glue glue;
Scissors incomingMessage;

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

#define D0 5
#define D1 3

#define AN0 0

#define DELAY 800

int tare;

void setup()   {
  glue.create();

  Serial.begin(19200); 
  incomingMessage.begin();

  lcd.begin(16, 2);

  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);

  tare = measure();

  lcd.clear();
  lcd.print("  PLACE  PHONE  ");
  lcd.setCursor(0, 1);
  lcd.print(" MEASURE SIGNAL ");
}

void loop()                     
{
  while (true) {
    glue.clear();
    // 1 for sensor 1, 2 for sensor 2
    glue.add(2);
    glue.add( measure() - tare );
    String package = glue.getPackage();
    Serial.println (package);


    if (incomingMessage.update() > 0) {
      int controller = incomingMessage.getInt(0);

      // 6 for sensor 1, 7 for sensor 2
      if ( controller == 7 ) { 
        lcd.setCursor(0, 0);
        lcd.print("--WAITING  FOR--");
        lcd.setCursor(0, 1);
        lcd.print("----OPPONENT----");
        boo = 1;
      }
      // 3 for sensor 1, 4 for sensor 2
      if ( controller == 4) {
        lcd.setCursor(0, 0);
        lcd.setCursor(0, 0);
        lcd.print("YOU ARE A WINNER");
        lcd.setCursor(0, 1);
        lcd.print("---NICE PHONE---");
      }
      // 4 for sensor 1, 3 for sensor 2
      if ( controller == 3) {
        lcd.setCursor(0, 0);
        lcd.setCursor(0, 0);
        lcd.print("YOU ARE A LOSER!");
        lcd.setCursor(0, 1);
        lcd.print("---LAME PHONE---");
      }

      if ( controller == 5) {
        lcd.setCursor(0, 0);
        lcd.setCursor(0, 0);
        lcd.print("YOU  BOTH  SUCK!");
        lcd.setCursor(0, 1);
        lcd.print("----------------");
      }
    }


  }


}

int measure () {
  int i,a0,a1;
  long s;
  for (i = 0; i < 256; i++) {
    digitalWrite (D0,HIGH);
    digitalWrite (D1,LOW);
    delayMicroseconds(DELAY);
    a0 = analogRead(AN0);

    // reverse polarity
    digitalWrite (D0,LOW);
    digitalWrite (D1,HIGH);
    delayMicroseconds(DELAY);
    a1 = analogRead(AN0);

    s += (long) (a0 - a1);

  }

  if ( s < 0) {
    s = -s;
  }

  return s>>5;
}






























