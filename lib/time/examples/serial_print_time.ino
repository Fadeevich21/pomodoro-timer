#include <Arduino.h>
#include "time.hpp"

#define DELAY_PRINT_TIME 1000
#define SERIAL_SPEED 9600

Time time;

void setup() {
    Serial.begin(SERIAL_SPEED);
}

void print_time() {
    char* time_str = time.get_time_str();
    Serial.println(time_str);
}

void loop() {
    static uint64_t milliseconds = millis();
    if (millis() - milliseconds > DELAY_PRINT_TIME) {
        milliseconds = millis();
        ++time;
        print_time();
    }
}