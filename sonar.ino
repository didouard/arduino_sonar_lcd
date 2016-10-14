// SONAR
int trig = 7;
int echo = 6;
long echo_read;
long distance;

void initSonar() {
  // Ultra son
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);
}

long getDistance() {
  long ldistance;
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  echo_read = pulseIn(echo, HIGH);
  ldistance = echo_read / 58;
  /*/Serial.print("Distance : ");
  Serial.println(distance);/**/
  return ldistance + 2;
}
