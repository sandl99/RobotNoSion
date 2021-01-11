void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
 // 1 la den
 // 0 la trang
  //Serial.print("Cam bien ");
  delay(500);
  Serial.println(digitalRead(16));
}
