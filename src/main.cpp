#include <Arduino.h>

unsigned long checkDelay = 5000; // time between main loops, non-blocking
//unsigned long cycleLength = 3600000; // 1 hour before next potential watering event
unsigned long cycleLength = 30000; // 30 secs between checks

int waterDuration = 2000; // water for X seconds

int percentThresh = 50; // % under which waterig is triggered

struct Plant
{
    const char *name;
    int relay;
    int sensor;
    int airValue;
    int waterValue;
    int liveRead;
    unsigned long plantMillis;
};

Plant black = {
    "Black", //name
    2,       // relay pin
    1,       // sensor pin
    572,     // air reading
    282,     // water reading
    0,       // live reading
    0        // plant milli counter
};

Plant green = {
    "Green", //name
    3,       // relay pin
    2,       // sensor pin
    575,     // air reading
    273,     // water reading
    0,       // live reading
    0};      // plant milli counter

Plant yellow = {
    "Yellow", //name
    4,        // relay pin
    3,        // sensor pin
    554,      // air reading
    266,      // water reading
    0,        // live reading
    0};       // plant milli counter

Plant red = {
    "Red", //name
    5,     // relay pin
    4,     // sensor pin
    573,   // air reading
    269,   // water reading
    0,     // live reading
    0};    // plant milli counter

///////////////////////////////////////////////
///////////////////////////////////////////////

unsigned long lastCheck = 0; // set with millis() at the end of each loop

//unsigned long plantMillis = 0;

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

    // digitalWrite(black.relay, HIGH);
    // digitalWrite(green.relay, HIGH);
    // digitalWrite(yellow.relay, HIGH);
    // digitalWrite(red.relay, HIGH);
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
    if (((currentMillis - plant.plantMillis) >= cycleLength) || lastCheck == 0)
    {

        if (readingPercent < percentThresh)
        {

            if (millis() <= (currentMillis + waterDuration))
            { // turn on the water
                //Serial.println("p");
                Serial.print("Water on relay ");
                Serial.println(plant.relay);
                digitalWrite(plant.relay, HIGH);
            }
            digitalWrite(plant.relay, LOW);
            Serial.println("water off");
        }
        //else
        //{
        digitalWrite(plant.relay, LOW);
        //Serial.println("do nothing");
        //}

        Serial.println();
        plant.plantMillis = currentMillis;
        Serial.print("Black relay state: ");
        Serial.println(digitalRead(black.relay));
        Serial.print("Green relay state: ");
        Serial.println(digitalRead(green.relay));
        Serial.print("Yellow relay state: ");
        Serial.println(digitalRead(yellow.relay));
        Serial.print("Red relay state: ");
        Serial.println(digitalRead(red.relay));
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
        digitalWrite(black.relay, HIGH);
        digitalWrite(green.relay, HIGH);
        digitalWrite(yellow.relay, HIGH);
        digitalWrite(red.relay, HIGH);
        Serial.println("###########");
        lastCheck = millis();
    }
    // end of loop
}
