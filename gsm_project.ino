#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2

#define Motion_Sensor A0
const int  alarm = 7;

bool Sensor_State;

void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);

  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);
  pinMode(alarm, OUTPUT);
  Serial.println("Initializing...");
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, i t will back to OK
  updateSerial();

  mySerial.println("ATH"); //hang up
  updateSerial();
}


void loop()
{
  Sensor_State = digitalRead(Motion_Sensor);   //We are constantly reading the button State

  if (Sensor_State == HIGH) {            //And if it's pressed
    Serial.println("Sensor detect motion");   //Shows this message on the serial monitor
    delay(200);                         //Small delay to avoid detecting the button press many times

    digitalWrite(alarm, HIGH);
    makeCall();                          //And this function is called

  }
  else {
    Serial.println(".");
    digitalWrite(alarm, LOW);
  }
}


void updateSerial()
{
  delay(500);
  while (Serial.available())
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }

  while (mySerial.available())
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}


void makeCall() {

  Serial.begin(9600);

  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);
  digitalWrite(alarm, LOW);
  mySerial.println("AT"); //Once the handshake test is successful, i t will back to OK
  updateSerial();
  mySerial.println("AT+CMGF=1");
  updateSerial();
  mySerial.println("AT+CMGS=\"+8801797750545 \"");
  updateSerial();
  mySerial.print("Warning !!! | Human Detected");
  updateSerial();

  mySerial.write(26);
  delay(15000);
  updateSerial();
  mySerial.println("AT");
  updateSerial();
  mySerial.println("ATD+ +8801797750545 ;"); //  change ZZ with country code and xxxxxxxxxxx with phone number to dial
  updateSerial();
  delay(20000); // wait for 20 seconds...
  mySerial.println("ATH"); //hang up
  updateSerial();

}
