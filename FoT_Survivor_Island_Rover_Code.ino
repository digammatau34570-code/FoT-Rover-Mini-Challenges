/*
Original Author: Shawn Hettiarachchi

Block: X

Last Edited: 09/03/2025

*/

// Pin constants,  set them equal to a digital port between 10-13

const int MOTOR_POWER_A = 3;

const int MOTOR_POWER_B = 11;

const int MOTOR_DIR_A = 12;

const int MOTOR_DIR_B = 13;

// Other constants

const int MOVE_TIME_SHORT = 8500;

const int MOVE_TIME_LONG = 7000;

const int TURN_TIME = 2780;

void setup() {

  pinMode(MOTOR_POWER_A, OUTPUT);

  pinMode(MOTOR_POWER_B, OUTPUT);

  pinMode(MOTOR_DIR_A, OUTPUT);

  pinMode(MOTOR_DIR_B, OUTPUT);

}

// Loops to perform rover functions repeatedly 

void loop() {

// Assuming the craft is placed at the bottom right corner of the table

  driveForward(MOVE_TIME_LONG);

  slowDown();

  turnLeft90();

  driveForward(MOVE_TIME_SHORT);

  slowDown();

  turnLeft90();

  driveForward(MOVE_TIME_LONG);

  slowDown();

  turnLeft90();

  driveForward(MOVE_TIME_SHORT);

  slowDown();

  turnLeft90();

  while (true) {

    digitalWrite(MOTOR_DIR_A, LOW);

    digitalWrite(MOTOR_DIR_B, LOW);
    
  }
  
}

// Helper Functions

void driveForward(int duration) {

  // Moving the Chassis Forward

  digitalWrite(MOTOR_POWER_A, HIGH);

  digitalWrite(MOTOR_POWER_B, HIGH);

  digitalWrite(MOTOR_DIR_A, LOW);
  
  digitalWrite(MOTOR_DIR_B, LOW);
  
  delay(duration);
  
}

void slowDown(){

  // Slowing the Chassis Down to Prevent Skid

  digitalWrite(MOTOR_POWER_A, LOW);
  
  digitalWrite(MOTOR_POWER_B, LOW);

  delay(200);
  
}

void turnLeft90(){

  // Turning the Chassis 90 Degrees

  digitalWrite(MOTOR_DIR_A, LOW);

  digitalWrite(MOTOR_POWER_A, HIGH);

  digitalWrite(MOTOR_DIR_B, LOW);

  digitalWrite(MOTOR_POWER_B, LOW);

  delay(TURN_TIME);
  
}
