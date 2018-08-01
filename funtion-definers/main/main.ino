#include "Arduino.h"
#include "Motor.h"
#include "Sensor.h"


namespace 
{
  const byte interrupt_pin_2 = 2;
  const byte interrupt_pin_3 = 3;

  auto speed = 200;

  // Instantiate the two motor objects, passing in the side of the robot the motor is on
  Motor left_motor{"left"};
  Motor right_motor{"right"};

  // Instantiate a sensor object
  Sensor sensor{};
}

int right_speed = 255;

void right_turn()
{
  left_motor.forward(speed);
  right_motor.reverse(speed); 
}

void left_turn()
{
  left_motor.reverse(speed);
  right_motor.forward(speed);  
}
void full_forward()
{
  right_motor.forward(speed);
  left_motor.forward(speed);
}

void full_stop()
{
  right_motor.stop();
  left_motor.stop();
}

void full_reverse()
{
  right_motor.reverse(speed);
  left_motor.reverse(speed);
}

int flag;
size_t index = 0;
char delays[200];
int timed_start;
const int powwwwer = 180;
int l_powwwwer, r_powwwwer;
#define MAGIC_GET_SLOWEST(smaller, bigger) ((int)(powwwwer * ((double)(smaller)) / ((double)(bigger))))

void setup()
{
  timed_start = millis();
  Serial.begin(115200);
  pinMode(interrupt_pin_2, INPUT_PULLUP);
  pinMode(interrupt_pin_3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_2), left_motor_pulse_interrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_3), right_motor_pulse_interrupt, RISING);
  flag = 3;
  /*int bob = millis();
  while(millis() - bob <= 10000)
  {
    left_motor.forward(255);
    right_motor.forward(255);
  }
  full_stop();
  int l_count = left_motor.get_pulse_count();
  int r_count = right_motor.get_pulse_count();
  if (l_count > r_count) {
    l_powwwwer = MAGIC_GET_SLOWEST(r_count, l_count);
    r_powwwwer = powwwwer;
  } else {
    r_powwwwer = MAGIC_GET_SLOWEST(l_count, r_count);
    l_powwwwer = powwwwer;
  }
  delay(10000);
  */
}
void loop()
{
  
  /*while (right_motor.get_pulse_count() != left_motor.get_pulse_count()) {
    if (right_motor.get_pulse_count() > left_motor.get_pulse_count()) {
      right_motor.forward(r_powwwwer*0.5);
      left_motor.forward(l_powwwwer);
    } else {
      left_motor.forward(l_powwwwer*0.5);
      right_motor.forward(r_powwwwer);
    }
      Serial.print("     \t");
      Serial.print(left_motor.get_pulse_count());
      Serial.print(" ");
      Serial.println(right_motor.get_pulse_count());
  }
  
  left_motor.forward(l_powwwwer);
  right_motor.forward(r_powwwwer);
  Serial.print(l_powwwwer);
  Serial.print(" ");
  Serial.print(r_powwwwer);
  Serial.print("\t");
  Serial.print(left_motor.get_pulse_count());
  Serial.print(" ");
  Serial.println(right_motor.get_pulse_count());*/
  /*int time1 = millis() - timed_start;
  Serial.println(sensor.distance_forwards());
  if (sensor.distance_forwards() > 20 && sensor.distance_forwards()) {
    full_forward();
  } else {
    delays[index++] = time1;
    timed_start = millis();
    right_turn();
    flag -= 1;
    while (!flag) {
      full_stop();
      while (index) {
        full_reverse();
        delay(delays[--index] * 0.75);
        left_turn();
        delay(820);
        full_stop();
      }
      while (1) {}
    }
    delay(820);
    full_stop();
  }
  delay(50);
  */
  /*
  if (sensor.distance_forwards() < 15 && sensor.distance_forwards() != 0){
    left_turn();
    delay(930);
    int bobv2 = sensor.distance_forwards();
    right_turn();
    delay(1860);
    int bobv3 = sensor.distance_forwards();
    left_turn();
    delay(930);
    if (bobv2 > bobv3)
    {
      left_turn();
      delay(930);
    } else {
      right_turn();
      delay(930);
    }
  } else {
    full_forward();
  }
  */
 // bool left = random(0, 1);
  /*int fwea;
  int twoo;
  while (sensor.distance_forwards() < 15) {
    fwea = millis() + 1000;
    twoo = millis() + 5000;
    while (fwea > millis() || twoo > millis()) {
      if (sensor.distance_forwards() < 15) {
        fwea = millis() + 750;
      }
      right_turn();
    }
    if (fwea > twoo) {
      left_turn();
      delay(930);
      int bobv2 = sensor.distance_forwards();
      right_turn();
      delay(1860);
      int bobv3 = sensor.distance_forwards();
      left_turn();
      delay(930);
      if (bobv2 > bobv3)
      {
        left_turn();
        delay(930);
      } else {
        right_turn();
        delay(930);
      }
    } else {
      left_turn();
      delay(375);
    }
  }
  full_forward();
  delay(100); */
  int fwea;
  int twoo;
  while (sensor.distance_forwards() < 15 && sensor.distance_forwards()) {
    int count1 = 0;
    int count2 = 0;
    int plz = random(0, 2);
    while (count1 < 8) {
      if(plz) {
        right_turn();
      } else {
        left_turn();
      }
      count1++;
      if (sensor.distance_forwards() < 15 && sensor.distance_forwards()) {
        count2++;
        if (count2 > 100)
        {
          left_turn();
          delay(930);
          int bobv2 = sensor.distance_forwards();
          right_turn();
          delay(1860);
          int bobv3 = sensor.distance_forwards();
          left_turn();
          delay(930);
          if (bobv2 > bobv3)
          {
            left_turn();
            delay(930);
          } else {
            right_turn();
            delay(930);
          }
          break;
        }
        count1 = 0;        
      }
    }
    /*if (count2 <= 100) {
      left_turn();
      delay(600);
    }*/
  }
  full_forward();
  delay(100); 
  /*int fwea;
  int twoo;
  int jed = 15;
  while (sensor.distance_forwards() < jed && sensor.distance_forwards() != 0) {
    fwea = millis() + 1000;
    twoo = millis() + 5000;
    while (fwea > millis() || twoo > millis()) {
      if (sensor.distance_forwards() < jed && sensor.distance_forwards() != 0) {
        fwea = millis() + 1000;
      }
      right_turn();
      delay(50);
      full_stop();
    }
    if (fwea > twoo) {
      jed -= 1;
    }
  }
  full_forward();
  delay(500);*/
}

void left_motor_pulse_interrupt()
{
  left_motor.inc_pulse();
}

void right_motor_pulse_interrupt()
{
  right_motor.inc_pulse();
}
