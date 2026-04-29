#include "time_sources/local_time_source.hpp"

#include "utils/time_point.hpp"

LocalTimeSource::LocalTimeSource()
    : LocalTimeSource{std::chrono::current_zone()}
{   
}

LocalTimeSource::LocalTimeSource(const std::chrono::time_zone* timeZone)
    : m_timeZone{timeZone}
    , m_utcSource{}
{
}

Utils::TimePoint LocalTimeSource::Now()
{
    const auto utcTime        = m_utcSource.CurrentUtcTime();
    const auto localTime      = std::chrono::zoned_time{m_timeZone, utcTime}.get_local_time();
    const auto timeComponents = std::chrono::hh_mm_ss { MillisecondsSinceMidnight(localTime) };
    return Utils::TimePoint{
        timeComponents.hours().count(),
        timeComponents.minutes().count(),
        timeComponents.seconds().count(),
        timeComponents.subseconds().count()
    };
}