//#ifndef GuitarString_h
#define GuitarString_h
#include "Arduino.h"
#include "Adafruit_VL53L0X.h"

class GuitarString {

public:
    GuitarString();
    void Init(int RecieverPin,int XShutPin, uint8_t LOXAddress, Adafruit_VL53L0X *LOX);
    void Reset();
    bool Enable();
    bool SetAddress();
    uint8_t GetAddress();
    uint16_t ReadMillimeters();
    void SetScale();
    int ReadNote();
    bool IsStringHit();
    int rID;
    Adafruit_VL53L0X *_LOX;
    VL53L0X_RangingMeasurementData_t _MData;
    
private:
   int _RecieverPin;
   uint8_t _LOXAddress; 
   int _XShutPin; 
   
};

//#endif
