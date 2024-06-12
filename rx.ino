#include <HardwareSerial.h>

// Define the serial port (e.g., Serial2)
HardwareSerial MySerial(2);
char number = ' ';
void setup() {
  Serial.begin(115200);
  // Initialize UART (GPIO16 for RX, GPIO17 for TX)
  MySerial.begin(115200, SERIAL_8N1, 16, 17);
  // Give some time for the serial to initialize
  delay(1000);
}

void loop() {
  if (MySerial.available()) {
    char number = SerialPort.read();
     Serial.write(number);
    //String incomingMessage = MySerial.readStringUntil('\n');
    //Serial.println("Received: " + incomingMessage);
  }
}
