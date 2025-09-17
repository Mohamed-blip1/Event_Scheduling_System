// main.cpp
#include "event_adder.h"

enum class Menu : size_t
{
    Exit = 0,
    AddEvent,
    CustomizeEvent,
    RemoveOldEvent,
    ListEvents,
    ShowMenu
};

int main()
{
    std::cout
        << "\n=====Event Scheduling System=====\n";
    menu_utils::main_menu();

    size_t choice;
    Manager manager;
    Time time;
    while (true)
    {
        Menu choice =
            static_cast<Menu>(input_utils::get_valid_number(0, 5));
        switch (choice)
        {
        case Menu::Exit:
            std::cout << "Goodbye.\n";
            break;

        case Menu::AddEvent:
            if (add_event_flow(manager, time))
                // If event added success show main menu
                menu_utils::main_menu();
            break;

        case Menu::CustomizeEvent:
            // Later Features: Reminders ,Recurring pattern,Duration,Attendees
            std::cout << "Soon!\n";
            break;

        case Menu::RemoveOldEvent:
        {
            unsigned short removed = manager.remove_old();
            if (removed != ZERO)
                std::cout << "'" << removed << " ' "
                          << "Event removed successfully.\n";
            else
                std::cout << "No events were removed!\n";
        }
        break;
        case Menu::ListEvents:
            if (!manager.list_events())
                std::cout << "No events yet!\n";
            break;

        case Menu::ShowMenu:
            menu_utils::main_menu();
            break;
        }

        if (choice == Menu::Exit)
            break;
    }
    return 0;
}
