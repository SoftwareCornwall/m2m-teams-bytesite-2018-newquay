#include "Arduino.h"
#include "Motor.h"
#include "Sensor.h"

namespace 
{
  const byte interrupt_pin_2 = 2;
  const byte interrupt_pin_3 = 3;
  int const LEDR = 14;
  int const LEDL = 15;

  auto speed = 245;
  auto speedL = 255;
  auto speedR = 210;

  int right_turn_count = 0;

  // Instantiate the two motor objects, passing in the side of the robot the motor is on
  Motor left_motor{"left"};
  Motor right_motor{"right"};

  // Instantiate a sensor object
  Sensor sensor{};
}

void setup()
{
  right_at_wall();
  Serial.begin(115200);
  pinMode(interrupt_pin_2, INPUT_PULLUP);
  pinMode(interrupt_pin_3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_2), left_motor_pulse_interrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_3), right_motor_pulse_interrupt, RISING);
  forward();
  pinMode(LEDR, OUTPUT);
  pinMode(LEDL, OUTPUT);
}


void loop(){
  
  right_at_wall();
  dont_hit_wall();
}


void half_spin(){
  left_motor.forward(speed);
  right_motor.reverse(speed);

  delay(1530);

  stop_motor();
}

void reverse(){
  
  left_motor.reverse(speed);
  right_motor.reverse(speed);

  delay(3000);

  stop_motor();
}
   
void spin(){

  left_motor.forward(speed);
  right_motor.reverse(speed);

  delay(3135);

  stop_motor();
}

void stop_motor(){

  left_motor.stop();
  right_motor.stop();

  delay(1);

  }

void forward(){
  left_motor.forward(speedL);
  right_motor.forward(speedR);

  delay(10);
  }
  
void forward1(){

  even_pulse_forward();

  delay(1);

  Serial.println(left_motor.get_pulse_count());
  Serial.println(right_motor.get_pulse_count());
  
  
  }

void left_turn(){
  
  left_motor.reverse(speed);
  right_motor.forward(speed);

  delay(730);
  
  }

void right_turn(){
  
  left_motor.forward(speed);
  right_motor.reverse(speed);

  delay(835);

  stop_motor();
  
  }

void eight(){
  forward();
  right_turn();
  forward();
  right_turn();
  forward();
  right_turn();
  forward();
  forward();
  left_turn();
  forward();
  left_turn();
  forward();
  left_turn();
  forward();
  }

void flashing_lights(){
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDL, HIGH);
  delay(500);
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDL, LOW);
  delay(500);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDL, LOW);
  delay(500);
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDL, HIGH);
  delay(500);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDL, LOW);
  delay(500);
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDL, HIGH);
  delay(500);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDL, LOW);
  delay(500);
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDL, HIGH);
  delay(500);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDL, LOW);
  delay(500);
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDL, HIGH);
  delay(500);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDL, LOW);
  delay(500);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDL, HIGH);
  delay(500);
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDL, LOW);
  delay(500);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDL, LOW);
  delay(500);
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDL, HIGH);
  delay(500);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDL, LOW);
  delay(500);
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDL, HIGH);
  delay(500);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDL, LOW);
  delay(500);
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDL, HIGH);
  delay(500);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDL, LOW); 
  delay(500);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDL, HIGH);
  delay(500);
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDL, LOW);
  delay(500);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDL, HIGH);
  delay(500);
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDL, LOW);
  delay(500);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDL, HIGH);
  delay(500);
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDL, LOW);
  delay(100);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDL, LOW);
  delay(100);
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDL, HIGH);
  delay(100);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDL, LOW);
  delay(100);
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDL, HIGH);
   
  }

void edge(){
  if(sensor.distance_down() >= 14){    
    stop_motor();    
    delay(100);
    reverse();
    stop_motor();
    endshow();    
    exit(0);
    }
  else if(sensor.distance_down()<14){
    forward();
    delay(40);
    } 
  }

void endshow(){
   reverse();

   spin();

   flashing_lights();
    
}

void moonwalk(){

      stop_motor();
      spin();
      delay(100);
      reverse();
      delay(1000);
  
    
    }
   
void almostend(){
    moonwalk();
    delay(500);
    half_spin();
    delay(10);
    edge();
  }

void dont_hit_wall(){
  if(sensor.distance_forwards()>20 || sensor.distance_forwards()<1){
    
   forward1();
    
    }

  if (right_turn_count > 1){
      stop_motor();
      reverse();
      almostend();
      }
    
    }
 
  
void right_at_wall(){
  if(sensor.distance_forwards()>20 || sensor.distance_forwards()<1){
    
   forward1();
    
    }

  if (right_turn_count < 2){
      right_turn();
      right_turn_count++;
      }
    
    }
   

    
    
void stop_at_wall(){

if(sensor.distance_forwards()>20 || sensor.distance_forwards()<1){
    
    forward();
    
    }
  else{
    
    stop_motor();

    } 
    
  }



void left_motor_pulse_interrupt()
{
  left_motor.inc_pulse();

}

void right_motor_pulse_interrupt()
{
  right_motor.inc_pulse();

}




/*void even_pulse_forward(){



  if (left_motor.get_pulse_count()-right_motor.get_pulse_count()>1){
  // decrease left motor
  speedL=speedL+1;
  speedR=speedR-1;
  left_motor.forward(speedL);
  Serial.println(speedL);
  
  }
  if (right_motor.get_pulse_count()-left_motor.get_pulse_count()>1){
  // decrease right motor
  speedR=speedR+1;
  speedL=speedL-1;
  right_motor.forward(speedR);
  Serial.println(speedR);
    }
  }*/



void even_pulse_forward(){
  

  if (left_motor.get_pulse_count()-right_motor.get_pulse_count()>1){
  // decrease left motor
  left_motor.forward(speedL-5);
  right_motor.forward(speedR+5);
  }
  else if (right_motor.get_pulse_count()-left_motor.get_pulse_count()>1){
  // decrease right motor
  right_motor.forward(speedR-5);
  left_motor.forward(speedL+5);
    }
  }
