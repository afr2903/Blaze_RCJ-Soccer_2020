#ifndef LineSystem_h
#define LineSystem_h

#include "Arduino.h"
#include "EEPROM.h"
#define MAX 60

class LineSystem{
    public:
        LineSystem(int _nSensor, int _pin[]);
        void calibrate();
        void clearLineOffset();
        void getLineOffset();
        void saveLineOffset();
        int get(int n);
        bool lineDetected();
        int getRecoveryAngle();
    private:
        int nSensor;
        int pin[MAX];
        int angleDiference;
        int lineOffset[MAX];

        int calibratePin= 20;
        bool flag= false;
        int calibrationState= 0;

        int sensorsDetected= 0;
        int recoveryAngle= 0;
};

#endif
