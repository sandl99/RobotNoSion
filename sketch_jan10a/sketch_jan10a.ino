#define line_1      A0
// trái
#define line_2      A1
#define line_3      A2 // line chính giữa
#define line_4      A3 // phải
#define line_5      A4

#define inA1 6 //Định nghĩa chân in1 của động cơ A
#define inA2 7 //Định nghĩa chân in2 của động cơ A
#define inB1 8 //Định nghĩa chân in1 của động cơ B
#define inB2 9 //Định nghĩa chân in2 của động cơ B

uint8_t speed_robot=150;  // set_speed_robot
int sensor=0;
int offset=80;

uint8_t line_val[5] = {0};

void setup()
{
  pinMode(inA1, OUTPUT);//Set chân in1 của dc A là output
  pinMode(inA2, OUTPUT);//Set chân in2 của dc A là output
  pinMode(inB1, OUTPUT);//Set chân in1 của dc B là output
  pinMode(inB2, OUTPUT);//Set chân in2 của dc B là output
  pinMode(5,1);
  pinMode(10,1);
  pinMode(line_1,INPUT);
  pinMode(line_2,INPUT);
  pinMode(line_3,INPUT);
  pinMode(line_4,INPUT);
  pinMode(line_5,INPUT);
  Serial.begin(9600);
}

void robotMover (byte inR1, byte inR2, byte inL1, byte inL2, byte action)
{
  /*
  inR1 inR2 là 2 chân tín hiệu động cơ bên phải
  inL1 inL2 là 2 chân tín hiệu động cơ bên trái
  action= 0 đứng yên
  action =1 đi thẳng
  action =2 lùi lại
  action =3 quay trái
  action =4 quay phải
  action =5 rẽ trái
  action =6 rẽ phải
  action =7 rẽ lùi trái
  action =8 rẽ lùi phải

  */
  analogWrite(5,speed_robot);
  analogWrite(10,speed_robot-20);
  switch (action)
  {
    case 0:// không di chuyển
      motorControlNoSpeed(inR1, inR2, 0);
      motorControlNoSpeed(inL1, inL2, 0);
      break;
    case 1://đi thẳng
      motorControlNoSpeed(inR1, inR2, 1);
      motorControlNoSpeed(inL1, inL2, 1);
      break;
    case 2:// lùi lại
      motorControlNoSpeed(inR1, inR2, 2);
      motorControlNoSpeed(inL1, inL2, 2);
      break;
    case 3:// quay trái
      motorControlNoSpeed(inR1, inR2, 1);
      motorControlNoSpeed(inL1, inL2, 2);
      break;
    case 4:// quay phải
      motorControlNoSpeed(inR1, inR2, 2);
      motorControlNoSpeed(inL1, inL2, 1);
      break;
    case 5:// rẽ trái
      motorControlNoSpeed(inR1, inR2, 1);
      motorControlNoSpeed(inL1, inL2, 0);
      break;
    case 6:// rẽ phải
      motorControlNoSpeed(inR1, inR2, 0);
      motorControlNoSpeed(inL1, inL2, 1);
      break;
    case 7:// rẽ lùi trái
      motorControlNoSpeed(inR1, inR2, 2);
      motorControlNoSpeed(inL1, inL2, 0);
      break;
    case 8:// rẽ lùi phải
      motorControlNoSpeed(inR1, inR2, 0);
      motorControlNoSpeed(inL1, inL2, 2);
      break;
    default:
      action = 0;
      
  }
}


void motorControlNoSpeed (byte in1,byte in2, byte direct)
{
// in1 and in2 are 2 signal pins to control the motor
// en is the enable pin
// the defauspeed is the highest
// direct includes:
//    0:Stop
//    1:Move on forward
//    2:Move on backward
switch (direct) 
  {
    case 0:// Dừng không quay
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      break;
    case 1:// Quay chiều thứ 1
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      break;    
    case 2:// Quay chiều thứ 2
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      break;
    //default: 
  }
}


void scan_sensor()
{
  if(digitalRead(line_1)==0) sensor=-2;
  if(digitalRead(line_2)==0) sensor=-1;
  if(digitalRead(line_3)==0) sensor=0;
  if(digitalRead(line_4)==0) sensor=1;
  if(digitalRead(line_5)==0) sensor=2;
}

void read_sensor(){
  line_val[0] = !digitalRead(line_1);
  line_val[1] = !digitalRead(line_2);
  line_val[2] = !digitalRead(line_3);
  line_val[3] = !digitalRead(line_4);
  line_val[4] = !digitalRead(line_5);  
}

void display_val(){
  int i;
  for (i = 0; i < 5; i++){
    Serial.print(line_val[i]);
    Serial.print(" ");  
  }
  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
    read_sensor();
    if ((line_val[0] == 1) && (line_val[1] == 1) && (line_val[2] == 0) && (line_val[3] == 1) && (line_val[4] == 1)){ // xe đang bám đúng line
      speed_robot = 150 + offset;
      robotMover(inA1, inA2, inB1, inB2, 1); // đi thẳng
    }
    else if ((line_val[0] == 1) && (line_val[1] == 0) && (line_val[3] == 1) && (line_val[4] == 1)){ // xe bị lệch phải một ít
      speed_robot = 100 + offset;
      robotMover(inA1, inA2, inB1, inB2, 5); // rẽ trái
    }
    else if ((line_val[0] == 0) && (line_val[3] == 1) && (line_val[4] == 1)){ // xe bị lệch phải nhiều
      speed_robot = 150 + offset;
      robotMover(inA1, inA2, inB1, inB2, 5); // rẽ trái
    }
    else if ((line_val[0] == 1) && (line_val[1] == 1) && (line_val[3] == 0) && (line_val[4] == 1)){ // xe bị lệch trái một ít
      speed_robot = 100 + offset;
      robotMover(inA1, inA2, inB1, inB2, 6); // rẽ phải
    }
    else if ((line_val[0] == 1) && (line_val[1] == 1) && (line_val[4] == 0)){ // xe bị lệch trái nhiều
      speed_robot = 150 + offset;
      robotMover(inA1, inA2, inB1, inB2, 6); // rẽ phải
    }
}
