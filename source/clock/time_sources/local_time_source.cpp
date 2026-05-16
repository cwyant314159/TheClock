#include "time_sources/local_time_source.hpp"
#include "utils/time_point.hpp"

#include <iostream>

LocalTimeSource::LocalTimeSource()
    : LocalTimeSource{chrono_tz::current_zone()}
{   
}

LocalTimeSource::LocalTimeSource(const chrono_tz::time_zone* timeZone)
    : m_timeZone{timeZone}
    , m_utcSource{}
{
}

Utils::TimePoint LocalTimeSource::Now()
{
    const auto utcTime        = m_utcSource.CurrentUtcTime();
    const auto localTime      = chrono_tz::zoned_time{m_timeZone, utcTime}.get_local_time();
    const auto timeComponents = std::chrono::hh_mm_ss { MillisecondsSinceMidnight(localTime) };

    return Utils::TimePoint{
        timeComponents.hours().count(),
        timeComponents.minutes().count(),
        timeComponents.seconds().count(),
        timeComponents.subseconds().count()
    };
}