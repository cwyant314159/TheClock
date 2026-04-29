#include "utils/time_point.hpp"

Utils::TimePoint::TimePoint()
    : TimePoint(0, 0, 0, 0)
{}

Utils::TimePoint::TimePoint(int64_t h, int64_t m, int64_t s, int64_t ms)
    : hours{h}
    , minutes{m}
    , seconds{s}
    , milliseconds{ms}
{}
