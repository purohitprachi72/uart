// String data = "#00:11:22:33:44:55,12,25,61424\n";

// void setup(){
//   Serial.begin(115200);
//   Serial1.begin(115200, SERIAL_8N1, 16, 17);
// }

// void loop(){
//   Serial1.print(data);
//   delay(1000);
//   Serial.println(data);
// }

char data[] = "#00:11:22:33:44:55,12,25,61424\n";
void setup(){
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, 16,17);

  Serial.write(data, sizeof(data)-1);
}

void loop(){
  delay(1000);
  Serial.print(sizeof(data));
  Serial.println(data);
}