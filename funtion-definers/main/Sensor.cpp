#include <NewPing.h>
#include "Arduino.h"
#include "Sensor.h"

namespace {
  
}

Sensor::Sensor(){
  
}

float Sensor::distance_forwards()
{
  NewPing forward_sensor(forward_trigger, forward_echo, max_distance);
  delay(50);
  return forward_sensor.ping_cm();
}

float Sensor::distance_down()
{
  NewPing down_sensor(down_trigger, down_echo, max_drop);
  delay(50);
  return down_sensor.ping_cm();
}

float Sensor::left_light_sensor()
{
  const int left_light_sensor = 7;
  return analogRead(left_light_sensor);
}

float Sensor::center_light_sensor()
{
  const int center_light_sensor = 6;
  return analogRead(center_light_sensor);
}

float Sensor::right_light_sensor()
{
  const int right_light_sensor = 2;
  return analogRead(right_light_sensor);
}

