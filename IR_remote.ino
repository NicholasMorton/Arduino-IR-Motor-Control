
/**** IR remote related code modified from the source below ****/ 
/*
  Code belongs to this video https://www.youtube.com/watch?v=wqZwQnh6ZtQ
  writen by Moz for YouTube changel logmaker360.
  13-04-2016
  code works on a car mp3 remote controller
*/



#include <IRremote.h>
// remote constants
int RECV_PIN = 12;
int BLUE_LED = 13;
int RED_LED = 8;
// motor constants
int enablePin = 11;
int in1Pin = 10;
int in2Pin = 9;
// motor direction
boolean reverse;
int speed;
int SPEED = 250;



IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  // **** remote setup *****/
  // initialize the digital pin as an output.
  pinMode(RECV_PIN, INPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
  // **** motor setup *****/
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  speed = 0;
  reverse = false;
  Serial.begin(9600);
}
void loop() {
  int i = 0;
  if (irrecv.decode(&results)) {
    translateIR();
    unknownRemoter();
    irrecv.resume(); // Receive the next value
  }
  // first run: speed at reduced power just to test
  //int speed = 200;
  setMotor(speed, reverse);
}

void translateIR() // takes action based on IR code received describing Car MP3 IR codes
{

  switch (results.value) {
    case 0xFFA25D:
      Serial.println(" CH-            ");
      break;
    case 0xFF629D:
      Serial.println(" CH             ");
      break;
    case 0xFFE21D:
      Serial.println(" CH+            ");
      break;
    case 0xFF22DD:
      Serial.println(" blue LED off          ");
      digitalWrite(BLUE_LED, LOW);
      break;
    case 0xFF02FD:
      Serial.println(" blue LED on        ");
      digitalWrite(BLUE_LED, HIGH);
      break;
    case 0xFFC23D:
      Serial.println(" PLAY/PAUSE     ");
      break;
    case 0xFFE01F:
      Serial.println(" VOL-           ");
      break;
    case 0xFFA857:
      Serial.println(" VOL+           ");
      break;
    case 0xFF906F:
      Serial.println(" EQ             ");
      break;
    case 0xFF6897:
      Serial.println(" 0              ");
      break;
    case 0xFF9867:
      Serial.println(" 100+           ");
      break;
    case 0xFFB04F:
      Serial.println(" 200+           ");
      break;
    case 0xFF30CF:
      Serial.println(" 1              ");
      break;

    case 0xFF18E7:
      Serial.println(" 2              ");
      break;

    case 0xFF7A85:
      Serial.println(" 3              ");
      break;

    case 0xFF10EF:
      Serial.println(" 4              ");
      break;

    case 0xFF38C7:
      Serial.println(" 5              ");
      break;

    case 0xFF5AA5:
      Serial.println(" 6              ");
      break;

    case 0xFF42BD:
      Serial.println(" 7              ");
      break;

    case 0xFF4AB5:
      Serial.println(" 8              ");
      break;

    case 0xFF52AD:
      Serial.println(" 9              ");
      break;

    default:
      Serial.print(" unknown button   ");
      Serial.println(results.value, HEX);

  }

  delay(250);


}

void unknownRemoter() {                      //this function is from an old remoter see video.
  long MOTOR_FORWARD = 0xFFC23D;
  long MOTOR_REVERSE =  0xFF906F;
  long MOTOR_STOP = 0xFFB04F;

  if (results.value == MOTOR_FORWARD) {
    Serial.println ("Motor forward");
    reverse = false;
    speed = SPEED;
    digitalWrite(RED_LED, LOW);
  }
  else if (results.value == MOTOR_REVERSE )
  {
    Serial.println ("Motor reverse");
    reverse = true;
    speed = SPEED;
    digitalWrite(RED_LED, HIGH);
  }
  else if (results.value == MOTOR_STOP )
  {
    Serial.println ("Motor stop");
    speed = 0;
  } else {
    Serial.print(" still an unknown button   ");
    Serial.println(results.value, HEX);
  }
}




/********** MOTOR CODE ************/
/*
  Adafruit Arduino - Lesson 15. Bi-directional Motor
*/
/*
  int enablePin = 11;
  int in1Pin = 10;
  int in2Pin = 9;
  //int switchPin = 7;
  //int potPin = 0;

  void setup()
  {
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  //pinMode(switchPin, INPUT_PULLUP);
  }

  void loop()
  {
  // first run: speed at reduced power just to test
  int speed = 200;
  setMotor(speed, reverse);
  }
*/

void setMotor(int speed, boolean reverse)
{
  analogWrite(enablePin, speed);
  digitalWrite(in1Pin, ! reverse);
  digitalWrite(in2Pin, reverse);
}



