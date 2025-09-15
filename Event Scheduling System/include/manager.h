#pragma once
// manager.h
#include <unordered_map>
#include "helpers.h"
#include "event.h"
#include <set>

constexpr  size_t EXPECTED_EVENTS = 20;

class Manager
{
public:
    using time_point = std::chrono::system_clock::time_point;
    using event_ptr = std::shared_ptr<Event>;

public:
    Manager() noexcept;

    void add_event(const std::string &title, const time_point &tp) noexcept;

private:
    std::set<event_ptr, Compare> sorted_events_;
    std::unordered_map<std::string, event_ptr> events_;
};