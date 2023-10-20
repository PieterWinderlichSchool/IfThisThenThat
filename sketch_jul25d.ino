#include "GuitarString.h"

#define AOS 2 // Amount of Strings

//const int pinlaser = 2;
//const int pinReciever = 3;
int amountOfStrings = 2;

GuitarString GuitarStrings[AOS];

Adafruit_VL53L0X TOFS[6] = {Adafruit_VL53L0X(), Adafruit_VL53L0X(), Adafruit_VL53L0X(), Adafruit_VL53L0X(), Adafruit_VL53L0X(), Adafruit_VL53L0X()};//Time of flight sensor initialisation
//VL53L0X_RangingMeasurementData_t MDatas[6];
uint8_t XShutPins[6]    = {7, 6, 5, 4, 3, 2}; //ToF PinAdress
uint8_t LOXAddresses[6] = {0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f}; //ToF Data Adress
uint8_t ReceiverPins[6] = {30,29,28,27,26,25};//Laser Reciever Pins


void setup() {
  Serial.begin(115200);

  //pinMode(pinLaser, OUTPUT); // set the laser pin to output mode
  // set the laser pin to output mode

  //digitalWrite(pinLaser, HIGH); // emit red laser
   // Setup serial connection for print out to console


  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }

  // create instances of guitar string
  for(int i = 0; i < AOS; i++) {
    GuitarStrings[i] = GuitarString();
    GuitarStrings[i].Init(ReceiverPins[i], XShutPins[i], LOXAddresses[i], &TOFS[i]);
    
    Serial.print("Random id: ");
    Serial.println(GuitarStrings[i].rID);
    Serial.println("- - - - - - - -");
  }

  Serial.println("Setting addresses...");

  // boot and set addresses
  for(int c = 0; c < AOS; c++) {
    Serial.print("<< String inx: ");
    Serial.print(c);
    Serial.println(" >>");
    //GuitarStrings[c].Reset();
    if(GuitarStrings[c].Enable()) {
      Serial.print("rID: ");
      Serial.print(GuitarStrings[c].rID);
      Serial.print(" enabled! > current address: ");
      Serial.print(GuitarStrings[c].GetAddress());
      Serial.print(" > setting address... ");
      if(GuitarStrings[c].SetAddress()) {
        Serial.print("> new address: ");
        Serial.println(GuitarStrings[c].GetAddress());
      } else Serial.println("> Addres could not be set!");
    } else {
      Serial.print("rID: ");
      Serial.print(GuitarStrings[c].rID);
      Serial.println(" could not be enabled!");
    }
  }
  //pinMode(pinReciever, INPUT);
}

void loop() {

  for(int i = 0; i < amountOfStrings; i++) {
    int rangeMMS = GuitarStrings[i].ReadMillimeters();
    Serial.print("Addr: ");
    Serial.print(GuitarStrings[i].GetAddress());
    Serial.print(" range in mm's: ");
    Serial.println(rangeMMS);
  }
  Serial.println("*-*-*-*-*-*-*");
  
  delay(7000);

  //int value = digitalRead(pinReciever);
  //Serial.println(value);

}
