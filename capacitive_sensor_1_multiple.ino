#include <CapacitiveSensor.h>

/*
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 */

CapacitiveSensor   cOrange = CapacitiveSensor(2, 3);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cYellow = CapacitiveSensor(4, 5);
CapacitiveSensor   cGreen = CapacitiveSensor(7, 6);
CapacitiveSensor   cBlue = CapacitiveSensor(8, 9);

int pitch1;
int pitch2;
int pitch3;
int pitch4;

long total1 = 0;
long total2 = 0;
long total3 = 0;
long total4 = 0; 
long total5 = 0;
long total6 = 0;

boolean currentState2 = LOW;
boolean lastState2 = LOW;
boolean currentState3 = LOW;
boolean lastState3 = LOW;
boolean currentState4 = LOW;
boolean lastState4 = LOW;
boolean currentState5 = LOW;
boolean lastState5 = LOW;

boolean currentStateBeat = LOW;
boolean lastStateBeat = LOW;

void setup()                    
{
   Serial.begin(9600);
   pinMode(10, OUTPUT);
   pinMode(12, OUTPUT);
   pinMode(11, OUTPUT);
   pinMode(13, OUTPUT);
}

void loop()                    
{ 
    if(analogRead(0) < 10)
      currentStateBeat = HIGH;
    if(analogRead(0) > 1020)
      currentStateBeat = LOW;
      
    if(currentStateBeat == HIGH & lastStateBeat == LOW){
      MIDIButton(0x90, 0x60, 0x40);
      lastStateBeat = HIGH;
    }
    
    if(analogRead(0) > 1020){
      lastStateBeat = LOW;
      MIDIButton(0x90, 0x61, 0x40);
      cOrange.reset_CS_AutoCal();
      cYellow.reset_CS_AutoCal();
      cGreen.reset_CS_AutoCal();
      cBlue.reset_CS_AutoCal();
    }
    
    if(analogRead(0) > 600){
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);
      digitalWrite(13, LOW);
      pitch1 = 0x47;
      pitch2 = 0x48;
      pitch3 = 0x49;
      pitch4 = 0x50;
    }
    else if(analogRead(0) > 300){
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);
      digitalWrite(13, LOW);
      pitch1 = 0x51;
      pitch2 = 0x52;
      pitch3 = 0x53;
      pitch4 = 0x54;
    }
    else{
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      digitalWrite(13, HIGH);
      pitch1 = 0x55;
      pitch2 = 0x56;
      pitch3 = 0x57;
      pitch4 = 0x58;
    }

    long start = millis();
    total2 =  cOrange.capacitiveSensor(30);   //sensitivity = 30???
    total3 =  cYellow.capacitiveSensor(30);
    total4 =  cBlue.capacitiveSensor(30);
    total5 =  cGreen.capacitiveSensor(30);

    if(total2 > 70)
      currentState2 = HIGH;
    else
      currentState2 = LOW;
    if(total3 > 70)
      currentState3 = HIGH;
    else
      currentState3 = LOW;
    if(total4 > 70)
      currentState4 = HIGH;
    else
      currentState4 = LOW;
    if(total5 > 70)
      currentState5 = HIGH;
    else
      currentState5 = LOW;
//break  

   if(lastState2 == LOW && currentState2 == HIGH)
   {
    MIDIButton(0x90, pitch1, 0x40);
    lastState2 = HIGH;
   }
   if(currentState2 == LOW && lastState2 == HIGH)
   {
    MIDIButton(0x80, pitch1, 0x40);
    lastState2 = LOW;
   }

   if(lastState3 == LOW && currentState3 == HIGH)
   {
    MIDIButton(0x90, pitch2, 0x40);
    lastState3 = HIGH;
   }
   if(currentState3 == LOW && lastState3 == HIGH)
   {
    MIDIButton(0x80, pitch2, 0x40);
    lastState3 = LOW;
   }

   if(lastState4 == LOW && currentState4 == HIGH)
   {
    MIDIButton(0x90, pitch3, 0x40);
    lastState4 = HIGH;
   }
   if(currentState4 == LOW && lastState4 == HIGH)
   {
    MIDIButton(0x80, pitch3, 0x40);
    lastState4 = LOW;
   }

   if(lastState5 == LOW && currentState5 == HIGH)
   {
    MIDIButton(0x90, pitch4, 0x40);
    lastState5 = HIGH;
   }
   if(currentState5 == LOW && lastState5 == HIGH)
   {
    MIDIButton(0x80, pitch4, 0x40);
    lastState5 = LOW;
   }
//break 
    if(currentState2 == LOW && currentState3 == LOW && currentState4 == LOW && currentState5 == LOW)
      digitalWrite(12, LOW);
      
    //Serial.print(millis() - start);        // check on performance in milliseconds
    //Serial.print("\t");                    // tab character for debug windown spacing

    //Serial.print(total2);                  // print sensor output 1
    //Serial.print("\t");

    //Serial.print(total3);                  // print sensor output 1
    //Serial.print("\t");

    //Serial.print(total4);                  // print sensor output 1
    //Serial.print("\t");

    //Serial.print(total5);                  // print sensor output 1
    //Serial.println("\t");


    if(currentState2 == HIGH || currentState3 == HIGH || currentState4 == HIGH || currentState5 == HIGH)
      digitalWrite(12, HIGH);

    delay(10);                             // arbitrary delay to limit data to serial port 
}

void MIDIButton(int command, int pitch, int velocity)
{
   Serial.write(command);
   Serial.write(pitch);
   Serial.write(velocity);
}
