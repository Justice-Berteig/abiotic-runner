/*
 *  Header file to define type aliases used throughout the program.
 */

#pragma once

#include <chrono>

/*
 * Type alias for time stuff because the names are super long otherwise.
 */
using TimeMicroseconds = std::chrono::microseconds;
using TimePoint        = std::chrono::time_point<std::chrono::steady_clock>;
