#include "Arduino.h"
#include "Omni.h"

Omni::Omni(int _pw[], int _dr[], int _di[], float _kp){
    for(int i=1; i<=4; i++){
        pw[i]=_pw[i];
        dr[i]=_dr[i];
        di[i]=_di[i];
        pinMode(pw[i],OUTPUT);
        pinMode(dr[i],OUTPUT);
        pinMode(di[i],OUTPUT);
    }
    kp= _kp;
}

void Omni::motor(int n, int sp, bool dir){
    n= n-'A'+1;
    analogWrite(pw[n], sp);
    digitalWrite(dr[n], dir);
    digitalWrite(di[n], !dir);
}
void Omni::test(){
    for(int i='A'; i<='D'; i++){
        motor(i, 255, 1);
        delay(1000);
        motor(i, 255, 0);
        delay(1000);
        motor(i, 0, 0);
    }
}
void Omni::align(float error){
    error>0? aux=0:aux=1;
    error= abs(error);
    for(int i='A'; i<='D'; i++)
        motor(i, error*kp, aux);
}
void Omni::move(int deg, int sp, float error){
    bool dir;
    for(int i='A'; i<='D'; i++){
        float mot_sp= sin((deg-ang[i-'A'+1])*PI/180)*sp;
        dir= mot_sp>0? 1:0;
        mot_sp= abs(mot_sp);
        mot_sp+= dir? error*kp:-error*kp;

        motor(i, mot_sp, dir);
    }
}
