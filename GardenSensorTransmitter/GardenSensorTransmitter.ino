#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;

void setup()
{
  Serial.begin(9600);    // Debugging only
  if (!driver.init())
    Serial.println("init failed");

  uint8_t test[2];
  get_temperatures(test);
}

void loop()
{

  int val;
  val = analogRead(A0); //connect sensor to Analog 0 Serial.print(val); //print the value to serial port delay(100);
  uint8_t val_byte = (val+1)/4-1; //converting to byte (1023 -> 255)
    
  //const char *msg = "Hello 499 :)";
  const uint8_t msg[12] = {val_byte,0,0,0,0,0,0,0,0,0,0,0}; //transmitter sends 12 bytes so only using the first value in this case
    
    
  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
  delay(1000);
}

void get_temperatures(uint8_t* values)
{
  values[0] = 1; // TODO: Get actual value
  values[2] = 2; // TODO: Get actual value
}
