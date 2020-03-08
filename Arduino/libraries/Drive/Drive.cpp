#include "Arduino.h"
#include "Drive.h"

//CONSTRUCTORS
Drive::Drive(int _nMot, motor **_mot){
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
void motor::moveMotor(double speed){
    bool dir= speed>0;
    if(ramp_active) speed = ramp(speed);
    speed= min(1, max(0,abs(speed))) * 255;
    if(pwmPin) analogWrite(pwmPin, speed);
    digitalWrite(rightPin, dir);
    digitalWrite(leftPin, !dir);
}
double motor::ramp(double speed){
    target_speed = speed;
    if( abs(target_speed) > abs(current_speed) ){
        if(target_speed>0) current_speed += ramp_rate;
        else current_speed -= ramp_rate;
    }
    return current_speed;
}
double motor::omniSpeed(int target, double speed){
    return sp= sin((target-angle)*PI/180)*speed;
}

//PID CONTROL
void Drive::setPID(double _kp, double _ki, double _kd){
    kp=_kp/255, ki=_ki/255, kd=_kd/255;
    integral= lastError= 0;
}
double Drive::getPID(double error){
    derivative= error-lastError;
    integral+= error;
    lastError= error;
    return (error*kp)+(integral*ki)+(derivative*kd);
}

//MOVEMENT FUNCTIONS
void Drive::test(double speed){
    for(int i=0; i<nMot; i++){
        (*mot[i]).moveMotor(speed);
        delay(500);
        (*mot[i]).moveMotor(-speed);
        delay(500);
        (*mot[i]).moveMotor(0);
    }
}
void Drive::align(double error){
    double pid= getPID(error);
    for(int i=0; i<nMot; i++)
        (*mot[i]).moveMotor(-pid);
}
void Drive::move(int target, double speed, double error){
    speed /= 255;
    double pid= getPID(error);
    double maxSp=0;
    for(int i=0; i<nMot; i++)
        maxSp= max( abs((*mot[i]).omniSpeed(target,speed)), maxSp);

    double scale= speed/maxSp;
    for(int i=0; i<nMot; i++)
        (*mot[i]).moveMotor( (*mot[i]).sp*scale - pid );
}
