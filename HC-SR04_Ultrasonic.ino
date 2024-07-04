#define TRIG_PIN 5
#define ECHO_PIN 18

void setup() {
  Serial.begin(115200);
  
  // Initialize the trigger pin as an output
  pinMode(TRIG_PIN, OUTPUT);
  
  // Initialize the echo pin as an input
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // Send a pulse to the trigger pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Read the time for the pulse to return
  long duration = pulseIn(ECHO_PIN, HIGH);
  
  // Calculate the distance in millimeters
  long distance_mm = (duration * 0.343) / 2;
  
  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance_mm);
  Serial.println(" mm");
  
  delay(1000); // 1 second delay between readings
}