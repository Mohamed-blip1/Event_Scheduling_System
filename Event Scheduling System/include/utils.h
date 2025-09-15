#pragma once
// utils.h
#include <iostream>
#include <optional>
#include <iomanip>
#include <limits>

constexpr size_t FOUR_SPACES = 4;
constexpr size_t TWO_SPACES = 2;
constexpr int CONFIRM_YES = 1;
constexpr int CONFIRM_NO = 2;
constexpr size_t MAX = 2;
constexpr size_t MIN = 1;

std::string trim(const std::string &str, char target = ' ');

std::string time_format(const std::string &temp, size_t space);

std::string get_time_component(const std::string &label, size_t space, char symbol = '\0');

namespace utils
{

    void menu() noexcept;
    void help_menu() noexcept;

    std::string get_string(const std::string &UI) ;

    std::string help_format_time() noexcept;

    size_t get_valid_number(size_t min = MIN, size_t max = MAX);

    std::optional<std::string> parse_time_input(const std::string &ui);

    bool confirm_time(const std::time_t &tt) noexcept;
}