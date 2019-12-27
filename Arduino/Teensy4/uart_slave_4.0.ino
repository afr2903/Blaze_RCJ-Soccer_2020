int asdf;
void setup() {
  Serial.begin(19200);
  Serial3.begin(19200);
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, 0);
  if (Serial3.available() > 0) {
    asdf = Serial3.read();
    Serial.println(asdf);
  }
}
