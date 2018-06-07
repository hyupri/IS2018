// Pin 12 has the green LED connected
int ledGreen = 12;
int ledYellow = 11;

// initial system state
char systemState = 'g';

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);      // open the serial port at 9600 bps:
  //  Serial.print("test");

  // initialize the digital pins as an output.
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
    // do not read in the empty command
    char currentInput = Serial.read();
    if(currentInput == 'y'){
      systemState = 'y';
    }
    if(currentInput == 'g'){
      systemState = 'g';
    }
  }

  if (systemState == 'g')
  {
    systemActivated();
  } else if (systemState == 'y')
  {
    humanPresenceDetected();
  } 
}

void systemActivated() {

  // to test 1 sec
  int timer = 1000;
  //  to run
  //  int timer = 20000;

  Serial.print("system is active\n");

  digitalWrite(ledGreen, HIGH);   // turn the green LED on
  delay(timer);               // wait for a second
  digitalWrite(ledGreen, LOW);    // turn the green LED off
  delay(timer);               // wait for a second
}

void humanPresenceDetected() {

  int timer = 1000;

  Serial.print("human presence detected\n");

  digitalWrite(ledYellow, HIGH);   // turn the yellow LED on
  delay(timer);               // wait for a second
  digitalWrite(ledYellow, LOW);    // turn the yellow LED off
  delay(timer);               // wait for a second
}

