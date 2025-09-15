// healpers.cpp
#include "helpers.h"
#include <vector>
#include <iomanip>

NowTime::NowTime() noexcept
{
    tp = system_clock::now();
    tt = system_clock::to_time_t(tp);
    tm = *std::gmtime(&tt);
}

void Time::time_format(const std::string &st)
{
    clear();
    iss.str(st);
    tm.tm_isdst = AUTO_DST;
    iss >> std::get_time(&tm, "%Y-%m-%d %H:%M");

    if (iss.fail())
        throw std::runtime_error("Invalid Format!");

    tt = std::mktime(&tm);
    if (tt == INVALID_TIME)
        throw std::runtime_error("Time not supported!");

    tp = system_clock::from_time_t(tt);
}

void Time::clear() noexcept
{
    iss.str("");
    iss.clear();
    tm = std::tm{};
}

bool Compare::operator()(const event_ptr &a, const event_ptr &b) const
{
    auto time1 = a->get_time();
    auto time2 = b->get_time();
    if (time1 != time2)
        return time1 < time2;

    return a->get_title() < b->get_title();
}