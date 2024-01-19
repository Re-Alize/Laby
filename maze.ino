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


NewPing sonarLeft(trigl, echol, 20); // NewPing setup of pins and maximum distance.
NewPing sonarRight(trigr, echor, 20);
NewPing sonarFront(trigf, echof, 20);

unsigned int pingSpeed = 30; // How frequently are we going to send out a ping (in milliseconds). 50ms would be 20 times a second.
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
 distancecheckl();
 distancecheckr();
}

void distancecheckf(){
   // Clears the trigPin
  digitalWrite(trigf, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigf, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigf, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echof, HIGH);
  // Calculating the distance
  distancef = duration * 0.034 / 2;
  Serial.print("Front Distance: ");
  Serial.println(distancef);
}

void distancecheckl(){
   // Clears the trigPin
  digitalWrite(trigl, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigl, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigl, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echol, HIGH);
  // Calculating the distance
  distancel = (duration / 29) / 2;
  Serial.print("Left Distance: ");
  Serial.println(distancel);
}

void distancecheckr(){
   // Clears the trigPin
  digitalWrite(trigr, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigr, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigr, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echor, HIGH);
  // Calculating the distance
  distancer = (duration / 29) / 2;
  Serial.print("Right Distance: ");
  Serial.println(distancer);
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