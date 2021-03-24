#include <Arduino.h>

//const unsigned long checkDelay = 5000;  // time between main loops, non-blocking
const unsigned long checkDelay = 1800000; // 1/2 hour before next potential

const int waterDuration = 5000; // water for X seconds

const int percentThresh = 50; // % under which waterig is triggered

struct Plant
{
    const char *name;
    const int relay;
    const int sensor;
    const int airValue;
    const int waterValue;
    int liveRead;
};

Plant black = {
    "Black", // name
    8,       // relay pin
    1,       // sensor pin
    572,     // air reading
    282,     // water reading
    0        // live reading
};

Plant green = {
    "Green", // name
    9,       // relay pin
    2,       // sensor pin
    575,     // air reading
    273,     // water reading
    0        // live reading
};

Plant yellow = {
    "Yellow", // name
    10,       // relay pin
    3,        // sensor pin
    554,      // air reading
    266,      // water reading
    0         // live reading
};

Plant red = {
    "Red", // name
    11,    // relay pin
    4,     // sensor pin
    573,   // air reading
    269,   // water reading
    0      // live reading
};

///////////////////////////////////////////////
///////////////////////////////////////////////

unsigned long lastCheck = 0; // set with millis() at the end of each loop

void setup()
{
    Serial.begin(9600);
    // set up structs for each plant
    digitalWrite(black.relay, HIGH);
    digitalWrite(green.relay, HIGH);
    digitalWrite(yellow.relay, HIGH);
    digitalWrite(red.relay, HIGH);

    pinMode(black.relay, OUTPUT);
    pinMode(green.relay, OUTPUT);
    pinMode(yellow.relay, OUTPUT);
    pinMode(red.relay, OUTPUT);

    pinMode(black.sensor, INPUT);
    pinMode(green.sensor, INPUT);
    pinMode(yellow.sensor, INPUT);
    pinMode(red.sensor, INPUT);

    // just in case do it again
    digitalWrite(black.relay, HIGH);
    digitalWrite(green.relay, HIGH);
    digitalWrite(yellow.relay, HIGH);
    digitalWrite(red.relay, HIGH);

    delay(500);
}

int convertPercent(int value, int min, int max)
{
    int moisturePercent = 0;
    moisturePercent = map(value, min, max, 0, 100);
    return moisturePercent;
}

void plantCheck(Plant plant)
{

    plant.liveRead = analogRead(plant.sensor);

    int readingPercent =
        convertPercent(plant.liveRead, plant.airValue, plant.waterValue);

    Serial.print("MOISTURE LEVEL ");
    Serial.print(plant.name);
    Serial.print(": ");
    Serial.print(readingPercent);
    Serial.print("%, raw: ");
    Serial.println(plant.liveRead);
    // if (((currentMillis - plant.plantMillis) >= cycleLength) ||

    if (readingPercent < percentThresh)
    {
        Serial.print("Water on relay ");
        Serial.println(plant.relay);
        digitalWrite(plant.relay, LOW);
        delay(waterDuration);
        digitalWrite(plant.relay, HIGH);
        Serial.println("water off");
    }
    else
    {
        digitalWrite(plant.relay, HIGH);
        Serial.println("do nothing");
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
