#include <Servo.h>

int servoPin = 7;  //servo control pin
int PEN_DOWN = 45; // angle of servo when pen is down
int PEN_UP = 0;   // angle of servo when pen is up

Servo penServo;

float wheel_dia=64.5; //diameter of the wheel in mm
float wheel_dia_correction = 2.0; // positive spiral out; negative spiral in
float wheel_base=119; //width wheel to wheel in mm
float wheel_base_correction_l = 0; //correction for left trun
float wheel_base_correction_r = 0; //correction for right turn

int steps_rev=512; //512 for 64x gearbox, 128 for 16x gearbox
int delay_time=2; //time between steps in ms

int L_stepper_pins[] = {2,4,3,5};
int R_stepper_pins[] = {8, 10, 9, 11};

int fwd_mask[][4] =  {{1, 0, 1, 0},
                      {0, 1, 1, 0},
                      {0, 1, 0, 1},
                      {1, 0, 0, 1}};

int rev_mask[][4] =  {{1, 0, 0, 1},
                      {0, 1, 0, 1},
                      {0, 1, 1, 0},
                      {1, 0, 1, 0}};

void setup() {
  Serial.begin(115200);
  for(int pin=0; pin<4; pin++){
    pinMode(L_stepper_pins[pin], OUTPUT);
    digitalWrite(L_stepper_pins[pin], LOW);
    pinMode(R_stepper_pins[pin], OUTPUT);
    digitalWrite(R_stepper_pins[pin], LOW);
  }
  penServo.attach(servoPin);
  delay(5000);

/* Insert here the drawing commands */
/************************************/
/* Auto generated drawingbot commands */
/* Paste them into your drawingbot sketch */
/* Auto generated drawingbot commands */
/* Paste them into your drawingbot sketch */
backward(30);
pendown();
forward(70);
right(60);
forward(70);
right(60);
forward(70);
right(60);
forward(70);
right(60);
forward(70);
right(60);
forward(70);
right(60);
penup();
/* End Auto generated drawing bot commands */
/* End Auto generated drawing bot commands */
/************************************/
  done();
}

int step(float distance){
  int steps = distance * steps_rev / ((wheel_dia + wheel_dia_correction) * 3.14159);
  return steps;  
}

void move(float distance, int mask_l[4][4], int mask_r[4][4]) {
  int steps = step(distance);
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<4; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(L_stepper_pins[pin], mask_l[mask][pin]);
        digitalWrite(R_stepper_pins[pin], mask_r[mask][pin]);
      }
      delay(delay_time);
    } 
  }
}

void forward(float distance){
  move(distance, fwd_mask, rev_mask);
}

void backward(float distance){
  move(distance, rev_mask, fwd_mask);
}
 
void right(float degrees){
  float rotation = degrees / 360.0;
  float distance = (wheel_base + wheel_base_correction_r) * 3.14159 * rotation;
  move(distance, fwd_mask, fwd_mask);
}

void left(float degrees){
  float rotation = degrees / 360.0;
  float distance = (wheel_base + wheel_base_correction_l) * 3.14159 * rotation;
  move(distance, rev_mask, rev_mask);
}

void done(){ // unlock stepper to save battery
  for(int mask=0; mask<4; mask++){
    for(int pin=0; pin<4; pin++){
      digitalWrite(R_stepper_pins[pin], LOW);
      digitalWrite(L_stepper_pins[pin], LOW);
    }
    delay(delay_time);
  }
}

void penup(){
  delay(250);
  penServo.write(PEN_UP);
  delay(250);
}

void pendown(){
  delay(250);  
  penServo.write(PEN_DOWN);
  delay(250);
}

void loop(){}
