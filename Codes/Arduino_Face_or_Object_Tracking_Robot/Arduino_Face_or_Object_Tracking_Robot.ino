// Arduino Obstracle Tracking Robot using Pixy Cam 2


// Define components
#define I2C
#include <Pixy2I2C.h>
Pixy2I2C pixy;
#include <AFMotor.h>


// This will hold the speacifications of the main Pixy object
int xAxis = 0;  
int yAxis = 0;
int width = 0;
int height = 0;
uint32_t lastBlockTime = 0;
uint16_t blocks;

// Define the motors
AF_DCMotor RB(2);
AF_DCMotor LB(1);
AF_DCMotor RF(3);
AF_DCMotor LF(4);


void setup()
{
  Serial.begin(9600);
  Serial.print("Starting...\n");
  pixy.init(); 

// Set the initial sppeed of the motors
  LF.setSpeed(150);
  LB.setSpeed(120);
  RF.setSpeed(120);
  RB.setSpeed(120);

// Set every motors off Initially
  LF.run(RELEASE);
  LB.run(RELEASE);
  RF.run(RELEASE);
  RB.run(RELEASE);

}

void loop()
{
  int i;
  // grab blocks!
  blocks = pixy.ccc.getBlocks();


  // If there are detect blocks, print them!
  if (pixy.ccc.numBlocks)
  {
    xAxis = pixy.ccc.blocks[0].m_x;
    yAxis = pixy.ccc.blocks[0].m_y;
    width = pixy.ccc.blocks[0].m_width;
    height = pixy.ccc.blocks[0].m_height;

    Serial.print("X: ");
    Serial.print(xAxis);
    Serial.print("    Y: ");
    Serial.print(yAxis);
    Serial.print("    w: ");
    Serial.print(width);
    Serial.print("    h: ");
    Serial.println(height);

// Set robot moving conditions

// xAxis for Left and Right Movement
    if (xAxis < 40) {
      left();
      //delay(10);

    } else if (xAxis > 230) {
      right();

// height for forword and backword movemnt
    } else if (height < 30) {
      fw();

    } else if (height > 40) {
      bw();

    } else {
      st();
    }

// Set robot stop if pixy cannot detect any object
  } else {
    Serial.println("Undetecte");
    st();
  }



}

// Functions for different movement of the robot
void fw() {
  LF.run(FORWARD);
  LB.run(FORWARD);
  RF.run(FORWARD);
  RB.run(FORWARD);
  Serial.println("Forward");
  delay(10);
}
void bw() {
  LF.run(BACKWARD);
  LB.run(BACKWARD);
  RF.run(BACKWARD);
  RB.run(BACKWARD);
  Serial.println("Backward");
  delay(10);
}

void left() {
  LF.run(BACKWARD);
  LB.run(FORWARD);
  RF.run(FORWARD);
  RB.run(BACKWARD);
  Serial.println("Left");
  delay(10);
}

void right() {
  LF.run(FORWARD);
  LB.run(BACKWARD);
  RF.run(BACKWARD);
  RB.run(FORWARD);
  Serial.println("Right");
  delay(10);
}

void lt() {
  LF.run(RELEASE);
  LB.run(RELEASE);
  RF.run(FORWARD);
  RB.run(FORWARD);

  Serial.println("Left Turn");
  delay(10);

}

void rt() {
  LF.run(FORWARD);
  LB.run(FORWARD);
  RF.run(RELEASE);
  RB.run(RELEASE);
  Serial.println("Right Turn");
  delay(10);

}
void st() {
  LF.run(RELEASE);
  LB.run(RELEASE);
  RF.run(RELEASE);
  RB.run(RELEASE);
  Serial.println("Stop");
  delay(10);
}
