
byte offset = 10;

byte SpMaxL=84 + offset;
byte SpMaxR=70 + offset;
#define inA1 6
#define inA2 7
#define inB1 8
#define inB2 9

int stat = 200;
int vach = 0;

void Tien( byte speedL, byte speedR);
void Lui(byte SpeedL, byte SpeedR);
void doline();
int trangThai5CamBien ();
int lechvach5mat(int sens1, int sens2, int sens3, int sens4, int sens5);

void setup() {
  Serial.begin(9600);
  pinMode(6, OUTPUT);//Set chân in1 của dc A là output
  pinMode(7, OUTPUT);//Set chân in2 của dc A là output
  pinMode(8, OUTPUT);//Set chân in1 của dc B là output
  pinMode(9, OUTPUT);//Set chân in2 của dc B là output
  
  pinMode(A4, INPUT);//Set chân cảm biến 1 là input
  pinMode(A3, INPUT);//Set chân cảm biến 2 là input
  pinMode(A2, INPUT);//Set chân cảm biến 3 là input
  pinMode(A1, INPUT);//Set chân cảm biến 4 là input
  pinMode(A0, INPUT);//Set chân cảm biến 5 là input

  digitalWrite(inA1, HIGH);
  digitalWrite(inA2, LOW);
  digitalWrite(inB1, HIGH);
  digitalWrite(inB2, LOW); 
  
  Tien(100,85);
  delay(5);
}

void loop() {
  doline();
// digitalWrite(inB1, HIGH);
//  Tien(100,100);
//  Serial.println("Tien(100,100)");
//  delay(1000);
//  
//  Tien(100,0);
//  Serial.println("Tien(100,0)");
//  delay(1000);
//
//  Tien(100,100);
//  Serial.println("Tien(100,100)");
//  delay(1000);
//
//  digitalWrite(inB1, LOW);
//  Serial.println("inB1 = LOW");
//  delay(1000);
////  digitalWrite(inB2, LOW);
}

void doline()
{
  int trangthai = trangThai5CamBien();
//  Serial.println(trangthai);

 if (trangthai == 0) {
    trangthai = stat;
 }
// trangthai=200;
  switch (trangthai)
  {
    case 200:
      Tien(SpMaxL,SpMaxR);
      break;
    case 0:
      Tien(SpMaxL-10,SpMaxR-10);
      break;
    case 1:
      Tien(SpMaxL-10,10);
      break;
    case 2:
      Tien(SpMaxL-15,5);
      break;
    case 3:
      Tien(SpMaxL - 15,0);
      break;
    case -1:
      Tien(10,SpMaxR-10);
      break;
    case -2:
      Tien(5,SpMaxR-15);
      break;
    case -3:
      Tien(0,SpMaxR - 15);
      break;
    default:
      digitalWrite(6, 0);
      digitalWrite(7, 0);
      digitalWrite(8, 0);
      digitalWrite(9, 0);
      break;
  }
  Serial.println(trangthai);
  stat = trangthai;
//  delay(100);
}
boolean IFSensor (byte PinNumb)
{
  // Có line là 1
  return digitalRead(PinNumb);
}

int trangThai5CamBien ()
{
  /*
      Âm là lệch phải
      Dương là lệch trái
      Mức độ lệch giảm tăng dần : 1 2 3
  */
  int sens1 = IFSensor(A4);
  int sens2 = IFSensor(A3);
  int sens3 = IFSensor(A2);
  int sens4 = IFSensor(A1);
  int sens5 = IFSensor(A0);
   if (sens1 == 0 && sens5 == 0){
    vach = 1;
  }
  if (sens1 == 1 && sens5 == 1){
    vach = 0;
  }
  if (vach == 0){
    sens1 = !sens1;
    sens2 = !sens2;
    sens3 = !sens3;
    sens4 = !sens4;
    sens5 = !sens5;
  }
//  Serial.print(sens1);
//  Serial.print(" ");
//  Serial.print(sens2);
//  Serial.print(" ");
//  Serial.print(sens3);
//  Serial.print(" ");
//  Serial.print(sens4);
//  Serial.print(" ");
//  Serial.println(sens5); 
//  delay(500);
  switch (lechvach5mat(sens1, sens2, sens3, sens4, sens5))
  {
    case -3:
      return -3;
      break;
    case -2:
      return -2;
      break;
    case -1:
      return -1;
      break;
    case 0:
      if ( (abs(sens1) + abs(sens2) + abs(sens3) + abs(sens4) + abs(sens5)) == 0)
        return 0;
      else
        return 200;
      break;
    case 1:
      return 1;
      break;
    case 2:
      return 2;
      break;
    case 3:
      return 3;
      break;

  }
}
int lechvach5mat(int sens1, int sens2, int sens3, int sens4, int sens5)
{
  /*
      Âm là lệch phải
      Dương là lệch trái
      Mức độ lệch giảm tăng dần : 1 3 2
  */

  int lechvach = -2 * sens1 - sens2 + sens4 + 2 * sens5;
  switch (lechvach)
  {
    case -3:// cái này là do 2 mắt biên đều chạm vạch
      return -2;
      break;
    case -2:
      return -3;
      break;
    case -1:
      return -1;
      break;
    case 0:
      return 0;
      break;
    case 1:
      return 1;
      break;
    case 2:
      return 3;
      break;
    case 3:
      return 2;
      break;

  }

}
void Tien( byte speedL, byte speedR)
{
  analogWrite(5, speedL);
  analogWrite(10, speedR);
  digitalWrite(inA1, HIGH);
  digitalWrite(inA2, LOW);
  digitalWrite(inB1, HIGH);
  digitalWrite(inB2, LOW);
}
//void Retrai()
//{
//  analogWrite(5, 255);
//  analogWrite(10, 255);
//  digitalWrite(6, 0);
//  digitalWrite(7, 0);
//  digitalWrite(8, 1);
//  digitalWrite(9, 0);
//}
//void Rephai()
//{
//  analogWrite(5, 255);
//  analogWrite(10, 255);
//  digitalWrite(6, 1);
//  digitalWrite(7, 0);
//  digitalWrite(8, 0);
//  digitalWrite(9, 0);
//}
void Lui(byte SpeedL, byte SpeedR)
{
  analogWrite(5, SpeedL);
  analogWrite(10, SpeedR);
  digitalWrite(6, 0);
  digitalWrite(7, 1);
  digitalWrite(8, 0);
  digitalWrite(9, 1);
} 
