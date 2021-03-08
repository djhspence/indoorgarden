#include <Arduino.h>

///////////////////////////////////////////////
///////////////////////////////////////////////

unsigned long checkDelay = 5000;
unsigned long cycleLength = 3600000; // 1 hour between checks
//unsigned long cycleLength = 5000; // 5 secs between checks

int waterDuration = 5000; // water for X seconds

int commonThresh = 540;
int percentThresh = 50;

struct MoistureSensor {
    int relay;
    int sensor;
    int airValue;
    int waterValue;
    int threshold;
    int liveRead;
} black, green, yellow, red;


// Black

int sens1thresh = commonThresh;
int relay1 = 2;
int h2oSensor1 = A1;
int airValue1 = 572;
int waterValue1 = 282;

// Green
int sens2thresh = commonThresh;
int relay2 = 3;
int h2oSensor2 = A2;
int airValue2 = 575;
int waterValue2 = 273;

// Yellow
int sens3thresh = commonThresh;
int relay3 = 4;
int h2oSensor3 = A3;
int airValue3 = 554;
int waterValue3 = 266;

// Red
int sens4thresh = 580;
int relay4 = 5;
int h2oSensor4 = A4;
int airValue4 = 573;
int waterValue4 = 269;

///////////////////////////////////////////////
///////////////////////////////////////////////

float h2oSensorReading1 = 0;
float h2oSensorReading2 = 0;
float h2oSensorReading3 = 0;
float h2oSensorReading4 = 0;

unsigned long cycleCount = 0;
unsigned long lastCheck = 0; // set with millis() at the end of each loop

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

// set up structs for each plant
    black= {2,1,572,282};
    green = {3, 2, 575, 273};
    yellow = {4, 3, 554, 266};
    red = {5, 4, 573, 269};
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
//                    (currentMillis + 20000)) {  // turn on the water for 20
//                    secs
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

int convertPercent (int value, int min, int max) {
    int moisturePercent = 0;
    moisturePercent = map(value, min, max, 0, 100);
    return moisturePercent;
}

void plantCheck1(plant)
{
    unsigned long currentMillis = millis();
    h2oSensorReading1 = analogRead(h2oSensor1);
    int readingPercent = convertPercent(MoistureSensor.liveRead, .airValue, .waterValue);
    Serial.print("MOISTURE LEVEL 1 (BLACK):");
    Serial.println(readingPercent);
    if ((currentMillis - plant1Millis) >= cycleLength)
    {

        if (readingPercent < percentThresh)
        {
            while (millis() <=
                   (currentMillis +
                    waterDuration))
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
    h2oSensorReading2 = analogRead(h2oSensor2);
    Serial.print("MOISTURE LEVEL 2 (GREEN):");
    Serial.println(h2oSensorReading2);
    if ((currentMillis - plant2Millis) >= cycleLength)
    {

        if (h2oSensorReading2 > sens2thresh)
        {
            while (millis() <=
                   (currentMillis +
                    waterDuration))
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
    h2oSensorReading3 = analogRead(h2oSensor3);
    Serial.print("MOISTURE LEVEL 3 (YELLOW):");
    Serial.println(h2oSensorReading3);
    if ((currentMillis - plant3Millis) >= cycleLength)
    {

        if (h2oSensorReading3 > sens3thresh)
        {
            while (millis() <=
                   (currentMillis +
                    waterDuration))
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
    h2oSensorReading4 = analogRead(h2oSensor4);
    Serial.print("MOISTURE LEVEL 4 (RED):");
    Serial.println(h2oSensorReading4);
    if ((currentMillis - plant4Millis) >= cycleLength)
    {

        if (h2oSensorReading4 > sens4thresh)
        {
            while (millis() <=
                   (currentMillis +
                    waterDuration))
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
    //non-blocking delay loop
    if (((millis() - lastCheck) >= checkDelay) || (lastCheck = 0)) // if delay has passed OR this is the first pass through the loop
    {
        plantCheck1();
        plantCheck2();
        plantCheck3();
        plantCheck4();
        Serial.println("###########");
        lastCheck = millis();
    }
    // end of loop
}
