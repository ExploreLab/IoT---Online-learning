int PIN_D6 = 12;

void setup() {
  pinMode(PIN_D6, INPUT);
  Serial.begin(115200);
}

void loop() {
  int A = digitalRead(PIN_D6);
  Serial.print(A);
  if(A == 1){
    Serial.println(" HOLD");
  }else{
    Serial.println(" PRESS");
  }  
  delay(1000);

}
