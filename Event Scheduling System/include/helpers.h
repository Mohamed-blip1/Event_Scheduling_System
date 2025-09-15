#pragma once
// helpers.h
#include "event.h"
#include <sstream>
#include <memory>

constexpr short AUTO_DST = -1;
constexpr std::time_t INVALID_TIME = -1;

struct NowTime
{
    using system_clock = std::chrono::system_clock;
    system_clock::time_point tp;
    std::time_t tt;
    std::tm tm;

    NowTime() noexcept;
    ~NowTime() = default;
};

struct Time
{
    using system_clock = std::chrono::system_clock;
    std::istringstream iss;
    system_clock::time_point tp;
    std::time_t tt;
    std::tm tm{};

    Time() = default;

    //  [[nodiscard]]
    void time_format(const std::string &st);

    void clear() noexcept;
};

struct Compare
{
    using event_ptr = std::shared_ptr<Event>;
    bool operator()(const event_ptr &a, const event_ptr &b) const; // Is it can be noexcept
};