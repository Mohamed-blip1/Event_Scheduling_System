// main.cpp
#include "event_adder.h"

enum class Menu : size_t
{
    Exit = 0,
    AddGroup,
    AddEvent,
    CustomizeEvent,
    ListEvents,
    RemoveOldEvent,
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
            static_cast<Menu>(input_utils::get_valid_number(0, 6));
        switch (choice)
        {
        case Menu::Exit:
            std::cout << "Goodbye.\n";
            break;

        case Menu::AddGroup:
        {
            std::string name = input_utils::get_string("Enter group name: ");
            if (manager.add_group(name))
                std::cout << "Group added seccessfully.\n";
            else
                std::cout << "Group already exist!\n";
        }
        break;

        case Menu::AddEvent:
            if (add_event_flow(manager, time))
                menu_utils::main_menu(); // If event added success show main menu
            break;

        case Menu::CustomizeEvent:
            std::cout << "Soon!\n"; // Later Features: (Reminders ,Recurring pattern,Duration,Attendees)
            break;

        case Menu::ListEvents:
            if (!manager.list_events())
                std::cout << "No events yet!\n";
            break;

        case Menu::RemoveOldEvent:
        {
            unsigned short removed = manager.remove_old();
            if (removed != ZERO)
                std::cout << "'" << removed << "' "
                          << "Event(s) removed successfully.\n";
            else
                std::cout << "No events were removed!\n";
        }
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
