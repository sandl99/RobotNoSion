#define inA1 6
#define inA2 7
#define inB1 8
#define inB2 9
#define enA 10
#define enB 5

// variables for PID algorithm
const int Kp = 20, Ki = 0, Kd = 0;
float errorP = 0;
float errorN = 0;
int P, I, D;
int PIDvalue;

// config
const int offset = 5;
const int initMotorLeft = -50 - offset - 15;
const int initMotorRight = 50 + offset;
const boolean using_backward = false;
const float scale = 2.0;

//function define
void startup();
boolean IFSensor(byte pinNum);
void readStatus();
void calculatePID();
void motor_drive_forward(int left, int right);
void motor_drive_backward(int left, int right);
void getError();

// sensor error
float err[32];
unsigned int stat;

void calculatePID() {
  P = errorN;
  I += errorN;
  D = errorN - errorP;
  PIDvalue = (Kp*P) + (Ki*I) + (Kd*D);
  PIDvalue /= scale;
  errorP = errorN;
}

void motor_drive_forward(int left, int right) {
  left = abs(left);
  if (using_backward) {
    digitalWrite(inA1, HIGH);
    digitalWrite(inA2, LOW);
    digitalWrite(inB1, HIGH);
    digitalWrite(inB2, LOW);
  }
  analogWrite(enA, left);
  analogWrite(enB, right);
}

void motor_drive_backward(int left, int right) {
  left = abs(left);
  digitalWrite(inA2, HIGH);
  digitalWrite(inA1, LOW);
  digitalWrite(inB2, HIGH);
  digitalWrite(inB1, LOW);
  analogWrite(enA, left);
  analogWrite(enB, right);
}

void setup() {
  Serial.begin(9600);
  pinMode(inA1, OUTPUT);//Set chân in1 của dc A là output
  pinMode(inA2, OUTPUT);//Set chân in2 của dc A là output
  pinMode(inB1, OUTPUT);//Set chân in1 của dc B là output
  pinMode(inB2, OUTPUT);//Set chân in2 của dc B là output
  
  pinMode(A4, INPUT);//Set chân cảm biến 1 là input
  pinMode(A3, INPUT);//Set chân cảm biến 2 là input
  pinMode(A2, INPUT);//Set chân cảm biến 3 là input
  pinMode(A1, INPUT);//Set chân cảm biến 4 là input
  pinMode(A0, INPUT);//Set chân cảm biến 5 là input

  digitalWrite(inA1, HIGH);
  digitalWrite(inA2, LOW);
  digitalWrite(inB1, HIGH);
  digitalWrite(inB2, LOW);

  startup();
}

void startup() {
//  Tien(100,85);
  delay(20);

  for (int i = 0; i < 32; i++) {
    err[i] = -5;
  }
  err[B00001] = 4;
  err[B00011] = 3;
  err[B00111] = 2.5;
  err[B00010] = 2;
  err[B00110] = 1;
  err[B00100] = 0;
  err[B01100] = -1;
  err[B01000] = -2;
  err[B11100] = -2.5;
  err[B11000] = -3;
  err[B10000] = -4;
}

boolean IFSensor(byte pinNum) {
//  black = 1, white = 0
  return digitalRead(pinNum);
}

void readStatus() {
  unsigned int tmp = 0;
  for (byte i = A4; i >= A0; i-=1) {
    tmp += IFSensor(i);
    if (i > A0) tmp <<= 1;
  }
  stat = tmp;
//  Serial.println(stat, BIN);
}

void getError() {
  readStatus();
  if (err[stat] < -4) {
    errorN = errorP;
  } else {
    errorN = err[stat];
  }
}

void loop() {
  delay(500);
  Serial.println(errorN);
  getError();
  calculatePID();
  int rspeed = initMotorRight + int(PIDvalue);
  int lspeed = initMotorLeft + int(PIDvalue);
  constrain(rspeed, 0, 255);
  constrain(lspeed, -255, 0);
  motor_drive_forward(lspeed, rspeed);
}
