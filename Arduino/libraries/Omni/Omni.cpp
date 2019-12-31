#include "Arduino.h"
#include "Omni.h"

//CONSTRUCTORES
Omni::Omni(int _nMot, motor **_mot){
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
    bool dir= speed>0? 1:0;
    sp= min(255, max(0,abs(speed)));
    if(pwmPin) analogWrite(pwmPin, speed);
    digitalWrite(rightPin, dir);
    digitalWrite(leftPin, !dir);
}
double motor::omniSpeed(int target, int speed){
    return sp= sin((target-angle)*PI/180)*speed;
}

//PID CONTROL
void Omni::setPID(double _kp, double _ki, double _kd){
    kp=_kp, ki=_ki, kd=_kd;
    integral= lastError= 0;
}
double Omni::getPID(double error){
    derivative= error-lastError;
    integral+= error;
    lastError= error;
    return (error*kp)+(integral*ki)+(derivative*kd);
}

//MOVEMENT FUNCTIONS
void Omni::test(int speed){
    for(int i=0; i<nMot; i++){
        (*mot[i]).moveMotor(speed);
        delay(500);
        (*mot[i]).moveMotor(-speed);
        delay(500);
        (*mot[i]).moveMotor(0);
    }
}
void Omni::align(double error){
    double pid= getPID(error);
    for(int i=0; i<nMot; i++)
        (*mot[i]).moveMotor(-pid);
}
void Omni::move(int target, int speed, double error){
    double pid= getPID(error);
    double maxSp=0;
    for(int i=0; i<nMot; i++)
        maxSp= max( abs((*mot[i]).omniSpeed(target,speed)), maxSp);

    double scale= speed/maxSp;
    for(int i=0; i<nMot; i++)
        (*mot[i]).moveMotor( (*mot[i]).sp*scale - pid );
}
