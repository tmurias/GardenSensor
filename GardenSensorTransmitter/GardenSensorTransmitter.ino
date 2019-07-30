#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 4

RH_ASK driver;
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);
DeviceAddress tempDeviceAddress; // We'll use this variable to store a found device address

int numberOfDevices; // Number of temperature devices found

 
void setup()
{
  Serial.begin(9600);    // Debugging only
  if (!driver.init())
    Serial.println("init failed");


  sensors.begin(); // Start up the library
  numberOfDevices = sensors.getDeviceCount();   // Grab a count of devices on the wire

  uint8_t test[2];
  get_temperatures(test);
}

void loop()
{

  int val;
  val = analogRead(A0); //connect sensor to Analog 0 Serial.print(val); //print the value to serial port delay(100);
  uint8_t val_byte = (val + 1) / 4 - 1; //converting to byte (1023 -> 255)

  //const char *msg = "Hello 499 :)";
  const uint8_t msg[12] = {val_byte, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //transmitter sends 12 bytes so only using the first value in this case


  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
  delay(1000);
}

void get_temperatures(uint8_t* values)
{
  float offset = 50;
  sensors.requestTemperatures(); // Send the command to get temperatures

  // Loop through each device, print out temperature data
  for (int i = 0; i < numberOfDevices; i++) {
    // Search the wire for address
    if (sensors.getAddress(tempDeviceAddress, i)) {

      float t = sensors.getTempC(tempDeviceAddress);
      //convert to byte
      if ( t > 50 ) {
        t = 50 ;
      }
      if ( t < -50 ) {
        t = -50  ;
      }

      t = t + offset;

      values[i] = (uint8_t)t;
    }
  }
}
