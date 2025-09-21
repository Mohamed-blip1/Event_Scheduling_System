// manager.cpp
#include "manager.h"

Manager::Manager() noexcept
{
    events_.rehash(EXPECTED_EVENTS);
    events_.max_load_factor(0.7);

    event_titles_.rehash(EXPECTED_EVENTS);
    event_titles_.max_load_factor(0.7);

    EventInfo info;
    NowTime time;

    //    Debuging
    //  using namespace std::chrono;
    //  using day = std::chrono::duration<double, std::ratio<86400>>;
    //  auto system_day = duration_cast<system_clock::duration>(day{1});
    //  time.tp_ -= system_day * 4;
    //  add_group("a");
    //  for (size_t i = 0; i <= 6; ++i)
    //  {
    //      info.title_ = '1' + i;
    //      info.group_name_ = "a";
    //      info.time_ = (time.tp_ += system_day);
    //      add_event(info);
    //  }
}

bool Manager::check_event_exist(const std::string &title) const noexcept
{
    return event_titles_.count(title) > 0;
}

bool Manager::check_group_exist(const std::string &name) const noexcept
{
    return events_.count(name) > 0;
}

bool Manager::add_group(const std::string &name) noexcept
{
    auto [it, ok] = events_.try_emplace(name);
    return ok;
}

bool Manager::add_event(const EventInfo &info) noexcept
{
    if (!check_group_exist(info.group_name_))
        return false;

    auto &it = events_.at(info.group_name_);
    it.emplace_back(std::make_unique<Event>(info));

    Event *event_ptr = it.back().get();
    auto it_ = sorted_events_.lower_bound(event_ptr);
    sorted_events_.emplace_hint(it_, event_ptr);
    event_titles_.emplace(info.title_);

    return true;
}

unsigned short Manager::remove_old() noexcept
{
    NowTime now_time;
    unsigned short removed = ZERO;

    auto it = sorted_events_.begin(); // iterate from oldest to newest
    while (it != sorted_events_.end())
    {
        Event *event = *it;
        if (event->get_time() > now_time.tp_)
            break;

        // Remove from event titles
        event_titles_.erase(event->get_title());

        // Erase from set (returns next iterator)
        it = sorted_events_.erase(it);

        // Remove from the owning vector
        auto &events_vec = events_.at(event->get_group_name());
        auto vec_it = std::find_if(events_vec.begin(), events_vec.end(),
                                   [event](const event_ptr &ptr)
                                   { return ptr.get() == event; });

        if (vec_it != events_vec.end())
            events_vec.erase(vec_it);

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
