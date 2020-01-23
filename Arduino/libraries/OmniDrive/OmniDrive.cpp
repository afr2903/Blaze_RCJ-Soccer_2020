#include "Arduino.h"
#include "OmniDrive.h"

//CONSTRUCTORS
OmniDrive::OmniDrive(int _nMot, motor **_mot){
    nMot= _nMot;
    mot= _mot;
    for(int i=0; i<nMot; i++)
        (*mot[i]).angle= (360/nMot)*(i+.5);
}
motor::motor(int rP, int lP, int pP){
    if(pP) pinMode(pwmPin=pP, OUTPUT);
    pinMode(rightPin=rP, OUTPUT);
    pinMode(leftPin=lP, OUTPUT);
}

//MOTOR CONTROL
void motor::moveMotor(int speed){
    bool dir= speed>0;
    speed= min(255, max(0,abs(speed)));
    if(pwmPin) analogWrite(pwmPin, speed);
    digitalWrite(rightPin, dir);
    digitalWrite(leftPin, !dir);
}
double motor::omniSpeed(int target, int speed){
    return sp= sin((target-angle)*PI/180)*speed;
}

//PID CONTROL
void OmniDrive::setPID(double _kp, double _ki, double _kd){
    kp=_kp, ki=_ki, kd=_kd;
    integral= lastError= 0;
}
double OmniDrive::getPID(double error){
    derivative= error-lastError;
    integral+= error;
    lastError= error;
    return (error*kp)+(integral*ki)+(derivative*kd);
}

//MOVEMENT FUNCTIONS
void OmniDrive::test(int speed){
    for(int i=0; i<nMot; i++){
        (*mot[i]).moveMotor(speed);
        delay(500);
        (*mot[i]).moveMotor(-speed);
        delay(500);
        (*mot[i]).moveMotor(0);
    }
}
void OmniDrive::align(double error){
    double pid= getPID(error);
    for(int i=0; i<nMot; i++)
        (*mot[i]).moveMotor(-pid);
}
void OmniDrive::move(int target, int speed, double error){
    double pid= getPID(error);
    double maxSp=0;
    for(int i=0; i<nMot; i++)
        maxSp= max( abs((*mot[i]).omniSpeed(target,speed)), maxSp);

    double scale= speed/maxSp;
    for(int i=0; i<nMot; i++)
        (*mot[i]).moveMotor( (*mot[i]).sp*scale - pid );
}
