// event.cpp
#include "event.h"

using time_point = std::chrono::system_clock::time_point;

Event::Event(const EventInfo &info) noexcept
    : info_(info) {}

const std::string &Event::get_title() const noexcept { return info_.title_; }
const time_point &Event::get_time() const noexcept { return info_.time_; }