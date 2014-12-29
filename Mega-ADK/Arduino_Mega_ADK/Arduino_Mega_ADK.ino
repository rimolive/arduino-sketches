#include <Max3421e.h>
#include <Usb.h>
#include <AndroidAccessory.h>

#define LED_PIN 13
AndroidAccessory acc("Manufacturer",
"Model",
"Description",
"1.0",
"http://yoursite.com",
"0000000012345678");
void setup()
{
  // set communiation speed
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  acc.powerOn();
}

void loop()
{
  byte msg[1];
  if (acc.isConnected()) {
    int len = acc.read(msg, sizeof(msg), 1); // read data into msg variable
    if (len > 0) {
      if (msg[0] == 1) // compare received data
        digitalWrite(LED_PIN,HIGH); // turn on light
      else
        digitalWrite(LED_PIN,LOW); // turn off light
    }
  }
  else
    digitalWrite(LED_PIN , LOW); // turn off light
}

