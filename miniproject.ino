#include <Dynamixel_Serial.h>

#define SERVO_ControlPin 0x04
#define SERVO_SET_Baudrate 57600    // Baud rate speed which the Dynamixel will be set too (57600)
#define LED13 0x0D
#define CW_LIMIT_ANGLE 0//0x001        // lowest clockwise angle is 1, as when set to 0 it set servo to wheel mode
#define CCW_LIMIT_ANGLE 0       // Highest anit-clockwise angle is 0XFFF, as when set to 0 it set servo to wheel mode
//#define WAVEIN_PIN 4

unsigned long sampleTimer = 0;
unsigned long sampleInterval = 100; //100 ms = 10Hz rate

void setup() {
  Serial.begin(57600);
  Serial.flush();
  Serial.begin(SERVO_SET_Baudrate);
  Dynamixel.begin(57600);
  Dynamixel.setDirectionPin(SERVO_ControlPin);
  
  Dynamixel.setProfileAcceleration(0x02, 20);

  Dynamixel.setProfileVelocity(0x02, 20);

  Dynamixel.setID(0x06, 0x02); //change between IDs (old ID, new ID)
  
  Dynamixel.setPosPgain(0x02, 850); //P-gain set once (loop setup)
  
  Dynamixel.setHoldingTorque(0x01, true);
  Dynamixel.setHoldingTorque(0x02, true);
  Dynamixel.setHoldingTorque(0x03, true);  //enable(true)/disable(false) torque
  Dynamixel.setHoldingTorque(0x04, true);
  Dynamixel.setHoldingTorque(0x05, true);
}

void loop(){
  /*unsigned long currMillis = millis();
  if(currMillis - sampleTimer >= sampleInterval)
  {
    sampleTimer = currMillis;
    Serial.println(Dynamixel.getTemp(0x02));
  }*/
  Dynamixel.setGoalPosition(0x02, 2700); //servo 2 moves to the specified position.
  delay(1000); //waits for the servo to get in that position
  Dynamixel.setGoalPosition(0x02, 2200); 
  delay(1000);
  //Dynamixel.getTemp(0x02); //reads present temperature of servo 2
  char temp = Dynamixel.getTemp(0x02); // 
  char pos = Dynamixel.getPosition(0x02);
  if(temp >= 25){
    Dynamixel.setGoalPosition(0x02, 2048);
    delay(2000);
    Dynamixel.setHoldingTorque(0x02, false);
  }
  delay(100);
  if(temp < 25){
    Dynamixel.setHoldingTorque(0x02, true);
  }
  delay(500);
}
