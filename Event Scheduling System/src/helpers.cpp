// helpers.cpp
#include "helpers.h"
#include <vector>
#include <iomanip>

using time_point = std::chrono::system_clock::time_point;

NowTime::NowTime() noexcept
{
    tp_ = system_clock::now();
    tt_ = system_clock::to_time_t(tp_);
    tm_ = *std::localtime(&tt_);
}

time_point Time::time_format(const std::string &st)
{
    clear();
    iss_.str(st);
    tm_.tm_isdst = AUTO_DST;
    iss_ >> std::get_time(&tm_, "%Y-%m-%d %H:%M");

    if (iss_.fail())
        throw std::runtime_error("Invalid Format!");

    tt_ = std::mktime(&tm_);
    if (tt_ == INVALID_TIME)
        throw std::runtime_error("Time not supported!");

    tp_ = system_clock::from_time_t(tt_);

    return tp_;
}

void Time::clear() noexcept
{
    iss_.str("");
    iss_.clear();
    tm_ = std::tm{};
}

bool Compare::operator()(const event_ptr &a_, const event_ptr &b_) const noexcept
{
    auto time1 = a_->get_time();
    auto time2 = b_->get_time();
    if (time1 != time2)
        return time1 < time2;

    return a_->get_title() < b_->get_title();
}