#include <ArduinoJson.h>

#define MAX_FIELDS 10
#define MAX_FIELD_LENGTH 11  // 10 characters + '\0'

char inputString[] = "#0x85 0x75,1,150,200,25.5,1623456789\n";  // Example input for heights
char fields[MAX_FIELDS][MAX_FIELD_LENGTH];
int num_fields = 0;

void setup() {
  Serial.begin(9600);
  extractFields(inputString + 1);  // Skip the initial '#'

  Serial.println("Extracted fields:");
  for (int i = 0; i < num_fields; ++i) {
    Serial.print("Field ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(fields[i]);
  }

  String jsonString = createJson();
  Serial.println("JSON String:");
  Serial.println(jsonString);
}

void loop() {
}

void extractFields(char *str) {
  num_fields = 0;
  char *start = str;

  for (char *ptr = str; *ptr != '\0'; ++ptr) {
    if (*ptr == ',' || *ptr == '\n') {
      int length = ptr - start;
      if (length < MAX_FIELD_LENGTH) {
        strncpy(fields[num_fields], start, length);
        fields[num_fields][length] = '\0';
        num_fields++;
      }
      start = ptr + 1;

      // Stop processing if we hit the maximum number of fields
      if (num_fields >= MAX_FIELDS) {
        break;
      }
    }
  }

  // Handle the last field if there was no comma or newline at the end
  if (*start != '\0' && num_fields < MAX_FIELDS) {
    strncpy(fields[num_fields], start, MAX_FIELD_LENGTH - 1);
    fields[num_fields][MAX_FIELD_LENGTH - 1] = '\0';
    num_fields++;
  }
}

String createJson() {
  StaticJsonDocument<256> doc;  // Static memory allocation

  if (num_fields >= 4) {  // Ensure there are enough fields to work with
    doc["mac_address"] = fields[0];
    int type = atoi(fields[1]);

    switch (type) {
      case 0:  // RPM data
        if (num_fields >= 4) {  // Ensure there are enough fields for rpm_value and timestamp
          doc["type"] = "rpm";
          doc["rpm_value"] = fields[2];
          doc["timestamp"] = fields[3];
        }
        break;
      case 1:  // Heights data
        if (num_fields >= 6) {  // Ensure there are enough fields for height1, height2, temperature, and timestamp
          doc["type"] = "height";
          doc["height1"] = fields[2];
          doc["height2"] = fields[3];
          doc["temperature"] = fields[4];
          doc["timestamp"] = fields[5];
        }
        break;
      default:
        doc["type"] = "unknown";
        doc["value"] = fields[2];
        if (num_fields > 3) {
          doc["timestamp"] = fields[3];
        }
        break;
    }
  }

  String jsonString;
  serializeJson(doc, jsonString);
  return jsonString;
}


// output:
// !�z�C���\�)�A�Extracted fields:
// Field 1: 0x85 0x75
// Field 2: 1
// Field 3: 150
// Field 4: 200
// Field 5: 25.5
// Field 6: 1623456789
// JSON String:
// {"mac_address":"0x85 0x75","type":"height","height1":"150","height2":"200","temperature":"25.5","timestamp":"1623456789"}
