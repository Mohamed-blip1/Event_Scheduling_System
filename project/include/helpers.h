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
    system_clock::time_point tp_;
    std::time_t tt_;
    std::tm tm_;

    NowTime() noexcept;
    ~NowTime() = default;
};

struct Time
{
    using time_point = std::chrono::system_clock::time_point;
    using system_clock = std::chrono::system_clock;
    std::istringstream iss_;
    std::time_t tt_;
    time_point tp_;
    std::tm tm_{};

    Time() = default;

    [[nodiscard]] time_point time_format(const std::string &st);

    void clear() noexcept;
};

struct Compare
{
    using event_ptr = Event *;
    bool operator()(const event_ptr &a_, const event_ptr &b_) const noexcept;
};
