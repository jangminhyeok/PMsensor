#include <Arduino.h>

#define PMsensorErrSuccess 100
#define PMsensorErrDataLow 101
#define PMsensorErrDataZero 102

class PMsensor {
  public:
    PMsensor();
	void init(int LEDpin, int sensorPin);
    float read(float sensitivity);
    float read();
    float read_filtered();
    float rawData;
    float dust;
    float val;
    float prevVal;

  private:
    int _LEDpin;
    int _sensorPin;
    float _sensitivity;

};
