#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "time.hpp"

#define DELAY_PRINT_TIME 1000
#define TIME_ONE_CYCLES_WORK_POMODORO "00:00:10"
#define TIME_ONE_CYCLES_SHORT_PAUSE_POMODORO "00:00:05"
#define TIME_ONE_CYCLES_LONG_PAUSE_POMODORO "00:00:07"

#define SSD1306_ADDRESS 0x3C
#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64

using SSD1306 = Adafruit_SSD1306;

SSD1306 display(SSD1306_WIDTH, SSD1306_HEIGHT);
Time time;

void time_setup_one_cycle_work_pomodoro() {
    time.set_time(TIME_ONE_CYCLES_WORK_POMODORO);
}

void time_setup_one_cycle_short_pause_pomodoro() {
    time.set_time(TIME_ONE_CYCLES_SHORT_PAUSE_POMODORO);
}

void time_setup_one_cycle_long_pause_pomodoro() {
    time.set_time(TIME_ONE_CYCLES_LONG_PAUSE_POMODORO);
}

void display_setup() {
    display.begin(SSD1306_SWITCHCAPVCC, SSD1306_ADDRESS);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
}

void setup() {
    pinMode(13, OUTPUT);
    display_setup();
}

void print_time() {
    char* time_str = time.get_time_str();
    display.clearDisplay();
    display.setCursor(15, 0);
    display.print(time_str);
    display.display();
}

void loop() {
    static uint8_t count_working_cycles_pomodoro = 0;
    static bool is_working = false;
    static uint64_t milliseconds = millis();
    if (millis() - milliseconds > DELAY_PRINT_TIME) {
        milliseconds = millis();
        print_time();
        if (time != "00:00:00") {
            --time;
            if (!is_working) {
                display.setCursor(4, 32);
                display.print("Time is up");
                display.display();
            }
        } else {
            if (is_working) {
                if (count_working_cycles_pomodoro < 3) {
                    time_setup_one_cycle_short_pause_pomodoro();
                } else {
                    time_setup_one_cycle_long_pause_pomodoro();
                }
                count_working_cycles_pomodoro = (count_working_cycles_pomodoro + 1) % 4;
            } else {
                time_setup_one_cycle_work_pomodoro();
            }

            is_working = !is_working;
            digitalWrite(13, is_working);
        }
    }
}