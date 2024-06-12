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

      const int numFields = 4;
      String fields[numFields];
      int fieldIndex = 0;
      int startIndex = 0;

      for (int i = 0; i <= data.length(); i++) {
        if (data[i] == ',' || data[i] == '\0') {
          fields[fieldIndex++] = data.substring(startIndex, i);
          startIndex = i + 1;
          if (fieldIndex >= numFields) break;  // Avoid overflow if more fields than expected
        }
      }

      if (fieldIndex < numFields) {
        fields[fieldIndex] = data.substring(startIndex);  // Capture the last field
      }

      // Print parsed data
      Serial.print("Address: ");
      Serial.println(fields[0]);
      Serial.print("Sensor Reading: ");
      Serial.println(fields[1]);
      Serial.print("Sensor ID: ");
      Serial.println(fields[2]);
      Serial.print("Timestamp: ");
      Serial.println(fields[3]);
    }
  }
}
