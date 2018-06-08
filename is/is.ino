// initialize pins for output
const int ledGreen = 12;
const int ledYellow = 11;
const int buzzer = 9; //buzzer to arduino pin 9

// ititialize pins for input
// PIR sensor
const int pirPin = 2;
int pirState = LOW;
int pirValue = 0;
// ultrasonic sensor
const int trigPin = 23;
const int echoPin = 22;
long duration;
int distance;

// initial system state
char systemState = 'g';

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);      // open the serial port at 9600 bps:
  //  Serial.print("test");

  // initialize the digital pins for output.
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output for ultrasonic sensor

  // initialize the digital pins for input.
  pinMode(pirPin, INPUT);
  pinMode(echoPin, INPUT); //Sets the echoPin as an Input for ultrasonic sensor

}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
    // to test output you can control the system using commands
    // if condition helps to prevent reading in the empty command
    char currentInput = Serial.read();
    if (currentInput == 'y') {
      systemState = 'y';
    }
    if (currentInput == 'g') {
      systemState = 'g';
    }
    if (currentInput == 'i') {
      systemState = 'i';
    }
    if (currentInput == 'c') {
      systemState = 'c';
    }
    if (currentInput == 'w') {
      systemState = 'w';
    }
    if (currentInput == '2') {
      systemState = '2';
    }
  }
  // act accordingly to the system state
  if (systemState == 'g')
  {
    systemActivated();
    pirRead();
  } else if (systemState == 'y')
  {
    humanPresenceDetected();
    ultrasonicRead();
  }
  else if (systemState == 'i')
  {
    intruderPresenceDetected();
  }
  else if (systemState == 'c')
  {
    correctCodeEntered();
  }
  else if (systemState == 'w')
  {
    wrongCodeEnteredOnce();
  }
  else if (systemState == '2')
  {
    wrongCodeEnteredTwice();
  }

  // handle sensor readings


}

// output functions

void systemActivated() {

  // to test 1 sec
  int timer = 1000;
  //  to run
  //  int timer = 20000;

  Serial.print("system is active\n");

  // indicate that the system is active with the green LED blinking
  digitalWrite(ledGreen, HIGH);
  delay(timer);
  digitalWrite(ledGreen, LOW);
  delay(timer);
}

void humanPresenceDetected() {

  int timer = 1000;

  Serial.print("human presence detected\n");

  // indicate that human presence was detected with the yellow LED blinking
  digitalWrite(ledYellow, HIGH);
  delay(timer);
  digitalWrite(ledYellow, LOW);
  delay(timer);
}

void intruderPresenceDetected() {

  int timer = 1000;

  Serial.print("intruder presence detected\n");

  // indicate that intruder presence was detected with the yellow LED blinking
  tone(buzzer, timer);
  delay(timer);
  noTone(buzzer);
  delay(timer);

}

void correctCodeEntered() {

  int timer = 1000;

  Serial.print("correct code entered \n");

  // indicate that the code was entered correctly with the gree LED long blink
  digitalWrite(ledGreen, HIGH);
  delay(timer * 3);
  digitalWrite(ledGreen, LOW);
  delay(timer);

  // change system state to the system active
  systemState = 'g';
}

void wrongCodeEnteredOnce() {

  int timer = 1000;

  Serial.print("wrong code entered once \n");

  // TODO we probably want the buzzer to work at this point

  // indicate that the code was entered incorrectly with the yellow LED long blink
  digitalWrite(ledYellow, HIGH);
  delay(timer * 3);
  digitalWrite(ledYellow, LOW);
  delay(timer);

  // change system state to the system active
  systemState = 'i';
}

void wrongCodeEnteredTwice() {

  int timer = 500;

  Serial.print("wrong code entered twice\n");

  // indicate that the code was twice entered incorrectly with the change of buzzer sound
  tone(buzzer, timer);
  delay(timer);
  noTone(buzzer);
  delay(timer);
}

// TODO sensor readings

void pirRead() {
  pirValue = digitalRead(pirPin);  // read input value
  if (pirValue == HIGH) {            // check if the input is HIGH

    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!\n");
      // We only want to print on the output change, not state
      pirState = HIGH;
      systemState = 'y';

    }
  } else {

    if (pirState == HIGH) {
      // we have just turned of
      Serial.println("Motion ended!\n");
      // We only want to print on the output change, not state
      pirState = LOW;
      systemState = 'g';

    }
  }
}

void ultrasonicRead() {
  
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  if(distance > 200){
    // system returns systemActivated state
    systemState = 'g';
  }else if(distance > 50){
    // system goes to humanPresenceDetected state
    systemState = 'y';
  }else{
    // system goes to intruderPresenceDetected state
    systemState g= 'i';
  }
  Serial.print("systemState: ");
  Serial.println(systemState);
}

