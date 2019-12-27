int asdf;
void setup() {
  Serial3.begin(19200);
}

void loop() {
  asdf= (asdf+1)%100;
  Serial3.write(asdf);
  Serial3.flush();
}
