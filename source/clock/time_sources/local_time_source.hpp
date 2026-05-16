#ifndef LOCAL_TIME_SOURCE
#define LOCAL_TIME_SOURCE

#include <chrono>

#include "time_sources/isource.hpp"
#include "time_sources/utc_time_source.hpp"

// At the time of writing, MacOS did not properly handle timezones in the 
// chrono library. A 3rd party library is used on MacOS targets that has a 
// similar (if not exact) API to the chrono library.
#if defined(__APPLE__)
    #include "date/tz.h"
    namespace chrono_tz = date;
#else
    namespace chrono_tz = std::chrono;
#endif

class LocalTimeSource : public ISource
{
public:
    LocalTimeSource();
    LocalTimeSource(const chrono_tz::time_zone* timeZone);
    Utils::TimePoint Now() override;

private:
    const chrono_tz::time_zone* m_timeZone;
    UtcTimeSource               m_utcSource;
};


#endif // LOCAL_TIME_SOURCE