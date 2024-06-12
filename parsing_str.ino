#include <HardwareSerial.h>

//Tx Code:
// void setup() {
//   Serial.begin(115200);  // For serial monitor
//   Serial2.begin(9600, SERIAL_8N1, 16, 17); // For UART
// }

// void loop() {
//   String data = "#192.168.1.2,23.5,1,1622557890";
//   Serial2.println(data);  // Send data over UART
//   Serial.println(data);
//   delay(1000);  // Send every second
// }

//Rx Code:
void setup() {
  Serial.begin(115200);  // Initialize Serial Monitor
  Serial1.begin(9600, SERIAL_8N1, 16, 17);   // Initialize UART for communication between ESP32s
}

void loop() {
  if (Serial1.available()) {
    String data = Serial1.readStringUntil('\n');
    Serial.println("Received data: " + data);

    if (data[0] == '#') {  // Check for valid starting character
      data = data.substring(1);  // Remove starting character

      char address[16], reading[8], sensorId[8], timestamp[16];
      int index = 0;
      int dataIndex = 0;
      int delimiterIndex = 0;

      while ((delimiterIndex = data.indexOf(',', dataIndex)) != -1) {
        String part = data.substring(dataIndex, delimiterIndex);
        switch (index) {
          case 0: part.toCharArray(address, 16); break;
          case 1: part.toCharArray(reading, 8); break;
          case 2: part.toCharArray(sensorId, 8); break;
        }
        dataIndex = delimiterIndex + 1;
        index++;
      }
      data.substring(dataIndex).toCharArray(timestamp, 16);

      // Print parsed data
      Serial.print("Address: ");
      Serial.println(address);
      Serial.print("Sensor Reading: ");
      Serial.println(reading);
      Serial.print("Sensor ID: ");
      Serial.println(sensorId);
      Serial.print("Timestamp: ");
      Serial.println(timestamp);
    }
  }
}
