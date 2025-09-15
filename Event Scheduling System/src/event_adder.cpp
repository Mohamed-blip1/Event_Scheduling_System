// event_adder.cpp
#include "event_adder.h"
#include <iostream>

bool add_event_flow(Manager &manager, Time &time)
{
    std::string title, str_time;
    title = utils::get_string("Enter event title (or type 'cancel' to exit):");
    if (title == "cancel")
    {
        std::cout << "Event creation cancelled.\n";
        return false;
    }

    utils::help_menu();
    while (true)
    {
        // Mean: show menu
        if (auto maybe_input = utils::parse_time_input(">");
            maybe_input.has_value())
        {

            str_time = maybe_input.value();
        }
        else
            continue;

        try
        {
            time.time_format(str_time);
        }
        catch (const std::exception &e)
        {
            std::cout << "\nError: " << e.what() << "\n";
            continue;
        }

        if (utils::confirm_time(time.tt))
        {
            manager.add_event(title, time.tp);
            std::cout << "Success.\n";
            return true;
        }

        std::cout << "Let's try again...\n\n";
    }
}