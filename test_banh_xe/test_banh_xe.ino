// Định ngĩa các chân điều khiển động cơ
#define inA1 2 
#define inA2 3 
#define inB1 4
#define inB2 5 

#define hongngoai1 15
#define hongngoai2 16
#define hongngoai3 17
#define hongngoai4 18
#define hongngoai5 19

#define ENA 10
#define ENB 11

void setup() {
  pinMode(inA1, OUTPUT);
  pinMode(inA2, OUTPUT);
  pinMode(inB1, OUTPUT);
  pinMode(inB2, OUTPUT);
  pinMode(hongngoai1, INPUT);
  pinMode(hongngoai2, INPUT);
  pinMode(hongngoai3, INPUT);
  pinMode(hongngoai4, INPUT);
  pinMode(hongngoai5, INPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  Serial.begin(9600);
  analogWrite(ENA, 68);
  analogWrite(ENB, 68);//đi chậm cho khỏi trượt Line
}

void lui();
void dithang();
void quayphai();
void quaytrai();
int benphai, bentrai;
void loop(){
  benphai = digitalRead(hongngoai2);
  bentrai = digitalRead(hongngoai4);

  if (benphai == 0 && bentrai == 0) dithang();
  if (benphai == 1) quayphai();
  if (bentrai == 1) quaytrai();
//  if (benphai = 0 && bentrai = 0){lui();}//Trượt ra khỏi Line thì lùi lại
//  else {giatrilech = benphai - bentrai}
//  
//  if (giatrilech > 0){
//    Serial.println("Lệch trái");
//    quaytrai();//Lệch trái, thỳ quay trái
//  }
//  else if ((giatrilech < 0){
//    Serial.println("Lệch phải");
//    quayphai();//lệch phải thì quay phải
//  }
//  else if (giatrilech == 0){
//    dithang(); //Không lệch đi thẳng
//   }
 }


void lui(){
           digitalWrite(inA1,HIGH);
           digitalWrite(inA2,LOW);
           digitalWrite(inB1,HIGH);
           digitalWrite(inB2,LOW);
   
}
void dithang(){
           digitalWrite(inA1,LOW);
           digitalWrite(inA2,HIGH);
           digitalWrite(inB1,LOW);
           digitalWrite(inB2,HIGH);
}
void quayphai(){
           digitalWrite(inA2,HIGH);
           digitalWrite(inA1,LOW);
           
           digitalWrite(inB1,LOW);
           digitalWrite(inB2,LOW);
}
void quaytrai(){
           digitalWrite(inA1,LOW);
           digitalWrite(inA2,LOW);
           digitalWrite(inB2,HIGH);
           digitalWrite(inB1,LOW);
}
