#ifndef ICLOCK_HPP
#define ICLOCK_HPP

namespace Utils { struct TimePoint; }

class IClock
{
public:
    virtual ~IClock() = default;
    virtual void Update(const Utils::TimePoint& tp) = 0;
    virtual void Draw() const = 0;
};

#endif // ICLOCK_HPP