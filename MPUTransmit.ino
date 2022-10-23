#include<Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
int acx,acy,flexvalue;

void setup()
{
  Wire.begin();
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop()
{
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68,4,true);
  acx=Wire.read()<<8|Wire.read();
  acy=Wire.read()<<8|Wire.read();
  flexvalue=analogRead(A0);
  int sentdata[3]={acx,acy,flexvalue};
  for(int i=0;i<3;i++)
  {
    Serial.println(sentdata[i]);
  }
  radio.write(sentdata, sizeof(sentdata));
  delay(100);
}
