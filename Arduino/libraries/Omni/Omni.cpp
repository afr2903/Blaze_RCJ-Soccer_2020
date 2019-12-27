#include "Arduino.h"
#include "Omni.h"
//4--1
//|  |
//3--2

Omni::Omni(int _n_mot, int _pw[], int _dr[], int _di[], float _kp, float _kd){ //Constructor
    n_mot= _n_mot;
    for(int i=1; i<=n_mot; i++){
        pinMode(pw[i]=_pw[i] ,OUTPUT);
        pinMode(dr[i]=_dr[i] ,OUTPUT);
        pinMode(di[i]=_di[i] ,OUTPUT);
        mot_ang[i]= (360/n_mot)*(i-.5);
    }
    kp= _kp; //Constantes del control
    kd= _kd;
}

void Omni::motor(int n, float sp){ //Movimiento de un motor individual. n= numero del motor / sp= velocidad (puede ser negativa)
    bool dir= sp>0? 1:0; //Direccion del motor (1 es derecha y 0 es izquierda)
    sp= min(255, max(0,abs(sp))); //Normalizar velocidad entre 0 y 255
    analogWrite(pw[n], sp);
    digitalWrite(dr[n], dir);   //Mover motor
    digitalWrite(di[n], !dir);
}
void Omni::test(){
    for(int i=1; i<=n_mot; i++){
        motor(i, 255); //Derecha
        delay(500);
        motor(i, -255); //Izquierda
        delay(500);
        motor(i, 0); //Apagar
    }
}
void Omni::align(float error){ //Alinearse sobre su propio eje. error= valor del sensor de orientación
    pid= (error*kp)+(error-last_error)*kd; //Control proporcional y derivativo
    last_error= error;
    for(int i=1; i<=n_mot; i++) //Mover cada uno de los motores
        motor(i, -pid);
}
void Omni::move(int deg, int sp, float error){ //Movimientos omnidireccionales. deg= angulo de direccion del robot(-360 a 360) / sp= velocidad de los motores / error= valor del sensor de orientación
    pid= (error*kp)+(error-last_error)*kd; //Control proporcional y derivativo
    last_error= error;
    float mot_sp[n_mot+1], max_sp=0;
    for(int i=1; i<=n_mot; i++)
        max_sp= max(abs(mot_sp[i]= sin((deg-mot_ang[i])*PI/180)),max_sp); //Maximizar velocidad a 1

    float scale= 1/max_sp;
    for(int i=1; i<=n_mot; i++){
        mot_sp[i]= mot_sp[i]*scale*sp - pid; //Obtener velocidad individual del motor para moverse en la direccion deseada con control
        motor(i, mot_sp[i]);
    }
}
