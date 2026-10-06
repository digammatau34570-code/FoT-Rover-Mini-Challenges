 /*
 * Original Author: Shawn Hettiarachchi
 * Latest Date Modified: 10/05/26
 * Block X
 */

// Pin Constants

const int TOUCH_SENSOR_PIN_A = 2;

const int TOUCH_SENSOR_PIN_B = 6;

const int MOTOR_POWER_A = 3;

const int MOTOR_POWER_B = 11;

const int MOTOR_DIR_A = 12;

const int MOTOR_DIR_B = 13;

// Other Constants

const int MOVE_BACK_TIME = 5000;

const int TURN_TIME = 6000;

const int MOVE_FORWARD_TIME = 10000;

const int OBSTACLE_MOVE_FORWARD_TIME = 7000;

void setup() {

  Serial.begin(9600);  

  pinMode(TOUCH_SENSOR_PIN_A, INPUT_PULLUP);

  pinMode(TOUCH_SENSOR_PIN_B, INPUT_PULLUP);

  pinMode(MOTOR_POWER_A, OUTPUT);

  pinMode(MOTOR_POWER_B, OUTPUT);

  pinMode(MOTOR_DIR_A, OUTPUT);

  pinMode(MOTOR_DIR_B, OUTPUT);

}

void loop() {

  moveForward();

  int touchStateA = digitalRead(TOUCH_SENSOR_PIN_A);

  int touchStateB = digitalRead(TOUCH_SENSOR_PIN_B);

  if (touchStateA == HIGH || touchStateB == HIGH) {

    Serial.println("The Sensor is being touched.");

    moveBack();

    turnLeft90();

    obstacleAvoidMoveForward(OBSTACLE_MOVE_FORWARD_TIME);

    turnRight90();

    moveForward();

  } if (touchStateA == LOW && touchStateB == LOW) {

    Serial.println("The Sensor is untouched.");

    moveForward();

  } else {
    
    moveForward();
    
  }
  
}

// Helper Functions

void moveBack() {

  // Moving the Chassis Backwards

  digitalWrite(MOTOR_POWER_A, HIGH);

  digitalWrite(MOTOR_POWER_B, HIGH);

  digitalWrite(MOTOR_DIR_A, HIGH);

  digitalWrite(MOTOR_DIR_B, LOW);

  delay(MOVE_BACK_TIME);

}

void turnLeft90() {

  // Turning the Chassis 90 Degrees

  digitalWrite(MOTOR_DIR_A, LOW);

  digitalWrite(MOTOR_POWER_A, HIGH);

  digitalWrite(MOTOR_DIR_B, LOW);

  digitalWrite(MOTOR_POWER_B, LOW);

  delay(TURN_TIME);

}

void moveForward() {

  // Moving the Chassis Forward

  digitalWrite(MOTOR_POWER_A, HIGH);

  digitalWrite(MOTOR_POWER_B, HIGH);

  digitalWrite(MOTOR_DIR_A, LOW);

  digitalWrite(MOTOR_DIR_B, LOW);

}

void obstacleAvoidMoveForward(int duration){

 digitalWrite(MOTOR_POWER_A, HIGH);

 digitalWrite(MOTOR_POWER_B, HIGH);

 digitalWrite(MOTOR_DIR_A, LOW);

 digitalWrite(MOTOR_DIR_B, LOW);

 delay(duration);
 
}

void turnRight90() {

  // Turning the Chassis 90 Degrees

  digitalWrite(MOTOR_DIR_A, LOW);

  digitalWrite(MOTOR_POWER_A, LOW);

  digitalWrite(MOTOR_DIR_B, LOW);

  digitalWrite(MOTOR_POWER_B, HIGH);

  delay(TURN_TIME);

}

