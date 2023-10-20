#include "Arduino.h"
#include "GuitarString.h"
#include "Adafruit_VL53L0X.h"

GuitarString::GuitarString() {
  rID = random(9999);
}

void GuitarString::Init(int RecieverPin, int XShutPin, uint8_t LOXAddress, Adafruit_VL53L0X *LOX) {
    _RecieverPin = RecieverPin;
    _LOXAddress = LOXAddress;
    _XShutPin = XShutPin;

    _LOX = LOX;
    delay(500);

    Serial.print("_ReceiverPin: ");
    Serial.print(_RecieverPin);
    Serial.print(" _XShutPin: ");
    Serial.print(_XShutPin);
    Serial.print(" _LOXAddress: ");
    Serial.println(_LOXAddress);
    //Serial.print("_ReceiverPin: ");
    //Serial.print();
 
    pinMode(_RecieverPin, INPUT);
    pinMode(_XShutPin, OUTPUT);
    digitalWrite(_XShutPin, LOW);
    delay(15);
}

void GuitarString::Reset() {
  digitalWrite(_XShutPin, HIGH);
  delay(15);
  digitalWrite(_XShutPin, LOW);
  delay(15);
}

bool GuitarString::Enable() {
  // enable
  digitalWrite(_XShutPin, HIGH);
  delay(15);

  // initialize VL53LOX
  if(_LOX->begin()) {
    delay(500);
    return true;
  }
  return false;
}

bool GuitarString::SetAddress() {
  if(_LOX->setAddress(_LOXAddress)) {
    delay(500);
    return true;
  }
  return false;  
}

uint8_t GuitarString::GetAddress() {
  return _LOX->pMyDevice->I2cDevAddr;  
}
    
uint16_t GuitarString::ReadMillimeters() {
  _LOX->rangingTest(&_MData, false);
  if(_MData.RangeStatus != 4) {
    Serial.println(_MData.RangeMilliMeter);
    return _MData.RangeMilliMeter;
  }
  return 9999;
}

bool GuitarString::IsStringHit(){
  // int value = digitalRead(RecieverPin);
 // Serial.println(value);
//  if(value == HIGH) return true;
//  return false;
//depricated
}

 
void GuitarString::SetScale() {
  
}

int GuitarString::ReadNote() {
      
}
