#define MQ135_PIN 34
#define RZERO 76.63 // Calibrated RZERO value for MQ135 (in clean air, typically 76.63)

float resistance;
float ppm;

void setup() {
  Serial.begin(115200);
  pinMode(MQ135_PIN, INPUT);
}

void loop() {
  int sensorValue = analogRead(MQ135_PIN);
  resistance = calculateResistance(sensorValue);
  ppm = getCO2Concentration(resistance);
  
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  Serial.print(" | Resistance: ");
  Serial.print(resistance);
  Serial.print(" kOhms | CO2 Concentration: ");
  Serial.print(ppm);
  Serial.println(" ppm");
  
  delay(1000); // 1 second delay
}

float calculateResistance(int raw_adc) {
  float loadResistance = 10.0; // Load resistance in kOhms
  float sensorVoltage = raw_adc * (3.3 / 4095.0); // Convert ADC value to voltage
  float sensorResistance = (3.3 - sensorVoltage) / sensorVoltage * loadResistance; // Calculate sensor resistance
  return sensorResistance;
}

float getCO2Concentration(float resistance) {
  float ratio = resistance / RZERO; // Calculate ratio
  float ppm = 116.6020682 * pow(ratio, -2.769034857); // Calculate CO2 concentration
  return ppm;
}