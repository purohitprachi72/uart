void setup(){
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, 16, 17);
}

void loop(){
  
  while(Serial1.available()>0){
    incomingData = Serial1.readStringUntil('\n');
    // Serial.println(incomingData);
    delay(100);
    char charArray[incomingData.length()+1];
    incomingData.toCharArray(charArray, incomingData.length()+1);
    Serial.println(charArray);
  }

}
