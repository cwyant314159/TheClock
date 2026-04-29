#ifndef TIME_POINT_HPP
#define TIME_POINT_HPP

#include <cstdint>

namespace Utils {

/**
 * @brief A structure containing hours (24hr), minutes, seconds, and milliseconds
 */
struct TimePoint
{
    TimePoint();
    TimePoint(int64_t h, int64_t m, int64_t s, int64_t ms);

    int64_t hours;
    int64_t minutes;
    int64_t seconds;
    int64_t milliseconds;
};

} // namespace utils

#endif // TIME_POINT_HPP