// void setup(){
//   Serial.begin(115200);
//   Serial1.begin(115200, SERIAL_8N1, 16, 17);
// }

// void loop(){
  
//   while(Serial1.available()>0){
//     String incomingData = Serial1.readStringUntil('\n');
//     Serial.println(incomingData);
//     delay(1000);
//   }

// }
char incomingData[100];
int indexVar = 0;

void setup(){
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, 16, 17);
}

void loop(){  
  while(Serial1.available()>0){
    char incomingByte = Serial1.read();

    if(incomingByte == '\n'){
      incomingData[indexVar] = '\0';
      Serial.println(incomingData);
      indexVar = 0;
    } else {
      if(indexVar < sizeof(incomingData)-1){
        incomingData[indexVar++] = incomingByte;
      }
    }
  }
  delay(100);
}

