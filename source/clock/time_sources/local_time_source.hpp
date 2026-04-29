#ifndef LOCAL_TIME_SOURCE
#define LOCAL_TIME_SOURCE

#include <chrono>

#include "time_sources/isource.hpp"
#include "time_sources/utc_time_source.hpp"

class LocalTimeSource : public ISource
{
public:
    LocalTimeSource();
    LocalTimeSource(const std::chrono::time_zone* timeZone);
    Utils::TimePoint Now() override;

private:
    const std::chrono::time_zone* m_timeZone;
    UtcTimeSource                 m_utcSource;
};


#endif // LOCAL_TIME_SOURCE