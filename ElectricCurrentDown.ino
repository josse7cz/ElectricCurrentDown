#include <SoftwareSerial.h>
SoftwareSerial sim(10, 11);
int _timeout;
String _buffer;
String number = "+420720119000"; //-> change with your number

int a;
bool running = false;
int LEDpin = 3;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LEDpin, OUTPUT);
  //sim module set
  _buffer.reserve(50);
  Serial.println("System starting...");
  sim.begin(9600);

}

void loop() {
   a = analogRead(A0);

  if (sim.available() > 0) {
    Serial.write(sim.read());
  }


  if (a <= 500 && running == false) {
    delay(100);
    digitalWrite(LEDpin, HIGH);
    for (int i = 1; i < 20; i++) {

      //Serial.println("Ahoj! Zřejmě došlo k výpadku proudu ve tvém objektu zájmu");
      SendMessage("Ahoj, já jsem Artur. Zřejmě došlo k výpadku proudu ve tvém objektu zájmu");
      running = true;
      break;
    }
  } else if (a > 500 && running) {
    delay(1000);
    running = false;
    digitalWrite(LEDpin, LOW);
    //Serial.println("Ahoj tady Artur! To sem zase já, ale vypadá to, že proud je zase zpět!!");
    SendMessage("Ahoj tady Artur! To sem zase já, ale vypadá to, že proud je zpět!!");

  }
  Serial.println(a);
}
void SendMessage(String Text)
{
  //Serial.println ("Sending Message");
  sim.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(200);
  //Serial.println ("Set SMS Number");
  sim.println("AT+CMGS=\"" + number + "\"\r"); //Mobile phone number to send message
  delay(200);
  String SMS = Text;
  sim.println(SMS);
  delay(100);
  sim.println((char)26);// ASCII code of CTRL+Z
  delay(200);
  _buffer = _readSerial();
}
String _readSerial() {
  _timeout = 0;
  while  (!sim.available() && _timeout < 12000  )
  {
    delay(13);
    _timeout++;
  }
  if (sim.available()) {
    return sim.readString();
  }
}
