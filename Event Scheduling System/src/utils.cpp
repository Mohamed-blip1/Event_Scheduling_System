// utils.cpp
#include "utils.h"

std::string trim(const std::string &str, char target)
{
    size_t start = str.find_first_not_of(target);
    size_t end = str.find_last_not_of(target);

    if (start == std::string::npos)
        return "";

    return str.substr(start, end - start + 1);
}

void utils::menu() noexcept
{
    constexpr size_t MENU_INDENT = 2;

    std::cout << "\nMENU:\n";
    std::cout << "----------------\n";
    std::cout << std::left << std::setw(MENU_INDENT) << "[1]" << " - Add event.\n";
    std::cout << std::left << std::setw(MENU_INDENT) << "[2]" << " - Adjuct event.\n";
    std::cout << "----------------\n";
}

void utils::help_menu() noexcept
{
    std::cout << "\nEvent time menu\n"
              << "----------------------------\n"
              << "  - To enter date manually: [YYYY-MM-DD HH:MM]\n"
              << "  - To get help formatting: type [help]\n"
              << "  - To cancel the action:   type [cancel]\n"
              << "  - To display the menu :   type [menu]\n"
              << "----------------------------\n\n";
}

std::string utils::get_string(const std::string &UI)
{
    std::string name;
    do
    {
        std::cout << UI;
        std::getline(std::cin, name);
        name = trim(name);
        if (name.empty())
            std::cout << "Input cannot be empty. Please try again.\n";

    } while (name.empty());

    return name;
}

size_t utils::get_valid_number(size_t min, size_t max)
{
    size_t number;
    std::string input;

    if (min > max)
        std::swap(min, max);

    while (true)
    {
        std::cout << "Enter choice > ";
        std::getline(std::cin, input);

        if (input.empty())
        {
            std::cout << "\nInput was empty!\n";
            continue;
        }

        std::istringstream iss(input);

        if (iss >> number && iss.eof())
            if (number >= min && number <= max)
                return number;

        std::cout << "\nInvalid number!\n";
    }
}

std::string time_format(const std::string &input, size_t width)
{
    if (input.empty())
        return std::string(width, '0');
    if (input.length() >= width)
        return input;
    return std::string(width - input.length(), '0') + input;
}

std::string get_time_component(const std::string &label, size_t width, char symbol)
{
    std::string input;
    std::cout << "Enter " << label << ": ";

    std::getline(std::cin, input);
    std::string padded = time_format(input, width);

    if (symbol != '\0')
        padded += symbol;

    return padded;
}

std::string utils::help_format_time() noexcept
{
    std::string time_str;
    time_str.reserve(16);

    time_str += get_time_component("Year", FOUR_SPACES, '-');
    time_str += get_time_component("Month", TWO_SPACES, '-');
    time_str += get_time_component("Day", TWO_SPACES, ' ');

    time_str += get_time_component("Hour", TWO_SPACES, ':');
    time_str += get_time_component("Minute", TWO_SPACES);

    return time_str;
}

std::optional<std::string> utils::parse_time_input(const std::string &UI)
{
    std::string input = get_string(UI);

    if (input == "menu")
    {
        help_menu();
        return std::nullopt;
    }

    if (input == "help")
        input = help_format_time();

    return input;
}

bool utils::confirm_time(const std::time_t &tt) noexcept
{

    std::cout << "Confirm time: "
              << std::put_time(std::localtime(&tt), "%Y-%m-%d %H:%M") << "\n"
              << "[1] - Yes\n"
              << "[2] - No\n";

    return utils::get_valid_number(CONFIRM_YES, CONFIRM_NO) == CONFIRM_YES;
}
