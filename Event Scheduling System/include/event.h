#pragma once
// event.h
#include <iostream>
#include <chrono>

class Event
{
public:
    using time_point = std::chrono::system_clock::time_point;

public:
    Event(const std::string &title, const time_point &tp) noexcept
        : title_(title), event_time_(tp) {}

    const std::string &get_title() const noexcept { return title_; }
    const time_point &get_time() const noexcept { return event_time_; }

private:
    std::string title_;
    time_point event_time_;
};
