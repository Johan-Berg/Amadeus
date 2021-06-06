int sensorValue;
void setup() {
 Serial.begin(9600);
}

void loop() {
 // read the input on analog pin 0:
 int sValue = analogRead(A1);

 //Serial.println(sValue);
 
 //change the number to be between 0 and 255
 sensorValue = map(sValue, 0, 255, 0, 255);
 
 // print out the value you mapped:
 Serial.write(sensorValue);
 
 delay(100); // delay in between reads for stability
}
