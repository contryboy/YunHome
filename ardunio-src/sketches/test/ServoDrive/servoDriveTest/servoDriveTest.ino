void setup() {
  Serial.begin(115200);

}

void loop() {
  Serial.println("#5 P1600 T500");
  delay(1000);
  Serial.println("#5 P1400 T500");
  delay(1000);
}
