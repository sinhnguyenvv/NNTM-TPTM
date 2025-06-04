const int trigPin = 9;
const int echoPin = 8;
const int ledPin = 7;
const float maxHeight = 40.0; // chiều cao thùng rác (cm)

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

float readDistanceCM() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;
  return distance;
}

void loop() {
  float distance = readDistanceCM();
  float fillLevel = 100 - (distance / maxHeight) * 100;
  fillLevel = constrain(fillLevel, 0, 100);

  Serial.print("Mức rác: ");
  Serial.print(fillLevel);
  Serial.println("%");

  if (fillLevel >= 80) {
    digitalWrite(ledPin, HIGH);  // Bật đèn
  } else {
    digitalWrite(ledPin, LOW);   // Tắt đèn
  }

  delay(5000); // đo mỗi 5 giây
}