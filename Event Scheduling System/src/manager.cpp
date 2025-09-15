// manager.cpp
#include "manager.h"

Manager::Manager() noexcept
{
    events_.rehash(EXPECTED_EVENTS);
    events_.max_load_factor(0.7);
}

void Manager::add_event(const std::string &title, const time_point &tp) noexcept
{
    Event event(title, tp);

    auto ptr = std::make_shared<Event>(title, tp);
    auto it = sorted_events_.lower_bound(ptr);
    sorted_events_.emplace_hint(it, ptr);
    events_.emplace(title, ptr);
}