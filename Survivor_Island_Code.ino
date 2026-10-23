 /*
 * Original Author: Shawn Hettiarachchi
 * Latest Date Modified: 10/05/26
 * Block X
 */

// Pin Constants

const int PHOTO_RESISTOR_PIN = A0;

const int TOUCH_SENSOR_PIN_A = 2;

const int TOUCH_SENSOR_PIN_B = 6;

const int LED_PIN = 9;

const int MOTOR_POWER_A = 3;

const int MOTOR_POWER_B = 11;

const int MOTOR_DIR_A = 12;

const int MOTOR_DIR_B = 13;

// Other Constants

const int MOVE_BACK_TIME = 5000;

const int TURN_TIME = 6000;

const int MOVE_FORWARD_TIME = 10000;

const int OBSTACLE_MOVE_FORWARD_TIME = 7000;

// Variables

String colorStore = "";

bool blueDetected = false;

void setup() {

  Serial.begin(9600);  

  pinMode(TOUCH_SENSOR_PIN_A, INPUT_PULLUP);

  pinMode(TOUCH_SENSOR_PIN_B, INPUT_PULLUP);

  pinMode(PHOTO_RESISTOR_PIN, INPUT_PULLUP);

  pinMode(LED_PIN, OUTPUT);

  pinMode(MOTOR_POWER_A, OUTPUT);

  pinMode(MOTOR_POWER_B, OUTPUT);

  pinMode(MOTOR_DIR_A, OUTPUT);

  pinMode(MOTOR_DIR_B, OUTPUT);

}

void loop() {

  int touchStateA = digitalRead(TOUCH_SENSOR_PIN_A);

  int touchStateB = digitalRead(TOUCH_SENSOR_PIN_B);

  int photoResistorValue = analogRead(PHOTO_RESISTOR_PIN);

  photoResistorValue = map(photoResistorValue, 0, 1023, 0, 400);

  blueDetected = false;
 
  isTouching(touchStateA, touchStateB);

  photoResistorReader(photoResistorValue);
   
}

// Helper Functions

void smartPause(unsigned long duration){

  unsigned long start = millis();

  while(millis() - start < duration){

    int color = analogRead(PHOTO_RESISTOR_PIN);

    color = map(color, 0, 1023, 0, 400);

    if (color < 45) {

      blueDetected = true;

      break;
      
    }

  }
  
}

void moveBack() {

  // Moving the Chassis Backwards

  digitalWrite(MOTOR_POWER_A, HIGH);

  digitalWrite(MOTOR_POWER_B, HIGH);

  digitalWrite(MOTOR_DIR_A, HIGH);

  digitalWrite(MOTOR_DIR_B, LOW);

  smartPause(MOVE_BACK_TIME);

}

void turnLeft90() {

  // Turning the Chassis 90 Degrees

  digitalWrite(MOTOR_DIR_A, LOW);

  digitalWrite(MOTOR_POWER_A, HIGH);

  digitalWrite(MOTOR_DIR_B, LOW);

  digitalWrite(MOTOR_POWER_B, LOW);

  smartPause(TURN_TIME);

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

 smartPause(duration);
 
}

void turnRight90() {

  // Turning the Chassis 90 Degrees

  digitalWrite(MOTOR_DIR_A, LOW);

  digitalWrite(MOTOR_POWER_A, LOW);

  digitalWrite(MOTOR_DIR_B, LOW);

  digitalWrite(MOTOR_POWER_B, HIGH);

  smartPause(TURN_TIME);

}

void isTouching(int stateA, int stateB) {

  // Touch Sensor Conditionals

  if (stateA == LOW || stateB == LOW) {

    Serial.println("The Sensor is being touched. Obstacle Detected!");

    if(!blueDetected) moveBack();

    if(!blueDetected) turnLeft90();

    if(!blueDetected) obstacleAvoidMoveForward(OBSTACLE_MOVE_FORWARD_TIME);

    if(!blueDetected) turnRight90();

    if(!blueDetected) moveForward();

    if (blueDetected == true){

      turnLeft90();

      smartPause(TURN_TIME * 2);

      moveForward();
      
    }

  } 
    
  else {

    moveForward();

  }
  
}

void photoResistorReader(int value) {

  String currentColor = "";

  if (value > 65) {

    digitalWrite(LED_PIN, LOW);

    currentColor = "Beige";
    
  }

  else if (50 <= value && value <= 65) {

    digitalWrite(LED_PIN, LOW);

    currentColor = "Green";
    
  }

  else if (value < 45) {

    digitalWrite(LED_PIN, HIGH);

    currentColor = "Blue";

    Serial.println(value);

    Serial.println("Danger! This is Blue!");
    
  }

 if (colorStore != currentColor) {

  colorStore = currentColor;

  Serial.print("The current color is:");

  Serial.println(colorStore);

  Serial.print("The value at the time of color change is:");

  Serial.print(value);

  if (colorStore == "Beige") {

    Serial.println("Little Unsafe, this is Beige!");
    
  }

  else if (colorStore == "Green") {

    Serial.println("All Good! Green!");
    
  }

  else if (colorStore == "Blue") {

    Serial.println("Danger! Blue!");
    
  } 
   
 }
  
}