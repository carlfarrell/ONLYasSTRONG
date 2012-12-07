#include <Glue.h>

#include <Scissors.h>

#define D4 4
#define D5 5
#define D6 6
#define D7 7
#define D8 8
#define D9 9
#define D10 10
#define D11 11
#define D12 12

Glue winnerMessage;
Scissors incomingMessage;

int con1 = 0;
int con2 = 0;

void setup () {

  incomingMessage.begin();
  winnerMessage.create();

  pinMode(D4, OUTPUT); 
  pinMode(D5, OUTPUT); 
  pinMode(D6, OUTPUT); 
  pinMode(D7, OUTPUT); 
  pinMode(D8, OUTPUT); 
  pinMode(D9, OUTPUT); 
  pinMode(D10, OUTPUT); 
  pinMode(D11, OUTPUT); 
  pinMode(D12, OUTPUT); 

  digitalWrite(D4, HIGH);
  digitalWrite(D5, HIGH);
  digitalWrite(D6, HIGH);
  digitalWrite(D7, HIGH);
  digitalWrite(D8, HIGH);
  digitalWrite(D9, HIGH);
  digitalWrite(D10, HIGH);
  digitalWrite(D11, HIGH);
  digitalWrite(D12, HIGH);
}

void loop() {

  if (incomingMessage.update() > 0) {

    int controller = incomingMessage.getInt(0);
    int signalstrength = incomingMessage.getInt(1);
    //////////////////////////////////////////////////////////////
    if ( controller == 1 && signalstrength > 5 ) {
      digitalWrite(D4, LOW);
      digitalWrite(D5, HIGH);
      digitalWrite(D6, LOW);
      digitalWrite(D7, HIGH);
      digitalWrite(D8, HIGH);
      digitalWrite(D9, HIGH);
      digitalWrite(D10, LOW);
      digitalWrite(D11, LOW);
      digitalWrite(D12, LOW);
      con1 = signalstrength;
      winnerMessage.clear();
      winnerMessage.add(6);
    }

    else if ( controller == 2 && signalstrength > 5) {
      digitalWrite(D4, LOW);
      digitalWrite(D5, LOW);
      digitalWrite(D6, LOW);
      digitalWrite(D7, HIGH);
      digitalWrite(D8, HIGH);
      digitalWrite(D9, HIGH);
      digitalWrite(D10, LOW);
      digitalWrite(D11, HIGH);
      digitalWrite(D12, LOW);
      con2 = signalstrength;
      winnerMessage.clear();
      winnerMessage.add(7);
    }

    else  {
      digitalWrite(D4, LOW);
      digitalWrite(D5, LOW);
      digitalWrite(D6, LOW);
      digitalWrite(D7, HIGH);
      digitalWrite(D8, HIGH);
      digitalWrite(D9, HIGH);
      digitalWrite(D10, LOW);
      digitalWrite(D11, LOW);
      digitalWrite(D12, LOW);
    }
    //////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////
    if (con2 > 5 && con1 > 5) {
      if (con2 > con1) {
        winnerMessage.clear();
        winnerMessage.add(4);
        digitalWrite(D4, LOW);
        digitalWrite(D5, LOW);
        digitalWrite(D6, LOW);
        digitalWrite(D7, HIGH);
        digitalWrite(D8, HIGH);
        digitalWrite(D9, HIGH);
        digitalWrite(D10, HIGH);
        digitalWrite(D11, HIGH);
        digitalWrite(D12, HIGH);
      }
      else if (con1 > con2) {
        winnerMessage.clear();
        winnerMessage.add(3);
        digitalWrite(D4, HIGH);
        digitalWrite(D5, HIGH);
        digitalWrite(D6, HIGH);
        digitalWrite(D7, HIGH);
        digitalWrite(D8, HIGH);
        digitalWrite(D9, HIGH);
        digitalWrite(D10, LOW);
        digitalWrite(D11, LOW);
        digitalWrite(D12, LOW);
      }
      else {
        winnerMessage.clear();
        winnerMessage.add(5);
      }
    }
    //////////////////////////////////////////////////////////////
  }

  else {
    digitalWrite(D4, HIGH);
    digitalWrite(D5, LOW);
    digitalWrite(D6, HIGH);
    digitalWrite(D7, LOW);
    digitalWrite(D8, HIGH);
    digitalWrite(D9, LOW);
    digitalWrite(D10, HIGH);
    digitalWrite(D11, LOW);
    digitalWrite(D12, HIGH);
  }
  
  String package = winnerMessage.getPackage();
  Serial.println (package);
  
  delay(500); 
}


























