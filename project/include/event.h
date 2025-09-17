#pragma once
// event.h
#include "utils.h"
#include <chrono>

struct EventInfo
{
    using system_clock = std::chrono::system_clock;

    std::string title_;
    std::string location_;
    std::string group_name_;
    std::string description_;
    system_clock::time_point time_;
};

class Event
{
public:
    using time_point = std::chrono::system_clock::time_point;

public:
    Event(const EventInfo &info) noexcept;

    const std::string &get_title() const noexcept;
    const time_point &get_time() const noexcept;
    const std::string &get_group_name() const noexcept;

private:
    EventInfo info_;
};
