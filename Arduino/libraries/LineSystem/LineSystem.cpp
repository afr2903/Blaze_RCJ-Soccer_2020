#include "Arduino.h"
#include "LineSystem.h"
#include "EEPROM.h"

//CONSTRUCTOR
LineSystem::LineSystem(int _nSensor, int _pin[]){
    nSensor= _nSensor;
    angleDiference= 360/nSensor;
    for(int i=0; i<nSensor; i++){
        pin[i]= _pin[i];
        lineOffset[i]= EEPROM.read(i)*4;
    }
}
int LineSystem::get(int n){
    return analogRead(pin[n]);
}

//CALIBRATION
void LineSystem::calibrate(){
    if(digitalRead(calibratePin)&&!flag) flag= true;
    if(!digitalRead(calibratePin)&&flag){
        ++calibrationState%= 3;
        flag= false;
        clearLineOffset();
    }
    if(calibrationState==1) getLineOffset();
    if(calibrationState==2) saveLineOffset();
}
void LineSystem::clearLineOffset(){
    for(int i=0; i<nSensor; i++) lineOffset[i]= 0;
}
void LineSystem::getLineOffset(){
    for(int i=0; i<nSensor; i++){
        lineOffset[i]= max( (get(i)+60), lineOffset[i]);
    }
}
void LineSystem::saveLineOffset(){
    for(int i=0; i<nSensor; i++){
        EEPROM.write(i, (lineOffset[i]/4));
    }
    calibrationState= 0;
}

//LINE
bool LineSystem::lineDetected(){
    if(calibrationState!=0) return false;
    sensorsDetected= recoveryAngle= 0;

    for(int i=0; i<nSensor; i++){
        if( get(i)>lineOffset[i] ){
            sensorsDetected++;
            recoveryAngle+= i*angleDiference;
        }
    }
    if(sensorsDetected) return true;
    return false;
}
int LineSystem::getRecoveryAngle(){
    return ( recoveryAngle/sensorsDetected +180 ) % 360;
}