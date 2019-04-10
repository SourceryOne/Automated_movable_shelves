
const int commandPin1 = 2;    // the number of the pushbutton pin 
const int commandPin2 = 3;    // the number of the pushbutton pin 
const int commandPin3 = 4;    // the number of the pushbutton pin 
const int commandPin4 = 5;    // the number of the pushbutton pin 

const int motor1SpeedPin = 9;           // the PWM pin the MOTOR1 is attached to
const int motor1DirectionPin = 10;
const int motor2SpeedPin = 11;           // the PWM pin the MOTOR2 is attached to
const int motor2DirectionPin = 12;

const int endStopPin1 = A0;
const int endStopPin2 = A1;
const int endStopPin3 = A2;
const int endStopPin4 = A3;

int commandPin1Read=1; //HIGH or LOW, PULLUP pins so LOW when set.
int commandPin2Read=1;
int commandPin3Read=1;
int commandPin4Read=1;

int command1Set=0; //HIGH or LOW, HIGH when set.
int command2Set=0;
int command3Set=0;
int command4Set=0;

int endStop1;
int endStop2;
int endStop3;
int endStop4;

int motor1Speed = 0;    //
int motor2Speed = 0;    //
int acceleration = 5;    // 
int motor1Direction = LOW;
int motor2Direction = LOW;

void setup() {
  // put your setup code here, to run once:
  Serial.begin( 9600 );
  pinMode(commandPin1, INPUT_PULLUP);
  pinMode(commandPin2, INPUT_PULLUP);
  pinMode(commandPin3, INPUT_PULLUP);
  pinMode(commandPin4, INPUT_PULLUP);
  pinMode(endStopPin1, INPUT_PULLUP);  // set pull-up on analog pin 0 
  pinMode(endStopPin2, INPUT_PULLUP);  // set pull-up on analog pin 1 
  pinMode(endStopPin3, INPUT_PULLUP);  // set pull-up on analog pin 2 
  pinMode(endStopPin4, INPUT_PULLUP);  // set pull-up on analog pin 3 
  pinMode(motor1SpeedPin, OUTPUT);
  pinMode(motor1DirectionPin, OUTPUT);
  pinMode(motor2SpeedPin, OUTPUT);
  pinMode(motor2DirectionPin, OUTPUT);
}

void loop() {
  // This makes sure that only one command is active at each time.
  commandPin1Read=digitalRead(commandPin1);
  commandPin2Read=digitalRead(commandPin2);
  commandPin3Read=digitalRead(commandPin3);
  commandPin4Read=digitalRead(commandPin4);
  
  endStop1=digitalRead(endStopPin1);
  endStop2=digitalRead(endStopPin2);
  endStop3=digitalRead(endStopPin3);
  endStop4=digitalRead(endStopPin4);


  //Making sure only one command is run at a time...
  if (commandPin1Read == 0) { 
    command1Set=1; 
    command2Set=0; 
    command3Set=0; 
    command4Set=0;
    Serial.println ("command1");
  }
  if (commandPin2Read == LOW) { 
    command1Set=0; 
    command2Set=1; 
    command3Set=0; 
    command4Set=0;
    Serial.println ("command2");
  }
  if (commandPin3Read == LOW) { 
    command1Set=0; 
    command2Set=0; 
    command3Set=1; 
    command4Set=0;
    Serial.println ("command3");
  }
  if (commandPin4Read == LOW) { 
    command1Set=0; 
    command2Set=0; 
    command3Set=0; 
    command4Set=1;
    Serial.println ("command4");
  }
//COMMAND1
  if (command1Set == 1) {
    Serial.println ("command1 is set");
    //Serial.print ("endstop4:");
    //Serial.println (endStop4);
    //command1=move all shelves to the right. so until e4, then e2 and e3.
    //1. Move shelf 5,6 to the right.
    //direction=right (HIGH);
    digitalWrite (motor2DirectionPin, HIGH);
    while (endStop4==LOW) { //run motor2 until endStop4==HIGH;
      motor2Speed = motor2Speed + acceleration;
      if (motor2Speed >= 255) { motor2Speed=255; }
      analogWrite(motor2SpeedPin, motor2Speed);
      endStop4=digitalRead(endStopPin4);
      //Serial.println (endStop4);
    }
    //Ramp Down Motor2
    while (motor2Speed>0) {
      motor2Speed = motor2Speed - acceleration;
      if (motor2Speed >= 0) { motor2Speed=0; }
      analogWrite(motor2SpeedPin, motor2Speed);
    }
    motor2Speed=0;
    //2. Move shelf 1,2,3,4 to the right. as long as estop 2 OR 3 are not pressed.
    digitalWrite (motor1DirectionPin, HIGH);
    while (endStop2==LOW | endStop3==LOW) { //run motor1 until endStop4==HIGH;
      //direction=right (HIGH);
      motor1Speed = motor1Speed + acceleration;
      if (motor1Speed >= 255) { motor1Speed=255; }
      analogWrite(motor1SpeedPin, motor1Speed);
      endStop2=digitalRead(endStopPin2);
      //Serial.println (endStop2);
      endStop3=digitalRead(endStopPin3);
      //Serial.println (endStop3);
    }
    //Ramp Down Motor2
    while (motor1Speed>0) {
      motor1Speed = motor1Speed - acceleration;
      if (motor1Speed >= 0) { motor1Speed=0; }
      analogWrite(motor1SpeedPin, motor1Speed);
    }
    motor1Speed=0;
    command1Set = 0;
    Serial.println ("Command1 Done!");
    //DONE! Shelf 1 is now open.
  }

//COMMAND2
  if (command2Set == 1) {
    Serial.println ("command2 is set");
    //Open shelves 2,3, by pressing shelf 3456 to the right and then 12 to the left
    //Motor2 to the left.
    //Below is all from command1 as all that needs to happen.
    //Serial.print ("endstop4:");
    //Serial.println (endStop4);
    //command1=move all shelves to the right. so until e4, then e2 and e3.
    //1. Move shelf 5,6 to the right.
    //direction=right (HIGH);
    digitalWrite (motor2DirectionPin, HIGH);
    while (endStop4==LOW) { //run motor2 until endStop4==HIGH;
      motor2Speed = motor2Speed + acceleration;
      if (motor2Speed >= 255) { motor2Speed=255; }
      analogWrite(motor2SpeedPin, motor2Speed);
      endStop4=digitalRead(endStopPin4);
      //Serial.println (endStop4);
    }
    //Ramp Down Motor2
    while (motor2Speed>0) {
      motor2Speed = motor2Speed - acceleration;
      if (motor2Speed >= 0) { motor2Speed=0; }
      analogWrite(motor2SpeedPin, motor2Speed);
    }
    motor2Speed=0;
    //2. Move shelf 1,2,3,4 to the right. as long as estop 2 OR 3 are not pressed.
    digitalWrite (motor1DirectionPin, HIGH);
    while (endStop2==LOW | endStop3==LOW) { //run motor1 until endStop4==HIGH;
      //direction=right (HIGH);
      motor1Speed = motor1Speed + acceleration;
      if (motor1Speed >= 255) { motor1Speed=255; }
      analogWrite(motor1SpeedPin, motor1Speed);
      endStop2=digitalRead(endStopPin2);
      //Serial.println (endStop2);
      endStop3=digitalRead(endStopPin3);
      //Serial.println (endStop3);
    }
    //Ramp Down Motor1
    while (motor1Speed>0) {
      motor1Speed = motor1Speed - acceleration;
      if (motor1Speed >= 0) { motor1Speed=0; }
      analogWrite(motor1SpeedPin, motor1Speed);
    }
    motor1Speed=0;
    //Then run motor1 to the left.
    //2. Move shelf 1,2 to the left. as long as estop 1 is not pressed.
    digitalWrite (motor1DirectionPin, LOW);
    while (endStop1==LOW) { //run motor1 until endStop1==HIGH;
      //direction=left (LOW);
      motor1Speed = motor1Speed + acceleration;
      if (motor1Speed >= 255) { motor1Speed=255; }
      analogWrite(motor1SpeedPin, motor1Speed);
      endStop1=digitalRead(endStopPin1);
      //Serial.println (endStop1);
    }
    //Ramp Down Motor1
    while (motor1Speed>0) {
      motor1Speed = motor1Speed - acceleration;
      if (motor1Speed >= 0) { motor1Speed=0; }
      analogWrite(motor1SpeedPin, motor1Speed);
    }
    motor1Speed=0;
    command2Set = 0;
    Serial.println ("Command2 Done!");
    //DONE!
  }

//COMMAND3
  if (command3Set == 1) {
    Serial.println ("command3 is set");
    //Open shelves 4,5, by pulling 12 to the left, then pressing shelf 34(56) to the left and then 56 to the right

    //1. Move shelf 1,2 to the left. as long as estop 1 is not pressed.
    digitalWrite (motor1DirectionPin, LOW);
    while (endStop1==LOW) { //run motor1 until endStop1==HIGH;
      //direction=left (LOW);
      motor1Speed = motor1Speed + acceleration;
      if (motor1Speed >= 255) { motor1Speed=255; }
      analogWrite(motor1SpeedPin, motor1Speed);
      endStop1=digitalRead(endStopPin1);
      //Serial.println (endStop1);
    }
    //Ramp Down Motor1
    while (motor1Speed>0) {
      motor1Speed = motor1Speed - acceleration;
      if (motor1Speed >= 0) { motor1Speed=0; }
      analogWrite(motor1SpeedPin, motor1Speed);
    }
    motor1Speed=0;

    //2. Move shelf 3456 to the left (LOW). as long as estop 2,3 is not pressed.
    digitalWrite (motor2DirectionPin, LOW);
    while (endStop2==LOW | endStop3==LOW) { //run motor1 until endStop2 AND 3==HIGH;
      //direction=left (LOW);
      motor2Speed = motor2Speed + acceleration;
      if (motor2Speed >= 255) { motor2Speed=255; }
      analogWrite(motor2SpeedPin, motor2Speed);
      endStop2=digitalRead(endStopPin2);
      //Serial.println (endStop2);
      endStop3=digitalRead(endStopPin3);
      //Serial.println (endStop3);
    }
    //Ramp Down Motor2
    while (motor2Speed>0) {
      motor2Speed = motor2Speed - acceleration;
      if (motor2Speed >= 0) { motor2Speed=0; }
      analogWrite(motor2SpeedPin, motor2Speed);
    }
    motor2Speed=0;


    //3. Pull/Move shelf 5,6 to the right until estop4.
    //direction=right (HIGH);
    digitalWrite (motor2DirectionPin, HIGH);
    while (endStop4==LOW) { //run motor2 until endStop4==HIGH;
      motor2Speed = motor2Speed + acceleration;
      if (motor2Speed >= 255) { motor2Speed=255; }
      analogWrite(motor2SpeedPin, motor2Speed);
      endStop4=digitalRead(endStopPin4);
      //Serial.println (endStop4);
    }
    //Ramp Down Motor2
    while (motor2Speed>0) {
      motor2Speed = motor2Speed - acceleration;
      if (motor2Speed >= 0) { motor2Speed=0; }
      analogWrite(motor2SpeedPin, motor2Speed);
    }
    motor2Speed=0;
    Serial.println ("Command3 DONE!");
    command3Set = 0;
    //DONE!
  }



//COMMAND4
  if (command4Set == 1 ) { 
    Serial.println ("command4 is set");
    //Open shelves 6 (7) by pulling 12 to the left and pushing 3456 to the left.
    //All commands from COMMAND3, but remove the last one from it (ie not pulling 56 back...
    
    //1. Move shelf 1,2 to the left. as long as estop 1 is not pressed.
    digitalWrite (motor1DirectionPin, LOW);
    while (endStop1==LOW) { //run motor1 until endStop1==HIGH;
      //direction=left (LOW);
      motor1Speed = motor1Speed + acceleration;
      if (motor1Speed >= 255) { motor1Speed=255; }
      analogWrite(motor1SpeedPin, motor1Speed);
      endStop1=digitalRead(endStopPin1);
      //Serial.println (endStop1);
    }
    //Ramp Down Motor1
    while (motor1Speed>0) {
      motor1Speed = motor1Speed - acceleration;
      if (motor1Speed >= 0) { motor1Speed=0; }
      analogWrite(motor1SpeedPin, motor1Speed);
    }
    motor1Speed=0;
    delay(50);
    //2. Move shelf 3456 to the left (LOW). as long as estop 2,3 is not pressed.
    digitalWrite (motor2DirectionPin, LOW);
    while (endStop2==LOW | endStop3==LOW) { //run motor1 until endStop2 AND 3==HIGH;
      //direction=left (LOW);
      motor2Speed = motor2Speed + acceleration;
      if (motor2Speed >= 255) { motor2Speed=255; }
      analogWrite(motor2SpeedPin, motor2Speed);
      endStop2=digitalRead(endStopPin2);
      //Serial.println (endStop2);
      endStop3=digitalRead(endStopPin3);
      //Serial.println (endStop3);
    }
    //Ramp Down Motor2
    while (motor2Speed>0) {
      motor2Speed = motor2Speed - acceleration;
      if (motor2Speed >= 0) { motor2Speed=0; }
      analogWrite(motor2SpeedPin, motor2Speed);
    }
    motor2Speed=0;
    
    command4Set = 0;
    Serial.println ("Command4 Done!");
    //DONE!
  }
}


