#ifndef LineSystem_h
#define LineSystem_h

#include "Arduino.h"
#include "EEPROM.h"
#define MAX 60

class LineSystem{
    public:
        LineSystem(int _nSensor, int _pin[]);
        void calibrate();
        void getLineOffset();
        void saveLineOffset();
    private:
        int nSensor;
        int pin[MAX];
        int angleDiference;
        int lineOffset[MAX];

        int calibratePin= 20;
        bool flag= false;
        int calibrationState= 0;
};

#endif
