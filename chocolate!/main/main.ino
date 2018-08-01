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

//int move_time = 1000;

void setup()
{
  Serial.begin(115200);
  pinMode(interrupt_pin_2, INPUT_PULLUP);
  pinMode(interrupt_pin_3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_2), left_motor_pulse_interrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_3), right_motor_pulse_interrupt, RISING);
}

void loop()
{
  Serial.println(sensor.distance_down());
  wheelie_mode();

  Serial.println("test complete!");
  Serial.println("exit run");
  exit(0);


}

 void figure_of_eight()
// Completes a figure of eight and returns to its starting position.
{
  int time_unit = 1000;
  for (int x = 0; x < 3; x++) {
    timed_forwards(time_unit);
    turn_left_90();
    Serial.println("loop complete");
  }
  timed_forwards(time_unit * 2);
  Serial.println("long forwards complete");
  for (int x = 0; x < 3; x++) {
    turn_right_90();
    timed_forwards(time_unit);
    Serial.println("loop2 complete");
  }
}

void taped_line()
// This can cover the taped line with a rather small error.
{
  timed_forwards(6000);
}

void turn_left_90()
// This enables the rover to move left.
{
  left_motor.reset_pulse();
  left_motor.reverse(200);
  right_motor.forward(200);
  while (left_motor.get_pulse_count() <= 52) {
    delay(1);
  }
  left_motor.stop();
  right_motor.stop();

  delay(1000);
}

void turn_right_90()
//Enables the rover to turn right.
{
  right_motor.reset_pulse();
  left_motor.forward(200);
  right_motor.reverse(200);
  while (right_motor.get_pulse_count() <= 49) {
    delay(1);
  }
  left_motor.stop();
  right_motor.stop();

  delay(1000);
}

void timed_forwards(int move_time)
//This makes the rover go forwards with timings.
{
  // Move robot forwards for one second
  left_motor.forward(200);
  delay(20);
  right_motor.forward(330);


  delay(move_time);
  Serial.println(move_time);

  left_motor.stop();
  right_motor.stop();

  delay(1000);
}

void turn_left_test()
// the most effective testing method.
{
  Serial.println("message from function");
  for (int ticks_number = 50; ticks_number <= 60; ticks_number = ticks_number + 1) {
    for (int x = 0; x < 4; x++) {
      left_motor.reset_pulse();
      Serial.println("motors on");
      left_motor.reverse(speed);
      right_motor.forward(speed);
      while (left_motor.get_pulse_count() <= ticks_number) {
        delay(1);
        Serial.println(left_motor.get_pulse_count());
        Serial.println(right_motor.get_pulse_count());
      }

      // Stop the robots motors
      left_motor.stop();
      right_motor.stop();
      Serial.println("motors stop");
      delay(1000);
    }
    delay(5000);

  }


  exit(0);


}

void turn_right_test()
// The most effective test for turns.
{
  for (int ticks_number = 40; ticks_number <= 50; ticks_number = ticks_number + 1) {
    for (int x = 0; x < 4; x++) {
      right_motor.reset_pulse();
      right_motor.reverse(speed);
      left_motor.forward(speed);
      while (right_motor.get_pulse_count() <= ticks_number) {
        delay(1);
        Serial.println(left_motor.get_pulse_count());
        Serial.println(right_motor.get_pulse_count());
      }
      // Stop the robots motors
      left_motor.stop();
      right_motor.stop();
      delay(1000);
    }
    delay(5000);

  }

  exit(0);
}

void forwards_test()
// Iterative testing for directional callibration.
{
  for (int ticks_number = 180; ticks_number <= 250; ticks_number = ticks_number + 10) {
    left_motor.forward(200);
    //right_motor.forward(ticks_number);
    right_motor.forward(200);
    delay(5000);

    left_motor.stop();
    right_motor.stop();
    Serial.println("motors stop");

    delay(5000);
  }
}

void robot_movement_test()
// The initial test for robot motor testing.
{
  // Move robot forwards for one second
  left_motor.forward(speed);
  right_motor.forward(speed);

  delay(1000);

  left_motor.forward(0.25 * speed);
  right_motor.forward(0.25 * speed);

  delay(1000);

  left_motor.forward(1.25 * speed);
  right_motor.forward(1.25 * speed);

  delay(500);

  // Turn right
  left_motor.forward(speed);
  right_motor.reverse(speed);

  delay(1000);

  // Turn left
  left_motor.reverse(speed);
  right_motor.forward(speed);

  delay(5000);

  // Move robot backwards for one second
  left_motor.reverse(speed);
  right_motor.reverse(speed);

  delay(1000);

  // Move robot forwards for one second
  left_motor.forward(speed);
  right_motor.forward(speed);

  delay(1000);

  // Stop the robots motors
  left_motor.stop();
  right_motor.stop();
}

void wheelie_mode()
//The wheelie that only the smallest rover can attempt without garunteed fail.
//This also serves as our demo mode.

{
  timed_forwards(1000);
  Serial.println(sensor.distance_down());
  while(sensor.distance_down() <16){
    timed_forwards(1000);
    Serial.println(sensor.distance_down());
    
    }
  left_motor.reverse(speed);
  right_motor.reverse(speed);
  delay(1000);
  
  
  for (int x = 0; x < 4; x++) {
    timed_forwards(1500);
    turn_right_90();
    turn_right_90();
  }

  robot_movement_test();

}

void left_motor_pulse_interrupt()
{
  left_motor.inc_pulse();
}

void right_motor_pulse_interrupt()
{
  right_motor.inc_pulse();
}



