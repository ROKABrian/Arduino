#define MOTOR_A1 9
#define MOTOR_A2 10
#define LED_PIN 11
#define TRIG_PIN 2  // 초음파 트리거 핀
#define ECHO_PIN 3  // 초음파 에코 핀

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(MOTOR_A1, OUTPUT);
  pinMode(MOTOR_A2, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration / 29 / 2;
}

void loop() {
  unsigned int vr = map(analogRead(A0), 0, 1023, 0, 511);
  int ledBrightness = map(vr, 0, 511, 0, 255);
  analogWrite(LED_PIN, ledBrightness);

  long distance = getDistance();
    
  int motorSpeed;
  if (distance > 50) {
      motorSpeed = 255;
  } else if (distance > 20) {
      motorSpeed = map(distance, 20, 50, 100, 255);
  } else {
      motorSpeed = 50;
  }

  if (vr < 256) {
    analogWrite(MOTOR_A1, motorSpeed - vr);
    analogWrite(MOTOR_A2, 0);
    Serial.print("front - ");
    Serial.println(motorSpeed - vr);
  } else {
    analogWrite(MOTOR_A1, 0);
    analogWrite(MOTOR_A2, vr - 256);
    Serial.print("back - ");
    Serial.println(vr - 256);
  }
  delay(10);
}
