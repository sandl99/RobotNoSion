#define inA1 6
#define inA2 7
#define inB1 8
#define inB2 9
#define enA 10
#define enB 5

// variables for PID algorithm
const float Kp = 0.035, Ki = 0, Kd = 0;
float errorP = 2000;
float errorN = 0;
int P, I, D;
int PIDvalue;

// config
const int offset = 15;
const int initMotorLeft = -60 - offset - 12;
const int initMotorRight = 60 + offset;
const boolean using_backward = false;
//const float scale = 1.0;

//function define
void startup();
boolean IFSensor(byte pinNum);
void readStatus();
void calculatePID();
void motor_drive_forward(int left, int right);
void motor_drive_backward(int left, int right);
void getError();

// sensor error
unsigned int stat;

// line black or white
boolean check = true;
unsigned int orcheckwhite = B10001;
unsigned int orcheckblack = B00000;

void calculatePID() {
  P = errorN - 2000;
  I += errorN;
  D = errorN - errorP;
  PIDvalue = (Kp*P) + (Kd*D);
//  PIDvalue /= scale;
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
  analogWrite(enA, right);
  analogWrite(enB, left);
}

void motor_drive_backward(int left, int right) {
  left = abs(left);
  digitalWrite(inA2, HIGH);
  digitalWrite(inA1, LOW);
  digitalWrite(inB2, HIGH);
  digitalWrite(inB1, LOW);
  analogWrite(enA, right);
  analogWrite(enB, left);
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

  unsigned int x = B11111;
  
  unsigned int orres_white = stat & orcheckwhite;
  unsigned int orres_black = (~stat) & orcheckwhite;
  if (orcheckwhite == orres_white) check = false;
  if (orcheckwhite == orres_black) check = true;
  if (!check) {
    stat = stat ^ (~x);
    stat = ~stat;
//    Serial.println(stat, BIN);
  }
}

void getError() {
  readStatus();
  int num = 0;
  int count = 4;
  unsigned int b = 1;
  errorN = 0;
  while (count >= 0) {
    int res = b & stat;
    stat >>= 1;
    if (res) {
      errorN += count * 1000;
      num += 1;
    }
    count -= 1;
  }

  if (num == 0) errorN = errorP;
  else errorN /= num;
}

void loop() {
//  Serial.println(errorN);
  getError();
  calculatePID();
  int rspeed, lspeed;
  int int_PID = int(PIDvalue);
//  int_PID = 0;
  if (int_PID > 0) {
    rspeed = initMotorRight - int_PID;
    lspeed = initMotorLeft - (-10);
  } else if (PIDvalue < 0) {
    rspeed = initMotorRight - 10;
    lspeed = initMotorLeft - int_PID;
  } else {
    rspeed = initMotorRight - int_PID;
    lspeed = initMotorLeft - int_PID;
  }
  rspeed = constrain(rspeed, 0, initMotorRight * 2);
  lspeed = constrain(lspeed, initMotorLeft * 2, 0);
  
  motor_drive_forward(lspeed, rspeed);
}
