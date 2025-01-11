const int trigPin = 10;    // 초음파 센서 Trig 핀
const int echoPin = 11;    // 초음파 센서 Echo 핀
const int motorA_IA = 3;   // L9110S 모터 A IA 핀
const int motorA_IB = 5;   // L9110S 모터 A IB 핀

void setup() {
  Serial.begin(9600);      // 시리얼 통신 시작
  pinMode(trigPin, OUTPUT);  // Trig 핀을 출력 모드로 설정
  pinMode(echoPin, INPUT);   // Echo 핀을 입력 모드로 설정
  pinMode(motorA_IA, OUTPUT); // 모터 A IA 핀을 출력 모드로 설정
  pinMode(motorA_IB, OUTPUT); // 모터 A IB 핀을 출력 모드로 설정
}

void loop() {
  long duration, distance;
  int speed;

  // 초음파 센서 펄스 발생
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // 초음파 반사 시간 측정
  duration = pulseIn(echoPin, HIGH);

  // 거리 계산 (음속 340m/s 기준, cm 단위)
  distance = duration / 29 / 2;

  // 거리 값에 따른 속도 계산
  if (distance <= 10) {
    speed = 0;  // 너무 가까우면 정지
  } else if (distance <= 30) {
    speed = map(distance, 10, 30, 50, 255); // 거리에 따라 속도 조절
  } else {
    speed = 255; // 멀리 있으면 최대 속도
  }

  // L9110S 모터 속도 및 방향 제어
  if (speed == 0) {
    digitalWrite(motorA_IA, LOW);
    digitalWrite(motorA_IB, LOW); // 정지
  } else {
    // 속도에 따른 PWM 생성
    analogWrite(motorA_IA, speed);
    digitalWrite(motorA_IB, LOW); // 정방향 (속도 제어는 IA 핀에서)
  }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm, ");
  Serial.print("Speed: ");
  Serial.println(speed);

  delay(100);
}
