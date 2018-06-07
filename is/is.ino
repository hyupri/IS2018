#include "CommandHandler.h" // The serial command handler is defined in here. 

CommandHandler<> SerialCommandHandler;

// Pin 12 has the green LED connected
int ledGreen = 12;
int ledYellow = 11;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);      // open the serial port at 9600 bps:
  //  Serial.print("test");

  // initialize the digital pins as an output.
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);

  //nitialize tSerialCommandHandler
  SerialCommandHandler.AddVariable(F("g"), systemActivated);
  SerialCommandHandler.AddVariable(F("y"), humanPresenceDetected);
}

void loop() {
  // put your main code here, to run repeatedly:
  //    systemActvated();

}

void systemActivated() {

  // to test 1 sec
  int timer = 1000;
  //  to run
  //  int timer = 20000;

  digitalWrite(ledGreen, HIGH);   // turn the green LED on
  delay(timer);               // wait for a second
  digitalWrite(ledGreen, LOW);    // turn the green LED off
  delay(timer);               // wait for a second
}

void humanPresenceDetected() {

  int timer = 500;

  digitalWrite(ledGreen, LOW); //  turn the green LED off
  digitalWrite(ledYellow, HIGH);   // turn the yellow LED on
  delay(timer);               // wait for a second
  digitalWrite(ledYellow, LOW);    // turn the yellow LED off
  delay(timer);               // wait for a second
}

