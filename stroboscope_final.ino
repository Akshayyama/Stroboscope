int light = 1;      // LIGHTS ON delay, microseconds
int dark;             // LIGHTS OFF delay
int min_dark = 5;     // min dark delay
int max_dark = 25;    // max dark delay
#define light_pin 12  // MOSFET pin
#define  potent_pin A6 // potentiometer pin
int angle;
boolean flag;
long lastchange;

#include "Arduino_BMI270_BMM150.h" 
#include "kalman.h"
Kalman kalmanX;
Kalman kalmanZ;
/* IMU Data */
float accX;
float accY;
float accZ;
int16_t tempRaw;
float gyroX;
float gyroY;
float gyroZ;
double accXangle; // Angle calculate using the accelerometer
double accZangle;
double temp;
double gyroXangle = 180; // Angle calculate using the gyro
double gyroZangle = 180;
double compAngleX = 180; // Calculate the angle using a Kalman filter
double compAngleZ = 180;
double kalAngleX; // Calculate the angle using a Kalman filter
double kalAngleZ;
uint32_t timer;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(light_pin, OUTPUT);
  kalmanX.setAngle(180); // Set starting angle
  kalmanZ.setAngle(180);
  timer = micros();
  while (!Serial);
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
}

void loop() {
  measure();                                            // obtain acceleration and angle speeds
  // if (accZ > 25000 && (millis() - lastchange > 300)) {  // Z axis shake detection
  //   flag = !flag;                                       // toggle light
  //   lastchange = millis();                              // timer
  // }

  // if (flag == 1) {
    angle = 250 - kalAngleZ;   // calculate angle (with 250 degrees offset)
    Serial.println(angle);
    // dark times calculation
    dark = map(analogRead(potent_pin), 0, 1024, min_dark, max_dark);
    digitalWrite(light_pin, 1);    // lights up
    delay(light);      // wait
    digitalWrite(light_pin, 0);    // lights down
    delay(dark);                   // wait
    delay(10 + angle*0.05); // extra wait
  //}
}

// oh my god, it's some tricky sh*t
void measure() {
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(accX, accY, accZ);

    // Serial.print(accX);
    // Serial.print('\t');
    // Serial.print(accY);
    // Serial.print('\t');
    // Serial.print(accZ);
    // Serial.print('\t');
  }

  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(gyroX, gyroY, gyroZ);

    // Serial.print(gyroX);
    // Serial.print('\t');
    // Serial.print(gyroY);
    // Serial.print('\t');
    // Serial.print(gyroZ);
    // Serial.println();
  }

  /* Calculate the angls based on the different sensors and algorithm */
  accZangle = (atan2(accX, accY) + PI) * RAD_TO_DEG;
  accXangle = (atan2(accY, accX) + PI) * RAD_TO_DEG;
  double gyroXrate = (double)gyroX / 131.0;
  double gyroZrate = -((double)gyroZ / 131.0);
  gyroXangle += kalmanX.getRate() * ((double)(micros() - timer) / 1000000); // Calculate gyro angle using the unbiased rate
  gyroZangle += kalmanZ.getRate() * ((double)(micros() - timer) / 1000000);
  kalAngleX = kalmanX.getAngle(accXangle, gyroXrate, (double)(micros() - timer) / 1000000); // Calculate the angle using a Kalman filter
  kalAngleZ = kalmanZ.getAngle(accZangle, gyroZrate, (double)(micros() - timer) / 1000000);
  timer = micros();

}