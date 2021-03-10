#include <Arduino.h>

unsigned long checkDelay = 5000;
unsigned long cycleLength = 3600000; // 1 hour between checks
// unsigned long cycleLength = 5000; // 5 secs between checks

int waterDuration = 5000; // water for X seconds

int commonThresh = 540;
int percentThresh = 50;

struct Plant
{
    const char *name;
    int relay;
    int sensor;
    int airValue;
    int waterValue;
    int threshold;
    int liveRead;
}; /*black, green, yellow, red;*/

Plant black = {
    "Black", //name
    2,       // relay pin
    1,       // sensor pin
    572,     // air reading
    282      // water reading
};

Plant green = {
    "Green", //name
    3,       // relay pin
    2,       // sensor pin
    575,     // air reading
    273      // water reading
};

Plant yellow = {
    "Yellow", //name
    4,        // relay pin
    3,        // sensor pin
    554,      // air reading
    266       // water reading
};

Plant red = {
    "Red", //name
    5,     // relay pin
    4,     // sensor pin
    573,   // air reading
    269    // water reading
};

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
    // set up structs for each plant

    pinMode(black.relay, OUTPUT);
    pinMode(green.relay, OUTPUT);
    pinMode(yellow.relay, OUTPUT);
    pinMode(red.relay, OUTPUT);

    pinMode(black.sensor, INPUT);
    pinMode(green.sensor, INPUT);
    pinMode(yellow.sensor, INPUT);
    pinMode(red.sensor, INPUT);

    digitalWrite(black.relay, HIGH);
    digitalWrite(green.relay, HIGH);
    digitalWrite(yellow.relay, HIGH);
    digitalWrite(red.relay, HIGH);
    delay(500);
}

int convertPercent(int value, int min, int max)
{
    int moisturePercent = 0;
    moisturePercent = map(value, max, min, 0, 100);
    return moisturePercent;
}

void plantCheck(Plant plant)
{
    unsigned long currentMillis = millis();
    plant.liveRead = analogRead(plant.sensor);
    int readingPercent =
        convertPercent(plant.liveRead, plant.airValue, plant.waterValue);
    Serial.print("MOISTURE LEVEL ");
    Serial.print(plant.name);

    Serial.print(": ");
    Serial.print(readingPercent);
    Serial.print("%, raw: ");
    Serial.println(plant.liveRead);
    if ((currentMillis - plant1Millis) >= cycleLength)
    {
        if (readingPercent < percentThresh)
        {
            while (millis() <=
                   (currentMillis +
                    waterDuration))
            { // turn on the water for 20 secs
                digitalWrite(plant.relay, LOW);
            }
            digitalWrite(plant.relay, HIGH);
        }
        else
        {
            digitalWrite(plant.relay, HIGH);
        }

        Serial.println();
        plant1Millis = currentMillis;
    }
}

void loop()
{
    // non-blocking delay loop
    if (((millis() - lastCheck) >= checkDelay) ||
        (lastCheck == 0)) // if delay has passed OR this is the first pass
    {                     // through the loop
        plantCheck(black);
        plantCheck(green);
        plantCheck(yellow);
        plantCheck(red);

        Serial.println("###########");
        lastCheck = millis();
    }
    // end of loop
}
