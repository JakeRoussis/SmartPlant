/*
 * SmartPlant v0.1
 * 
 * Checks plant soil moisture and alerts user when they need to water it.
 * 
 * Checks soil moisture level against a pre-determined 'suitable' value that was tested
 * and take this value to test it against the current soil condition. This is then
 * passed through an if statement that changes the colour of the LED for the situation.
 * 
 * RED - Plant requires watering
 * BLUE - Plant has just been watered/has too much moisture
 * Green - Plant is at ideal range
 * 
 * Created 6/08/2018 
 * by Jake Roussis
 * 
 * Current 'waterMe' values are only test values in order to determine
 * LED functionality and set-up. Correct values will be in v1.0
 * 
 */

int val = 0; //Store moisture value
int soilPin = A0; //Variable for sensor
int soilPower = 7; //Variable for sensor power
int waterMe = 450; //Minimum level for when the plant needs water

int redPin = 11; //RGB Red pin
int greenPin = 10; //RGB green pin
int bluePin = 9; //RGB blue pin

void setup() {
  Serial.begin(9600); //Open serial over USB
  pinMode(soilPower, OUTPUT); //Initialize
  digitalWrite(soilPower, LOW); // Set to low so no power is flowing through sensor

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

}

int readSoil() {
  digitalWrite(soilPower, HIGH); //Turn sensor ON
  delay(10); //Wait 10ms
  val = analogRead(soilPin); //Read the value from sensor
  digitalWrite(soilPin, LOW); //Turn sensor off
  return val; //Send moisture value
}

void setColour(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

void loop() {
  Serial.print("Soil Moisture = ");
  Serial.println(readSoil());
  delay(1000); // Take a reading every once every second

  if (readSoil() < waterMe) {
    setColour(2550, 0, 0); //Requires watering
  } else if (readSoil() > 850) {
    setColour(0, 0, 255); //A lot of water detected
  } else {
    setColour(0, 255, 0); //Perfect range of water
  }
}

