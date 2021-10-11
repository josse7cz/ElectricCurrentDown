

int a;
bool running = false;
int LEDpin = 3;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LEDpin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  a = analogRead(A0);
  if (a <= 500 && running == false) {
    digitalWrite(LEDpin, HIGH);
    for (int i = 1; i < 20; i++) {
      Serial.println("POslat SMS");
      running = true;
      break;
    }
  } else if (a > 500 && running) {
    delay(100);
    running = false;
    digitalWrite(LEDpin, LOW);

  }
  Serial.println(a);
}
