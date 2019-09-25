

const int sensorPin = A0;  /* Connect Soil moisture analog sensor pin to A0 of NodeMCU */
float liquid_level;
int liquid_percentage;
int top_level = 512;
int bottom_level = 3;


void setup() {
  Serial.begin(115200); /* Define baud rate for serial communication */
}

void loop() {
  liquid_level = analogRead(sensorPin);
  liquid_percentage = ((liquid_level-bottom_level)/top_level)*100;
  Serial.println(liquid_level);
  Serial.print("%");
  delay(5000);
}
