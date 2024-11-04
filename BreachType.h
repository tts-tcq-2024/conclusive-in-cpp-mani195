#pragma once

#include <iostream>

enum class BreachType :std::uint8_t
{
    TOO_LOW = 0x00,
    TOO_HIGH = 0x01,
    NORMAL = 0x02
};
