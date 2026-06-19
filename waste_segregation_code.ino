Programming code: 
const int rainSensorPin = A0; // Rain sensor analog pin
const int rainThreshold = 900; // Adjust according to your sensor readings
const int trigPin = 6; // Ultrasonic Trigger
const int echoPin = 5; // Ultrasonic Echo
const int metalSensorPin = 4; // Metal proximity sensor (digital)
const int greenLedPin = 3; // Green LED
const int irSensorPin = 4; // IR sensor digital pin
int rainValue;
int metal = 0; // flag for metal detection
void setup()
{
 Serial.begin(9600);
 servo1.attach(10); // Servo 1 on pin 10
 servo2.attach(11); // Servo 2 on pin 11
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(metalSensorPin, INPUT);
 pinMode(greenLedPin, OUTPUT);
 pinMode(irSensorPin, INPUT);
 // Initial positions
 servo1.write(90);
 servo2.write(90);
}
// === Loop ===
void loop()
{
 // --- Rain Sensor ---
 rainValue = analogRead(rainSensorPin);
 Serial.print("Rain Value: ");
 Serial.println(rainValue);
 int irState = digitalRead(irSensorPin);
 int metalDetected = digitalRead(metalSensorPin);
if (rainValue < rainThreshold)
 {
 Serial.println("Wet detected...");
 smoothMove(servo1, 90, 0, 15);
 delay(500);
 smoothMove(servo1, 0, 90, 15);
 }
 if (metalDetected == LOW)
 {
 metal = 1;
 Serial.println("METAL DETECTED...");
 smoothMove(servo1, 90, 180, 15);
 delay(500);
 smoothMove(servo1, 180, 90, 15);
 }
 if (irState == LOW)
 {
 Serial.println("DOOR OPENED.....");
 smoothMove(servo2, 90, 0, 15);
 delay(500);
 smoothMove(servo2, 0, 90, 15);
 }
 else
 {
 servo1.write(90);
 servo2.write(90);
 digitalWrite(greenLedPin, LOW);
 Serial.println("IR HIGH - System Stopped");
 metal = 0;
 }
 long distance = getDistance();
 Serial.print("Distance: ");
 Serial.println(distance);
 if (distance < 5) {
 digitalWrite(greenLedPin, HIGH);
 } else {
 digitalWrite(greenLedPin, LOW);
 }
delay(500);

}

long getDistance()

{

 digitalWrite(trigPin, LOW);

 delayMicroseconds(2);

 digitalWrite(trigPin, HIGH);

 delayMicroseconds(10);

 digitalWrite(trigPin, LOW);

 long duration = pulseIn(echoPin, HIGH);

 long distance = duration * 0.034 / 2; // Convert to cm

 return distance;

}

void smoothMove(Servo &servo, int fromAngle, int toAngle, int stepDelay)

{

 if (fromAngle < toAngle)

 {

 for (int pos = fromAngle; pos <= toAngle; pos++)

 {

 servo.write(pos);

 delay(stepDelay);

 }

 }

 else

 {

 for (int pos = fromAngle; pos >= toAngle; pos--)

 {

 servo.write(pos);

 delay(stepDelay);

 }

 }

}
