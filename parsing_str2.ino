//Rx code same as in parsing_str
//#include <HardwareSerial.h>

void setup() {
  Serial.begin(115200);  // Initialize Serial Monitor
  Serial2.begin(9600, SERIAL_8N1, 16, 17);   // Initialize UART for communication between ESP32s
}

void loop() {
  if (Serial2.available()) {
    String data = Serial2.readStringUntil('\n');
    Serial.println("Received data: " + data);

    if (data[0] == '#') {  // Check for valid starting character
      data = data.substring(1);  // Remove starting character

      char address[16] = {0}, reading[8] = {0}, sensorId[8] = {0}, timestamp[16] = {0};
      int fieldIndex = 0;
      int charIndex = 0;
      char currentField[16] = {0};

      for (int i = 0; i <= data.length(); i++) {
        char c = data[i];
        if (c == ',' || c == '\0') {
          currentField[charIndex] = '\0';  // Null-terminate the current field
          switch (fieldIndex) {
            case 0: strncpy(address, currentField, sizeof(address)); break;
            case 1: strncpy(reading, currentField, sizeof(reading)); break;
            case 2: strncpy(sensorId, currentField, sizeof(sensorId)); break;
            case 3: strncpy(timestamp, currentField, sizeof(timestamp)); break;
          }
          fieldIndex++;
          charIndex = 0;  // Reset for next field
        } else {
          currentField[charIndex++] = c;
        }
      }

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
