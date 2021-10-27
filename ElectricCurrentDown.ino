#include <SoftwareSerial.h>
SoftwareSerial sim(10, 11);
int _timeout;
String _buffer;
String number = "+420607936139"; //-> change with your number

int a;
int b = 0;
int pinLed = 3;
int pinWaterLevel = 2;
bool smsOKSend = false;
bool smsKOSend = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(pinWaterLevel, INPUT);    // sets the digital pin 2 as input
  Serial.begin(9600);
  pinMode(pinLed, OUTPUT);// sets the pin 3 as output

  //sim module set
  _buffer.reserve(50);
  Serial.println("System starting...");
  sim.begin(9600);

}

void loop() {
  a = analogRead(A0);
  b = digitalRead(pinWaterLevel);

  if (sim.available()) {
    Serial.write(sim.read());
  }

  //kdyz WS zjisti vodu nebo photorezistor registruje zhasnuti svetla a zaroven nebyla poslana SMS a NESVITI ledka TAK(posli sms a rozsvit ledku, nezapomen nastavit booleany)
  if (b != 0 || a <= 500) {
    //pokud nebyla poslana SMS
    if (smsKOSend == false) {
      delay(100);//proti chybam
      digitalWrite(pinLed, HIGH);
      Serial.println("Ahoj! Zřejmě došlo k zavadě na odčerpávacím systému ve tvém objektu!");
      //zatim ne metodu send-- poplatky
      //SendMessage("Ahoj! Zřejmě došlo k zavadě na odčerpávacím systému ve tvém objektu!");
      smsKOSend = true;
      smsOKSend = false;
    }

    //kdyz se to opravi tj nahodi proud a WS je vyplej posli sms OK a zhasni ledku a nastav booleany
  } else if (b == 0 && a > 500 ) {
    delay(100);
    digitalWrite(pinLed, LOW);
    if (smsOKSend == false) {

      Serial.println("Ahoj tady Artur! To sem zase já, ale vypadá to, že je vše v pořádku!!");
      //zatim ne metodu send-- poplatky
      //SendMessage("Ahoj tady Artur! To sem zase já, ale vypadá to, že je vše v pořádku!!");
      smsOKSend = true;
      smsKOSend == false;
      digitalWrite(pinLed, LOW);
    }
  }
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
