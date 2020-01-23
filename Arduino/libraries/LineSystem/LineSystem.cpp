#include "Arduino.h"
#include "LineSystem.h"
#include "EEPROM.h"

//CONSTRUCTOR
LineSystem::LineSystem(int _nSensor, int _pin[]){
    nSensor= _nSensor;
    angleDiference= 360/nSensor;
    for(int i=1; i<=nSensor; i++){
        pin[i]= _pin[i];
        lineOffset[i]= EEPROM.read(i)*4;
    }
}

//CALIBRATION
void LineSystem::calibrate(){
    if(digitalRead(calibratePin)&&!flag) flag= true;
    if(!digitalRead(calibratePin)&&flag){
        ++calibrationState%= 3;
        flag= false;
    }
    if(calibrationState==1) getLineOffset();
    if(calibrationState==2) saveLineOffset();
}
void LineSystem::getLineOffset(){
    for(int i=1; i<=nSensor; i++){
        lineOffset[i]= max( (analogRead(pin[i])+20), lineOffset[i]);
    }
}
void LineSystem::saveLineOffset(){
    for(int i=1; i<=nSensor; i++){
        EEPROM.write(i, lineOffset[i]/4);
    }
    calibrationState= 0;
}