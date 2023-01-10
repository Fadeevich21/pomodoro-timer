#pragma once

#include <stdint.h>

class Time {
private:
    uint8_t hour;
    uint8_t minute;
    uint8_t second;

    void increment_second();
    void increment_minute();
    void increment_hour();

    void decrement_second();
    void decrement_minute();
    void decrement_hour();

public:
    Time();
    Time(const uint8_t hour, const uint8_t minute,
         const uint8_t second);
    
    void set_time(const uint8_t hour, const uint8_t minute,
                  const uint8_t second);

    Time operator++(int);
    Time& operator++();

    Time operator--(int);
    Time& operator--();

    char* get_time_str() const;
};