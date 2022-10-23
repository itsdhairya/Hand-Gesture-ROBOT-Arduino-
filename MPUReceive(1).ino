#include<Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include<Servo.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
Servo myservo[4];
int acx,acy,flexvalue,base,arm1,arm2,grip;

void setup()
{
  myservo[0].attach(3);
  myservo[1].attach(5);
  myservo[2].attach(6);
  myservo[3].attach(9);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() 
{
  if (radio.available()) 
  {
    int receiveddata[3];
    radio.read(receiveddata,sizeof(receiveddata));
    acx=receiveddata[0];
    acy=receiveddata[1];
    flexvalue=receiveddata[2];
    for(int i=0;i<3;i++)
    {
      Serial.println(receiveddata[i]);
    }
    base=map(acy,-17000,17000,0,180);
    arm1=map(acx,17000,-17000,170,90);
    arm2=map(acx,17000,-17000,10,90);
    grip=map(flexvalue,750,900,0,180);
    myservo[0].write(base);
    myservo[1].write(arm1);
    myservo[2].write(arm2);
    myservo[3].write(grip);
    delay(100);
  }
}
