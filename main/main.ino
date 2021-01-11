#define inA1 6
#define inA2 7
#define inB1 8
#define inB2 9

unsigned int statusP;
unsigned int statusN;

int Kp, Ki, Kd;
int errorP;
int errorN;
int P, I, D;

void startup();
boolean IFSensor(byte pinNum);
void readStatus();
void calculate();

void calculate() {
  
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
  Tien(100,85);
  delay(20);
}

boolean IFSensor(byte pinNum) {
//  black = 1, white = 0
  return digitalRead(pinNum);
}

void readStatus() {
  unsigned int tmp = 0;
  for (int i = A4; i >= A0; i--) {
    tmp += IFSensor(i);
    tmp <<= 1;
  }
  statusN = tmp;
}

void getError() {
  
}
