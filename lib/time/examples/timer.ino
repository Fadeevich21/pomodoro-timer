#include <Arduino.h>
#include "time.hpp"

#define DELAY_PRINT_TIME 1000
#define SERIAL_SPEED 9600

Time time;

void time_setup() {
    time.set_time(0, 1, 0);
}

void setup() {
    Serial.begin(SERIAL_SPEED);
    time_setup();
}

void print_time() {
    char* time_str = time.get_time_str();
    Serial.println(time_str);
}

void loop() {
    static bool timer_is_running = true;
    static uint64_t milliseconds = millis();
    if (timer_is_running && millis() - milliseconds > DELAY_PRINT_TIME) {
        milliseconds = millis();
        if (time != "00:00:00") {
            --time;
            print_time();
        } else {
            Serial.println("Time is up!");
            timer_is_running = false;
        }
    }
}