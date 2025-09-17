// manager.cpp
#include "manager.h"

Manager::Manager() noexcept
{
    events_.rehash(EXPECTED_EVENTS);
    events_.max_load_factor(0.7);
}

bool Manager::check_event_exist(const std::string &title) const noexcept
{
    if (events_.count(title))
        return true;
    return false;
}

bool Manager::add_event(const EventInfo &info) noexcept
{
    auto [it, ok] = events_.emplace(info.title_, std::make_unique<Event>(info));
    if (!ok)
        return false;

    Event *event_ptr = it->second.get();
    auto it_ = sorted_events_.lower_bound(event_ptr);
    sorted_events_.emplace_hint(it_, event_ptr);
    return true;
}

unsigned short Manager::remove_old() noexcept
{
    NowTime now_time;
    unsigned short removed = ZERO;

    auto it = sorted_events_.rbegin();
    while (it != sorted_events_.rend())
    {
        auto &event = *it;
        if (event->get_time() > now_time.tp_)
            break;

        events_.erase(event->get_title());
        auto base_it = std::prev(it.base());
        it = std::make_reverse_iterator(sorted_events_.erase(base_it));
        removed++;
    }
    return removed;
}

bool Manager::list_events() const noexcept
{
    if (sorted_events_.size() == ZERO)
        return false;
    for (const auto &event : sorted_events_)
    {
        auto time = system_clock::to_time_t(event->get_time());

        std::cout << "Title: " << event->get_title()
                  << ". Time: " << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M") << "\n";
    }
    return true;
}