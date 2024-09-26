#include <Arduino.h>
#include <ESP32Servo.h> 
#include <TwoWayESP.h>

const int PinA1 = 19;
const int PinA2 = 18;
const int PinB1 = 17;
const int PinB2 = 16;
byte speed = 250;
uint8_t broadcastAddress[] = {0x08,0xD1,0xF9,0xE1,0xC9,0x58};
Servo RightFing;
Servo RightElb;
Servo RightBic;
Servo RightShoul;  
///////////////
Servo LeftFing;
Servo LeftElbow;
Servo LeftBic;
Servo LeftShoul;
//////////////
Servo myservo9;
Servo myservo10;

int rightFingers = 13; // Клешня правая      
int rightElbow = 12; // локоть правая 
int rightBiceps = 14; // бицепс правый 
int rightShoulder = 27; //плечо правое 
///////////////////////
int leftFingers = 26; // левая клешня     
int leftElbow = 25; // левый локоть
int leftBiceps = 33; // левый бицепс
int leftShoulder = 32; // левое плечо 
////////////////////////
int servoPin9 = 21;///поворотное колесо
int servoPin10 = 22;///поворот торса
typedef struct ServoAngles{
    uint16_t id;
    uint16_t Serv1; // левый локоть д13
    uint16_t Serv2; // левое плечо1 д14 
    uint16_t Serv3; //  левое плечо2 д12 
    uint16_t Serv4; // правое плечо1 д33
    uint16_t Serv5; // правое плечо2 д25
    uint16_t Serv6; // правый локоть д26
    uint16_t buttRight; //поворот направо 
    uint16_t buttLeft; // поворот налево 
    uint16_t buttFront; // езда вперед 
    uint16_t buttBack; // езда назад
    uint16_t buttLeftHand; // левая клешня 
    uint16_t buttRightHand; // правая клешня 
    uint16_t RotBody; // поворот тела 
} ServoAngles;

ServoAngles recv;

void setup()
{
  Serial.begin(115200);
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  /////////////////////////////
  RightFing.setPeriodHertz(50);
  RightElb.setPeriodHertz(50);
  RightBic.setPeriodHertz(50);
  RightShoul.setPeriodHertz(50);
////////////////////////////////
  LeftFing.setPeriodHertz(50);
  LeftElbow.setPeriodHertz(50);
  LeftBic.setPeriodHertz(50);
  LeftShoul.setPeriodHertz(50);
//////////////////////////////
  myservo9.setPeriodHertz(50);
  myservo10.setPeriodHertz(50);
  ////////////////////////////////
  RightFing.attach(rightFingers, 500, 2400);
  RightElb.attach(rightElbow, 500, 2400);
  RightBic.attach(rightBiceps, 500, 2400);
  RightShoul.attach(rightShoulder, 500, 2400);
///////////////////////////////////////
  LeftFing.attach(leftFingers, 500, 2400);
  LeftElbow.attach(leftElbow, 500, 2400);
  LeftBic.attach(leftBiceps, 500, 2400);
  LeftShoul.attach(leftShoulder, 500, 2400);
////////////////////////////////////////
  myservo9.attach(servoPin9, 500, 2400);
  myservo10.attach(servoPin10, 500, 2400);
  pinMode(PinA1,OUTPUT);
  pinMode(PinA2,OUTPUT);
  pinMode(PinB1,OUTPUT);
  pinMode(PinB2,OUTPUT);
   // Выставляем режим работы WiFi
	TwoWayESP::Begin(broadcastAddress);
}

void backward() // Вперед.
{
  analogWrite(PinA1, 0);
  analogWrite(PinA2, speed);
  analogWrite(PinB1, 0);
  analogWrite(PinB2, speed);
}
void forward() //Назад...
{
  analogWrite(PinA1, speed);
  analogWrite(PinA2, 0);
  analogWrite(PinB1, speed);
  analogWrite(PinB2, 0);
}
void left() // В левую сторону
{
  analogWrite(PinA1, speed);
  analogWrite(PinA2, 0);
  analogWrite(PinB1, 0);
  analogWrite(PinB2, speed);
}
void right() //В правую сторону
{
  analogWrite(PinA1, 0);
  analogWrite(PinA2, speed);
  analogWrite(PinB1, speed);
  analogWrite(PinB2, 0);
}
void stop() //Стоп
{
  analogWrite(PinA1, 0);
  analogWrite(PinA2, 0);
  analogWrite(PinB1, 0);
  analogWrite(PinB2, 0);
  delay (2000);
}

void loop() {
  	if(TwoWayESP::Available()) {
		TwoWayESP::GetBytes(&recv, sizeof(ServoAngles));
  LeftElbow.write(recv.Serv6);//локоть левый
  Serial.println(recv.Serv6);
  LeftBic.write(recv.Serv5);//локоть левый
  Serial.println(recv.Serv5);
  LeftShoul.write(recv.Serv4);//локоть левый
  Serial.println(recv.Serv4);
  RightElb.write(recv.Serv1);//правая локоть+
  Serial.println(recv.Serv1);
  RightBic.write(recv.Serv2);//правый бицепс
  Serial.println(recv.Serv2);
  RightShoul.write(recv.Serv3);//правое плечо
  Serial.println(recv.Serv3);
    }
    delay(10);
}