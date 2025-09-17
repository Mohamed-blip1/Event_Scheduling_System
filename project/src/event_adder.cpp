// event_adder.cpp
#include "event_adder.h"
#include "helpers.h"
#include <iostream>

bool add_event_flow(Manager &manager, Time &time)
{
    EventInfo info;
    std::string str_time;
    info.title_ =
        input_utils::get_string("\nEnter event Title (or type 'cancel' to exit): ");

    if (info.title_ == "cancel")
    {
        std::cout << "Event creation cancelled.\n";
        return false;
    }

    menu_utils::help_menu();
    while (true)
    {
        if (auto maybe_input = time_utils::parse_time_input(">");
            (maybe_input.has_value()))
        {
            str_time = maybe_input.value();
        }
        else // show help_menu
            continue;

        try
        {
            info.time_ = time.time_format(str_time);
            break;
        }
        catch (const std::exception &e)
        {
            std::cout << "\nError: " << e.what() << "\n";
            std::cout << "Please use format: YYYY-MM-DD HH:MM or type 'help'\n";
            continue;
        }
    }

    info.location_ =
        input_utils::get_string("\nEnter event Location: ");

    info.description_ =
        input_utils::get_string("Enter event Description: ");

    if (!manager.add_event(info))
    {
        std::cout << "Event with this title already exists!\n";
        return false;
    }
    std::cout << "Success! "
                 "(You can manage your event at any time)\n";
    return true;
}