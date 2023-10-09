#include <SparkFun_ADXL345.h>       
ADXL345 adxl = ADXL345();             // I2C Comunicatie
int x = 0;
int y = 0;
int z = 0;
void setup(){

  Serial.begin(9600);                
  adxl.powerOn();                     
  adxl.setRangeSetting(8);           //Range setting 
  adxl.setTapDetectionOnXYZ(0, 0, 1);
  adxl.setDoubleTapLatency(80);       // 1.25 ms per increment
  adxl.setDoubleTapWindow(200);       // 1.25 ms per increment
  adxl.setFreeFallThreshold(7);       // (5 - 9) recomandat - 62.5mg per increment
  adxl.setFreeFallDuration(30);       // (20 - 70) reomandat - 5ms per increment
  adxl.FreeFallINT(1);
  adxl.doubleTapINT(1);
} 
void loop(){ 
  adxl.readAccel(&x, &y, &z);       
  Serial.write(x);  
  Serial.write(y);
  Serial.write(z);
  delay(70);
}



