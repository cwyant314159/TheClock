#include "time_sources/utc_time_source.hpp"

#include "utils/time_point.hpp"

Utils::TimePoint UtcTimeSource::Now()
{
    const auto currUtc        = CurrentUtcTime();
    const auto timeComponents = std::chrono::hh_mm_ss { MillisecondsSinceMidnight(currUtc) };
    return Utils::TimePoint{
        timeComponents.hours().count(),
        timeComponents.minutes().count(),
        timeComponents.seconds().count(),
        timeComponents.subseconds().count()
    };
}

std::chrono::system_clock::time_point UtcTimeSource::CurrentUtcTime() const
{
    return std::chrono::system_clock::now();
}