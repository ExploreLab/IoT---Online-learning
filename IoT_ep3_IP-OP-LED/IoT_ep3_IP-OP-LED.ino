int A;
int PIN_D6 = 12;
int LED_D5 = 14;
int LED_WIFI = 2;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_D6, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_D5, OUTPUT);
  pinMode(LED_WIFI, OUTPUT);

}

void loop() {
  int A = digitalRead(PIN_D6);
  //Serial.println(A);
  delay(200);
  if(A == 0){
    Serial.println("PRESS");
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(LED_D5, HIGH);
    digitalWrite(LED_WIFI, HIGH);
    delay(100);
  }else{
    Serial.println("HOLD");
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(LED_D5, LOW);
    digitalWrite(LED_WIFI, LOW);
    delay(100);
  }
}
