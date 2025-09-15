// manin.cpp
//  #include "manager.h"
#include "event_adder.h"
#include <cstring>
#include <limits>

using time_point = std::chrono::system_clock::time_point;
using system_clock = std::chrono::system_clock;

int main()
{
    Time time;
    Manager manager;

    size_t choice =
        std::numeric_limits<size_t>::max();

    std::cout << "\n====Event Scheduling====\n";
    utils::menu();
    while (choice != 0)
    {
        choice = utils::get_valid_number();

        switch (choice)
        {
        case 1:
            add_event_flow(manager, time);
            break;
        case 9:
            utils::menu();
        }
    }
    return 0;
}
