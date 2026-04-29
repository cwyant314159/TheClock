#ifndef ISOURCE_HPP
#define ISOURCE_HPP

#include <chrono>

namespace Utils { struct TimePoint; }

class ISource
{
public:
    virtual ~ISource() = default;
    virtual Utils::TimePoint Now() = 0;

protected:
    template <class T>
    std::chrono::milliseconds MillisecondsSinceMidnight(T timePoint)
    {
        // Compute the number of milliseconds since midnight
        const auto midnight = std::chrono::floor<std::chrono::days>(timePoint);
        return std::chrono::duration_cast<std::chrono::milliseconds>(timePoint - midnight);
    }
};

#endif // ISOURCE_HPP