#ifndef UTC_TIME_SOURCE
#define UTC_TIME_SOURCE

#include <chrono>

#include "time_sources/isource.hpp"

class UtcTimeSource : public ISource
{
public:
    Utils::TimePoint Now() override;
    std::chrono::system_clock::time_point CurrentUtcTime() const;
};

#endif // UTC_TIME_SOURCE