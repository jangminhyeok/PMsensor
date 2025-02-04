#include "PMsensor.h"

PMsensor::PMsensor() {
}

void PMsensor::init(int LEDpin, int sensorPin) {
  _LEDpin = LEDpin;
  _sensorPin = sensorPin;
  pinMode(_LEDpin, OUTPUT);
}

float PMsensor::read(float sensitivity) {
  int ret = PMsensorErrSuccess ;
  _sensitivity = sensitivity;
  digitalWrite(_LEDpin, LOW);
  delayMicroseconds(280);

  rawData = analogRead(_sensorPin);
  delayMicroseconds(40);

  digitalWrite(_LEDpin, HIGH); 	 
  delayMicroseconds(9680);

  val = (0.143 * (rawData * 0.0049)-0.03) * 1000;
  float filteredVal = (prevVal * (1 - _sensitivity)) + (val * _sensitivity);
  prevVal = filteredVal;
  float val = filteredVal;

  return val;

}

float PMsensor::read() {
  int ret = PMsensorErrSuccess ;
  digitalWrite(_LEDpin, LOW);
  delayMicroseconds(280);

  rawData = analogRead(_sensorPin);
  delayMicroseconds(40);

  digitalWrite(_LEDpin, HIGH);
  delayMicroseconds(9680);

  val = (0.143 * (rawData * 0.0049) - 0.03) * 1000;

  return val;
  
}

float PMsensor::read_filtered() {
  _sensitivity = 0.1;

  digitalWrite(_LEDpin, LOW);
  delayMicroseconds(280);
  dust = analogRead(_sensorPin);
  delayMicroseconds(40);
  digitalWrite(_LEDpin, HIGH);
  delayMicroseconds(9680);

  dust = (0.143 * (dust * 0.0049) - 0.03) * 1000;
  float filteredVal = (prevVal * (1 - _sensitivity)) + (dust * _sensitivity);
  prevVal = filteredVal;
  dust = filteredVal;

  if (dust < 100) {
    dust = dust / 4;
  }
  else if (dust > 100 && dust < 200) {
    dust = (dust / 4) * 1.15;
  }
  else if (dust > 200 && dust < 300) {
    dust = (dust / 4) * 1.15 * 1.3;
  }
  else if (dust > 300 && dust < 400) {
    dust = (dust / 4) * 1.15 * 1.3 * 1.45;
  }
  else if (dust > 400 && dust < 500) {
    dust = (dust / 4) * 1.15 * 1.3 * 1.45 * 1.6;
  }

 	return dust;
}