#include <Arduino.h>

int waterDuration = 20000; // water for X seconds
int sens1thresh = 550;
int sens2thresh = 550;
int sens3thresh = 550;
int sens4thresh = 550;

int relay1 = 2;
int relay2 = 3;
int relay3 = 4;
int relay4 = 5;

int h2oSensor1 = A0;
int h2oSensor2 = A1;
int h2oSensor3 = A2;
int h2oSensor4 = A3;

float h2oSensorReading1 = 0;
float h2oSensorReading2 = 0;
float h2oSensorReading3 = 0;
float h2oSensorReading4 = 0;

// unsigned long cycleLength = 3600000;  // 1 hour between checks
unsigned long cycleLength = 10000; // 10 secs between checks
unsigned long cycleCount = 0;

unsigned long plant1Millis = 0;
unsigned long plant2Millis = 0;
unsigned long plant3Millis = 0;
unsigned long plant4Millis = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(relay1, OUTPUT);
    pinMode(relay2, OUTPUT);
    pinMode(relay3, OUTPUT);
    pinMode(relay4, OUTPUT);

    pinMode(h2oSensor1, INPUT);
    pinMode(h2oSensor2, INPUT);
    pinMode(h2oSensor3, INPUT);
    pinMode(h2oSensor4, INPUT);

    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
    digitalWrite(relay3, HIGH);
    digitalWrite(relay4, HIGH);
    delay(500);
}
// int h2oSensor;

// plantCheck(h2oSensor) {
//     unsigned long currentMillis = millis();
//     if ((currentMillis - plant1Millis) >= cycleLength) {
//         int h2oSensorReading = analogRead(h2oSensor1);
//         Serial.print("MOISTURE LEVEL 1:");
//         Serial.println(h2oSensorReading1);
//         if (h2oSensorReading1 > 550) {
//             while (millis() <=
//                    (currentMillis + 20000)) {  // turn on the water for 20 secs
//                 digitalWrite(relay1, LOW);
//             }
//             digitalWrite(relay1, HIGH);
//         } else {
//             digitalWrite(relay1, HIGH);
//         }

//         Serial.println();
//         plant1Millis = currentMillis;
//     }
// }

void plantCheck1()
{
    unsigned long currentMillis = millis();
    if ((currentMillis - plant1Millis) >= cycleLength)
    {
        h2oSensorReading1 = analogRead(h2oSensor1);
        Serial.print("MOISTURE LEVEL 1:");
        Serial.println(h2oSensorReading1);
        if (h2oSensorReading1 > sens1thresh)
        {
            while (millis() <=
                   (currentMillis + waterDuration))
            { // turn on the water for 20 secs
                digitalWrite(relay1, LOW);
            }
            digitalWrite(relay1, HIGH);
        }
        else
        {
            digitalWrite(relay1, HIGH);
        }

        Serial.println();
        plant1Millis = currentMillis;
    }
}

void plantCheck2()
{
    unsigned long currentMillis = millis();
    if ((currentMillis - plant2Millis) >= cycleLength)
    {
        h2oSensorReading2 = analogRead(h2oSensor2);
        Serial.print("MOISTURE LEVEL 2:");
        Serial.println(h2oSensorReading2);
        if (h2oSensorReading2 > sens2thresh)
        {
            while (millis() <=
                   (currentMillis + waterDuration))
            { // turn on the water for 20 secs
                digitalWrite(relay2, LOW);
            }
            digitalWrite(relay2, HIGH);
        }
        else
        {
            digitalWrite(relay2, HIGH);
        }
        Serial.println();
        plant2Millis = currentMillis;
    }
}

void plantCheck3()
{
    unsigned long currentMillis = millis();
    if ((currentMillis - plant3Millis) >= cycleLength)
    {
        h2oSensorReading3 = analogRead(h2oSensor3);
        Serial.print("MOISTURE LEVEL 3:");
        Serial.println(h2oSensorReading3);
        if (h2oSensorReading3 > sens3thresh)
        {
            while (millis() <=
                   (currentMillis + waterDuration))
            { // turn on the water for 20 secs
                digitalWrite(relay3, LOW);
            }
            digitalWrite(relay3, HIGH);
        }
        else
        {
            digitalWrite(relay3, HIGH);
        }
        Serial.println();
        plant3Millis = currentMillis;
    }
}

void plantCheck4()
{
    unsigned long currentMillis = millis();
    if ((currentMillis - plant4Millis) >= cycleLength)
    {
        h2oSensorReading4 = analogRead(h2oSensor4);
        Serial.print("MOISTURE LEVEL 4:");
        Serial.println(h2oSensorReading4);
        if (h2oSensorReading4 > sens4thresh)
        {
            while (millis() <=
                   (currentMillis + waterDuration))
            { // turn on the water for 20 secs
                digitalWrite(relay4, LOW);
            }
            digitalWrite(relay4, HIGH);
        }
        else
        {
            digitalWrite(relay4, HIGH);
        }
        Serial.println();
        plant4Millis = currentMillis;
    }
}

void loop()
{
    plantCheck1();
    plantCheck2();
    plantCheck3();
    plantCheck4();
    Serial.println("###########");
}

//////////////////////////
// Simple code for Measuring Voltage from
// Capacitive soil moisture sensor

// int soil_pin = A0; // AOUT pin on sensor

// void setup() {
//   Serial.begin(9600); // serial port setup
//   analogReference(EXTERNAL); // set the analog reference to 3.3V
// }

// void loop() {
//   Serial.print("Soil Moisture Sensor Voltage: ");
//   Serial.print((float(analogRead(soil_pin))/1023.0)*3.3); // read sensor
//   Serial.println(" V");
//   delay(100); // slight delay between readings
// }