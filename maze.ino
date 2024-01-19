#include <NewPing.h> //ping lib

#define maxdist 100

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
}

void checksurround (){
  distancel = sonarLeft.ping_cm();
  distancer = sonarLeft.ping_cm();
  distancef = sonarLeft.ping_cm();

  lsense = (distancel + lastpingl) / 2;
  rsense = (distancer + lastpingr) / 2;
  fsense = (distancef + lastpingf) / 2;

  lastpingl = lsense;
  lastpingr = rsense;
  lastpingf = fsense;
}

void wallcheck(){
  if (lsense < wallthreshold) {

  }
}

void fw(){
  digitalWrite(ena, 100);  
  digitalWrite(enb, 100);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void bw(){
  digitalWrite(ena, 100);  
  digitalWrite(enb, 100);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void right(){
  digitalWrite(ena, 100);  
  digitalWrite(enb, 0);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void left(){
  digitalWrite(ena, 0);  
  digitalWrite(enb, 100);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
