#include <stdio.h>      /* printf */
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */
#include <iostream>

#include <Pid.h>

using namespace std;
float readSensor();
void setActuator(float value);
double getDeltaTime();

float comandValue= 10; ///For example we want 10V of bus bar voltage
float controlValue = 0; //initial voltage
float acceptValue = 0.98f; //98% final value
float sensorValue = 0;

int main() {

  Pid myPid(1,0.5,0.01,0); //Kp=1 Kd=0.5 Ki=0.01

  time_t time0; //Simulator timers
  time0 = time(NULL);

  //main control loop
  //while final value is under 98%
  while(sensorValue< acceptValue*comandValue)
  {
    float sensorValue = readSensor(); //Get the actual value from the plant
    
    controlValue = myPid.calc(getDeltaTime(), comandValue-sensorValue); //Check the difference between reference value and actual value

    setActuator(controlValue); //Apply the new control value

    cout <<"reference: " << comandValue << "| sensorValue: "<<sensorValue <<"| controlValue: "<<controlValue <<endl;
  }

  return 0;
}
/**
* @brief Get sensor value from API of your plant
* @return
*/
float readSensor()
{
  float value = 0;

  //value = getFromAPI...

  //In this example we simulate that sensor value is controlValue * 1.8
  value = controlValue * 1.8;

  return value;
}
/**
* @brief Set control value from API of your plant
* @return
*/
void setActuator(float value)
{
  //setFromAPI(value)...
}
/**
* @brief Get clock reference from API of your plant
* @return Delta Time between cicyes
*/
double getDeltaTime()
{
  double time=0.01;

  //time = getClockTime()

  return time;
}