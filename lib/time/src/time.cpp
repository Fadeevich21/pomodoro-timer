#include "time.hpp"

#define NUMBER_SECONDS_IN_MINUTE 60
#define NUMBER_MINUTES_IN_HOUR 60
#define NUMBER_HOURS_IN_DAY 24

void Time::increment_second() {
    if (this->second + 1 == NUMBER_SECONDS_IN_MINUTE) {
        this->increment_minute();
    }
    this->second = (this->second + 1) % NUMBER_SECONDS_IN_MINUTE;
}

void Time::increment_minute() {
    if (this->minute + 1 == NUMBER_MINUTES_IN_HOUR) {
        this->increment_hour();
    }
    this->minute = (this->minute + 1) % NUMBER_MINUTES_IN_HOUR;
}

void Time::increment_hour() {
    this->hour = (this->hour + 1) % NUMBER_HOURS_IN_DAY;
}

void Time::decrement_second() {
    if (this->second == 0) {
        this->decrement_minute();
        this->second = NUMBER_SECONDS_IN_MINUTE;
    }

    --this->second;
}

void Time::decrement_minute() {
    if (this->minute == 0) {
        this->decrement_hour();
        this->minute = NUMBER_MINUTES_IN_HOUR;
    }

    --this->minute;
}

void Time::decrement_hour() {
    if (this->hour == 0) {
        this->hour = NUMBER_HOURS_IN_DAY;
    }

    --this->hour;
}

Time::Time()
    : Time(0, 0, 0) {
}

Time::Time(const uint8_t hour, const uint8_t minute,
           const uint8_t second) {
    set_time(hour, minute, second);
}

void Time::set_time(const uint8_t hour, const uint8_t minute,
                    const uint8_t second) {
    this->hour = hour;
    this->minute = minute;
    this->second = second;
}

Time& Time::operator++() {
    this->increment_second();
    
    return *this;
}

Time Time::operator++(int) {
    Time tmp = *this;
    ++tmp;

    return tmp;
}

Time& Time::operator--() {
    this->decrement_second();
    
    return *this;
}

Time Time::operator--(int) {
    Time tmp = *this;
    --tmp;

    return tmp;
}

char *Time::get_time_str() const {
    static char time_str[9];

    time_str[0] = this->hour / 10 + '0';
    time_str[1] = this->hour % 10 + '0';

    time_str[2] = ':';

    time_str[3] = this->minute / 10 + '0';
    time_str[4] = this->minute % 10 + '0';

    time_str[5] = ':';

    time_str[6] = this->second / 10 + '0';
    time_str[7] = this->second % 10 + '0';

    time_str[8] = '\0';

    return time_str;
}
