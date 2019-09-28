int pw[]={0,5,4,14,22};
int dr[]={0,6,2,16,18};
int di[]={0,7,3,15,19};
int an[]={0,45,135,225,315};
bool aux;
float kp, kd;
/*
  D--A
  -  -
  C--B
*/

void setup() {
  for(int i=1; i<=4; i++){
    pinMode(pw[i],OUTPUT);
    pinMode(dr[i],OUTPUT);
    pinMode(di[i],OUTPUT);
  }
}

void loop() {
  test();
}
void mov(float mag, int deg){
  for(int i=1; i<=4; i++){
      
  }
}
void align(float mag){
  mag>0? aux=0:aux=1; //!derecha o izquierda
  mag= abs(mag);
  for(int i='A'; i<='D'; i++)
    motor(i, mag*kp, aux);
}
void test(){
  for(int i='A'; i<='D'; i++){
    motor(i, 255, 1);
    delay(1000);
    motor(i, 255, 0);
    delay(1000);
    motor(i, 0, 0);
  }
}
void motor(int n, int sp, bool dir){
  n= n-'A'+1;
  analogWrite(pw[n], sp);
  digitalWrite(dr[n], dir);
  digitalWrite(di[n], !dir);
}
