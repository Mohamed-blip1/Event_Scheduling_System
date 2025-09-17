#pragma once
// manager.h
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include "helpers.h"
#include "event.h"
#include <vector>
#include <set>

constexpr size_t EXPECTED_EVENTS = 30;
constexpr unsigned short ZERO = 0;

class Manager
{
public:
    using time_point = std::chrono::system_clock::time_point;
    using system_clock = std::chrono::system_clock;
    using event_ptr = std::unique_ptr<Event>;

public:
    Manager() noexcept;

    bool add_group(const std::string &name) noexcept;
    bool add_event(const EventInfo &info) noexcept;

    unsigned short remove_old() noexcept;

    [[nodiscard]] bool check_event_exist(const std::string &title) const noexcept;
    [[nodiscard]] bool check_group_exist(const std::string &name) const noexcept;

    bool list_events() const noexcept;

private:
    std::unordered_set<std::string> event_titles_;
    std::set<Event *, Compare> sorted_events_;
    // I well switch to std::list later
    std::unordered_map<std::string, std::vector<event_ptr>> events_;
};