#include <NewPing.h> //ping lib

#define maxdist 100

int dir;

#define STOP 0
#define FORWARD 1
#define BACKWARD 2
#define LEFT 3
#define RIGHT 4

float P = 0.7 ;
float D = 0.5 ;
float I = 0.4 ;
float oldErrorP ;
float totalError ;
int offset = 5 ;

bool frontw;
bool leftw;
bool rightw;
bool fturn;
bool rwf;
bool lwf;

int in1 = 5;
int in2 = 7;
int ena = 6;

int in3 = 8;
int in4 = 10;
int enb = 9;

int trigf = 12;
int echof = 13;

int trigl = 11;
int echol = 4;

int trigr = 2;
int echor = 3;

int distancef;
int distancel;
int distancer;

int baseSpeed = 70 ;
int RMS ;
int LMS ;

long duration; 

float lastpingf, lastpingr, lastpingl, lsense, rsense, fsense;

int wallthreshold = 10;
int frontthreshold = 7;

NewPing sonarLeft(trigl, echol, maxdist); // NewPing setup of pins and maximum distance.
NewPing sonarRight(trigr, echor, maxdist);
NewPing sonarFront(trigf, echof, maxdist);

unsigned int pingSpeed = 30;
unsigned long pingTimer; 

void setup() {
  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(trigf, OUTPUT);
  pinMode(echof, INPUT);
  pinMode(trigl, OUTPUT);
  pinMode(echol, INPUT);
  pinMode(trigr, OUTPUT);
  pinMode(echor, INPUT);
  Serial.begin(9600);
}

void loop() {
  checksurround();
  wallcheck();

  if ( fturn == false ) {

    pid_start();

  }
  else if (lwf == true ) {

    PID(true) ;

  }
  else if (rwf == true ) {
    PID(false) ;
  }


  if (leftw == true && rightw == false && frontw == true ) {

    // turnright();
    PID(false) ;

    if ( fturn == false ) {
      fturn = true ;
      rwf = true ;
    }
  }
   if (leftw == false && rightw == true && frontw == true ) {

    PID(true) ;

    if ( fturn == false ) {

      fturn = true ;
      lwf = true ;
       
    }
  }
   if ( lsense == 0 || lsense > 100 && rsense == 0 || rsense > 100 && fsense == 0 || fsense > 100 ) {

    setDirection(STOP);
  }
}

void checksurround (){
  distancel = sonarLeft.ping_cm();
  distancer = sonarRight.ping_cm();
  distancef = sonarFront.ping_cm();

  lsense = (distancel + lastpingl) / 2;
  rsense = (distancer + lastpingr) / 2;
  fsense = (distancef + lastpingf) / 2;

  lastpingl = lsense;
  lastpingr = rsense;
  lastpingf = fsense;
}

void wallcheck(){
  if (lsense < wallthreshold) {
    leftw = true;
  } else {
    leftw = false;
  }
  
  if (rsense < wallthreshold) {
    rightw = true;
  } else {
    rightw = false;
  }

  if (fsense < wallthreshold) {
    frontw = true;
  } else {
    frontw = false;
  }
}


void setDirection(int dir) {

  if ( dir == FORWARD ) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else if ( dir == LEFT ) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  else if ( dir == RIGHT ) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else if ( dir == STOP ) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
  else if ( dir == BACKWARD ) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
}

//--------------------------------- control ---------------------------------//

void pid_start() {

  float errorP = lsense - rsense; // proportional
  float errorD = errorP - oldErrorP; //integral
  float errorI = (2.0 / 3.0) * errorI + errorP ; //derivative

  totalError = P * errorP + D * errorD + I * errorI ;
  
  oldErrorP = errorP ;

  RMS = baseSpeed + totalError ;
  LMS = baseSpeed - totalError ;

  if (RMS < 0) {

    RMS = map(RMS , 0 , -255, 0, 255);

    analogWrite(ena , RMS);
    analogWrite(enb , LMS);

    setDirection(RIGHT);

  }
  else if (LMS < 0) {
    LMS = map(LMS , 0 , -255, 0, 255);


    analogWrite(ena , RMS);
    analogWrite(enb , LMS);

    setDirection(LEFT);
  }
  else {

    analogWrite(ena , RMS);
    analogWrite(enb , LMS);

    setDirection(FORWARD);
  }

}


//----------------------------- wall follow  control -------------------------------//

void PID( boolean left ) {

  if (left == true ) {

    float errorP = lsense - rsense - offset ;
    float errorD = errorP - oldErrorP;
    float errorI = (2.0 / 3) * errorI + errorP ;


    totalError = P * errorP + D * errorD + I * errorI ;

    oldErrorP = errorP ;


    RMS = baseSpeed + totalError ;
    LMS = baseSpeed - totalError ;

    //  if(RMS < -255) RMS = -255; if(RMS > 255)RMS = 255 ;
    //  if(LMS < -255) LMS = -255;  if(LMS > 255)LMS = 255 ;


    if (RMS < 0) {

      RMS = map(RMS , 0 , -255, 0, 255);

      analogWrite(ena , RMS);
      analogWrite(enb , LMS);

      setDirection(RIGHT);

    }
    else if (LMS < 0) {
      LMS = map(LMS , 0 , -255, 0, 255);


      analogWrite(ena , RMS);
      analogWrite(enb , LMS);

      setDirection(LEFT);
    }
    else {

      analogWrite(ena , RMS);
      analogWrite(enb , LMS);

      setDirection(FORWARD);
    }

  }
  else {

    float errorP = lsense - rsense + offset ;
    float errorD = errorP - oldErrorP;
    float errorI = (2.0 / 3) * errorI + errorP ;

    totalError = P * errorP + D * errorD + I * errorI ;

    oldErrorP = errorP ;


    RMS = baseSpeed + totalError ;
    LMS = baseSpeed - totalError ;

    //  if(RMS < -255) RMS = -255; if(RMS > 255)RMS = 255 ;
    //  if(LMS < -255) LMS = -255;  if(LMS > 255)LMS = 255 ;


    if (RMS < 0) {

      RMS = map(RMS , 0 , -255, 0, 255);

      analogWrite(ena , RMS);
      analogWrite(enb , LMS);

      setDirection(RIGHT);

    }
    else if (LMS < 0) {
      LMS = map(LMS , 0 , -255, 0, 255);


      analogWrite(ena , RMS);
      analogWrite(enb , LMS);

      setDirection(LEFT);
    }
    else {

      analogWrite(ena , RMS);
      analogWrite(enb , LMS);

      setDirection(FORWARD);
    }

  }

}
