int asdf;
void setup() {
  Serial.begin(19200);
  Serial1.begin(19200);
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, 0);
  //Serial.print(".");
  if (Serial1.available() > 0) {
    asdf = Serial1.read()-50;
    Serial.println(asdf);
    //delay(500);
  }
}
