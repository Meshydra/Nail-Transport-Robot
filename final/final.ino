// IR Sensors
#define LEFT_IR_PIN 6
#define CENTER_IR_PIN 7
#define RIGHT_IR_PIN 11

// Motor one
#define MOTOR1_ENABLE_PIN  9
#define MOTOR1_INPUT_PIN_1 2
#define MOTOR1_INPUT_PIN_2 3

// motor two
#define MOTOR2_ENABLE_PIN 10
#define MOTOR2_INPUT_PIN_1 4
#define MOTOR2_INPUT_PIN_2 5

//Audio Feedback
#define BUZZER_PIN 13

//Visual Feedback
#define LEFT_LED_PIN 0
#define RIGHT_LED_PIN 1

// Obstacle avoid
#define ECHO_PIN A3
#define TRIG_PIN A2

int Speed = 50; // speed of this robot

void setup()
{
  //IR Sensors
  pinMode(LEFT_IR_PIN, INPUT);
  pinMode(CENTER_IR_PIN, INPUT);
  pinMode(RIGHT_IR_PIN, INPUT);

  //Settings the motors
  pinMode(MOTOR1_ENABLE_PIN , OUTPUT);
  pinMode(MOTOR1_INPUT_PIN_1, OUTPUT);
  pinMode(MOTOR1_INPUT_PIN_2, OUTPUT);
  pinMode(MOTOR2_INPUT_PIN_1, OUTPUT);
  pinMode(MOTOR2_INPUT_PIN_2, OUTPUT);
  pinMode(MOTOR2_ENABLE_PIN, OUTPUT);

  //Setting the Audio
  pinMode(BUZZER_PIN, OUTPUT);

  //Obstacle avoid
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
}

void loop()
{
  bool LEFT_IR_PINV = digitalRead(LEFT_IR_PIN);
  bool CENTER_IR_PINV = digitalRead(CENTER_IR_PIN);
  bool RIGHT_IR_PINV = digitalRead(RIGHT_IR_PIN);

  digitalWrite(TRIG_PIN, LOW);
  delay(5);
  digitalWrite(TRIG_PIN, HIGH);
  delay(50);
  digitalWrite(TRIG_PIN, LOW);

  int duration = pulseIn(ECHO_PIN, HIGH);

  // 29 is used as a conversion factor from microseconds to centimeters
  int cm = duration / 29 / 2;

  if (LEFT_IR_PINV == 0 && CENTER_IR_PINV == 1 && RIGHT_IR_PINV == 0)
  {
    forward();
  }
  else if (LEFT_IR_PINV == 0 && CENTER_IR_PINV == 0 && RIGHT_IR_PINV == 0)
  {
    stop();
    emitBeep();
  }
  else if (LEFT_IR_PINV == 1 && CENTER_IR_PINV == 1 && RIGHT_IR_PINV == 0)
  {
    turnLeft();
  }
  else if (LEFT_IR_PINV == 0 && CENTER_IR_PINV == 1 && RIGHT_IR_PINV == 1)
  {
    forward();
  }
  else if (LEFT_IR_PINV == 1 && CENTER_IR_PINV == 0 && RIGHT_IR_PINV == 0)
  {
    turnLeft();
    blinkLeft();
  }
  else if (LEFT_IR_PINV == 0 && CENTER_IR_PINV == 0 && RIGHT_IR_PINV == 1)
  {
    turnRight();
    blinkRight();
  }
  if (LEFT_IR_PINV == 1 && CENTER_IR_PINV == 1 && RIGHT_IR_PINV == 1)
  {
    stop();
    blink();
  }
}

void forward()
{
  analogWrite(MOTOR1_ENABLE_PIN , Speed);
  analogWrite(MOTOR2_ENABLE_PIN, Speed);
  digitalWrite(MOTOR1_INPUT_PIN_1, HIGH);
  digitalWrite(MOTOR1_INPUT_PIN_2, LOW);
  digitalWrite(MOTOR2_INPUT_PIN_1, HIGH);
  digitalWrite(MOTOR2_INPUT_PIN_2, LOW);
}

void turnLeft()
{
  analogWrite(MOTOR1_ENABLE_PIN , Speed/2);
  analogWrite(MOTOR2_ENABLE_PIN, Speed/2);
  digitalWrite(MOTOR1_INPUT_PIN_1, LOW);
  digitalWrite(MOTOR1_INPUT_PIN_2, HIGH);
  digitalWrite(MOTOR2_INPUT_PIN_1, HIGH);
  digitalWrite(MOTOR2_INPUT_PIN_2, LOW);
}

void turnRight()
{
  analogWrite(MOTOR1_ENABLE_PIN , Speed/2);
  analogWrite(MOTOR2_ENABLE_PIN, Speed/2);
  digitalWrite(MOTOR1_INPUT_PIN_1, HIGH);
  digitalWrite(MOTOR1_INPUT_PIN_2, LOW);
  digitalWrite(MOTOR2_INPUT_PIN_1, LOW);
  digitalWrite(MOTOR2_INPUT_PIN_2, HIGH);
}

void stop() {
  digitalWrite(MOTOR1_INPUT_PIN_1, LOW);
  digitalWrite(MOTOR1_INPUT_PIN_2, LOW);
  digitalWrite(MOTOR2_INPUT_PIN_1, LOW);
  digitalWrite(MOTOR2_INPUT_PIN_2, LOW);
  analogWrite(MOTOR1_ENABLE_PIN , 0);
  analogWrite(MOTOR2_ENABLE_PIN, 0);
  emitBeep();
}

void blinkLeft(){
  digitalWrite(LEFT_LED_PIN, HIGH);   // turn on the left LED
  delay(500);                       // wait for 500 milliseconds
  digitalWrite(LEFT_LED_PIN, LOW);    // turn off the left LED
}

void blinkRight(){
  digitalWrite(RIGHT_LED_PIN, HIGH);   // turn on the right LED
  delay(500);                       // wait for 500 milliseconds
  digitalWrite(RIGHT_LED_PIN, LOW);    // turn off the right LED
}

void blink(){
  digitalWrite(RIGHT_LED_PIN, HIGH);   // turn on the right LED
  digitalWrite(LEFT_LED_PIN, HIGH);   // turn on the left LED
  delay(500);                       // wait for 500 milliseconds
  digitalWrite(LEFT_LED_PIN, LOW);    // turn off the left LED                      // wait for 500 milliseconds
  digitalWrite(RIGHT_LED_PIN, LOW);    // turn off the right LED
}

// Function to emit a short beep sound
void emitBeep() {
  int beepDuration = 100; // Duration (in milliseconds) that the beep sound should be emitted for
  
  tone(BUZZER_PIN, 1000, beepDuration); // Emit a 1kHz beep sound for the specified duration
  delay(beepDuration); // Wait for the beep to finish before continuing
}