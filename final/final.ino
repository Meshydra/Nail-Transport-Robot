// IR sensor pins
#define LEFT_IR_PIN 6
#define CENTER_IR_PIN 7
#define RIGHT_IR_PIN 11

// Motor one pins
#define MOTOR1_ENABLE_PIN 9
#define MOTOR1_INPUT_PIN_1 2
#define MOTOR1_INPUT_PIN_2 3

// Motor two pins
#define MOTOR2_ENABLE_PIN 10
#define MOTOR2_INPUT_PIN_1 4
#define MOTOR2_INPUT_PIN_2 5

// Buzzer pin
#define BUZZER_PIN 13

// LED pins
#define LEFT_LED_PIN 8
#define RIGHT_LED_PIN 12


// Obstacle avoid
#define ECHO_PIN A3
#define TRIG_PIN A2

// Variables to store IR sensor values
int leftIRValue;
int centerIRValue;
int rightIRValue;

//Controls the Speed of the robot
int speed = 90;

void setup()
{

  // Set motor pins as output
  pinMode(MOTOR1_ENABLE_PIN, OUTPUT);
  pinMode(MOTOR1_INPUT_PIN_1, OUTPUT);
  pinMode(MOTOR1_INPUT_PIN_2, OUTPUT);
  pinMode(MOTOR2_ENABLE_PIN, OUTPUT);
  pinMode(MOTOR2_INPUT_PIN_1, OUTPUT);
  pinMode(MOTOR2_INPUT_PIN_2, OUTPUT);

  // Set IR sensor pins as input
  pinMode(LEFT_IR_PIN, INPUT);
  pinMode(CENTER_IR_PIN, INPUT);
  pinMode(RIGHT_IR_PIN, INPUT);

  // Set LED and buzzer pins as output
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LEFT_LED_PIN, OUTPUT);
  pinMode(RIGHT_LED_PIN, OUTPUT);

  //Obstacle avoid
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
}

void loop(){
  // Read IR sensor values
  leftIRValue = digitalRead(LEFT_IR_PIN);
  centerIRValue = digitalRead(CENTER_IR_PIN);
  rightIRValue = digitalRead(RIGHT_IR_PIN); 

  digitalWrite(BUZZER_PIN, HIGH);    
  digitalWrite(LEFT_LED_PIN, HIGH);    
  digitalWrite(RIGHT_LED_PIN, HIGH);

// Check the values of the IR sensors and perform the appropriate action
if (leftIRValue == 0 && centerIRValue == 1 && rightIRValue == 0)
  {
    forward();
  }
  else if (leftIRValue == 0 && centerIRValue == 0 && rightIRValue == 0)
  {    
    uTurn();y
  }
  else if (leftIRValue == 1 && centerIRValue == 1 && rightIRValue == 0)
  {
      turnLeft();
  }
  else if (leftIRValue == 0 && centerIRValue == 1 && rightIRValue == 1)
  {
      turnRight();
  }
  else if (leftIRValue == 1 && centerIRValue == 0 && rightIRValue == 0)
  {
    blink(LEFT_LED_PIN);
    turnLeft();
  }
  else if (leftIRValue == 0 && centerIRValue == 0 && rightIRValue == 1)
  {
    blink(RIGHT_LED_PIN);
    turnRight();
  }
  else if (leftIRValue == 1 && centerIRValue == 1 && rightIRValue == 1)
  {
    turnRight();
  }
  else if (leftIRValue == 1 && centerIRValue == 0 && rightIRValue == 1)
  {
    stop();
  }
}

// Function to move the robot forward
void forward()
{
  
  analogWrite(MOTOR1_ENABLE_PIN , speed);
  analogWrite(MOTOR2_ENABLE_PIN, speed);
  digitalWrite(MOTOR1_INPUT_PIN_1, HIGH);
  digitalWrite(MOTOR1_INPUT_PIN_2, LOW);
  digitalWrite(MOTOR2_INPUT_PIN_1, HIGH);
  digitalWrite(MOTOR2_INPUT_PIN_2, LOW);
}

// Function to turn the robot left
void turnLeft()
{
  
  analogWrite(MOTOR1_ENABLE_PIN , speed);
  analogWrite(MOTOR2_ENABLE_PIN, speed);
  digitalWrite(MOTOR1_INPUT_PIN_1, LOW);
  digitalWrite(MOTOR1_INPUT_PIN_2, HIGH);
  digitalWrite(MOTOR2_INPUT_PIN_1, HIGH);
  digitalWrite(MOTOR2_INPUT_PIN_2, LOW);
}

void turnRight()
{
  analogWrite(MOTOR1_ENABLE_PIN , speed);
  analogWrite(MOTOR2_ENABLE_PIN, speed);
  digitalWrite(MOTOR1_INPUT_PIN_1, HIGH);
  digitalWrite(MOTOR1_INPUT_PIN_2, LOW);
  digitalWrite(MOTOR2_INPUT_PIN_1, LOW);
  digitalWrite(MOTOR2_INPUT_PIN_2, HIGH);
}


// Stop the robot
void stop()
{
  
  digitalWrite(MOTOR1_INPUT_PIN_1, LOW);
  digitalWrite(MOTOR1_INPUT_PIN_2, LOW);
  digitalWrite(MOTOR2_INPUT_PIN_1, LOW);
  digitalWrite(MOTOR2_INPUT_PIN_2, LOW);
  analogWrite(MOTOR1_ENABLE_PIN, 0);
  analogWrite(MOTOR2_ENABLE_PIN, 0);
}

void uTurn()
{
  turnRight(); // Make a left turn
}

void blink(int pin){
    digitalWrite(pin, LOW);
}
