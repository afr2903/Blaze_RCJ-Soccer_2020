#ifndef Omni_h
#define Omni_h

#include "Arduino.h"
#define MAX 10
//4--1
//|  |
//3--2

class Omni
{
  public:
    Omni(int _n_mot, int _pw[], int _dr[], int _di[], float _kp, float _kd); //Constructor
    void motor(int n, float sp); //Movimiento de un motor individual
    void test(); //Probar motores uno por uno
    void align(float error); //Alinearse sobre su propio eje
    void move(int deg, int sp, float error); //Movimientos omnidireccionales
  private:
    int n_mot;
    int pw[MAX], dr[MAX], di[MAX]; //Pines de los motores
    int mot_ang[MAX]; //Angulo en que se encuentran posicionados los motores
    float kp, kd, last_error, pid; //Variables para el control
};

#endif
