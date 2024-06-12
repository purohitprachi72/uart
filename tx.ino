#include <HardwareSerial.h>
HardwareSerial SerialPort(2); //2Tx/Rx gpio on esp32
void setup() {
  Serial.begin(115200);
  SerialPort.begin(115200,SERIAL_8N1,16,17);
}
void loop() {
  SerialPort.print("Hello!");
  delay(100);
}
