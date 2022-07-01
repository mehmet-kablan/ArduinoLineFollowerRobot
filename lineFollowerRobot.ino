int pinENA = 5;
int pinIN1 = 3;
int pinIN2 = 12;
int pinIN3 = 11;
int pinIN4 = 8;
int pinENB = 6;
int pinSensor1 = A0;
int pinSensor2 = A1;

void setup() {
  //set Arduino pint to work as outputs (form the signals and not read them)
  initArduinoPins();

  //disable both side motors and wait 1s
  stopMotors();
  delay(1000);

  //START MOVING FORWARD  
  moveForward(150);
}

void loop() {
  if(digitalRead(pinSensor1) == LOW && digitalRead(pinSensor2) == LOW){  //both sensors white
    moveForward(150);
  } else if(digitalRead(pinSensor1) == HIGH && digitalRead(pinSensor2) == HIGH){   //both sensors black
    stopMotors();
  } else if(digitalRead(pinSensor1) == HIGH){ //one black
    moveRight(100, 120);
    while(digitalRead(pinSensor2) == HIGH); //do nothing else until reach another edge (until other sensor sees line)
  } else if(digitalRead(pinSensor2) == HIGH){ //one black
    moveLeft(100, 120);
    while(digitalRead(pinSensor1) == HIGH); //do nothing else until reach another edge (until other sensor sees line)
  }
}

void moveForward(int vel){
  //START MOVING FORWARD  
  //enable side A motors at speed 'vel' and set motor polarity (direction)
  analogWrite(pinENA, vel); //speed values are 0-255
  digitalWrite(pinIN1, LOW);
  digitalWrite(pinIN2, HIGH);
  //enable side B motors at speed 'vel' and set motor polarity (direction)
  analogWrite(pinENB, vel);
  digitalWrite(pinIN3, LOW);
  digitalWrite(pinIN4, HIGH);
}

void stopMotors(){
  digitalWrite(pinENA, LOW);
  digitalWrite(pinENB, LOW);
}



void moveLeft(int vel, int angle){
  int pwm_output_fast_side = vel+angle;
  int pwm_output_slow_side = vel-angle;
  
  //side A motors
  if(pwm_output_fast_side > 255){
    pwm_output_fast_side = 255;
  }
  analogWrite(pinENA, pwm_output_fast_side);
  digitalWrite(pinIN1, LOW);
  digitalWrite(pinIN2, HIGH);

  //side B motors 
  if(pwm_output_slow_side < 0){
    analogWrite(pinENB, -pwm_output_slow_side);
    digitalWrite(pinIN3, HIGH);
    digitalWrite(pinIN4, LOW);
  } else {
    analogWrite(pinENB, pwm_output_slow_side);
    digitalWrite(pinIN3, LOW);
    digitalWrite(pinIN4, HIGH);
  }
}

void moveRight(int vel, int angle){
  int pwm_output_fast_side = vel+angle;
  int pwm_output_slow_side = vel-angle;
  
  //side A motors
  if(pwm_output_slow_side < 0){
    analogWrite(pinENA, -pwm_output_slow_side);
    digitalWrite(pinIN1, HIGH);
    digitalWrite(pinIN2, LOW);
  } else {
    analogWrite(pinENA, pwm_output_slow_side);
    digitalWrite(pinIN1, LOW);
    digitalWrite(pinIN2, HIGH);
  }

  //side B motors 
  if(pwm_output_fast_side > 255){
    pwm_output_fast_side = 255;
  }
  analogWrite(pinENB, pwm_output_fast_side);
  digitalWrite(pinIN3, LOW);
  digitalWrite(pinIN4, HIGH);
}


void initArduinoPins(){
  pinMode(pinENA, OUTPUT);
  pinMode(pinENB, OUTPUT);
  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);
  pinMode(pinIN3, OUTPUT);
  pinMode(pinIN4, OUTPUT);

  pinMode(pinSensor1, INPUT);
  pinMode(pinSensor2, INPUT);
}
