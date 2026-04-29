#ifndef COMPOUND_CLOCK_HPP
#define COMPOUND_CLOCK_HPP

extern "C" { 
    #include <raylib.h> 
}

#include "clocks/iclock.hpp"
#include "clocks/centisecond_clock.hpp"
#include "clocks/simple_clock.hpp"

class CompoundClock : public IClock
{
public:
    CompoundClock(const Vector2& origin, float radius);
    void Update (const Utils::TimePoint& tp) override;
    void Draw() const override;

private:
    SimpleClock      m_mainClock;
    CentisecondClock m_subClock;
};


#endif // COMPOUND_CLOCK_HPP