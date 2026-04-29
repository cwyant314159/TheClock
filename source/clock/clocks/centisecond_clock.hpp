#ifndef CENTISECOND_CLOCK_HPP
#define CENTISECOND_CLOCK_HPP

extern "C" { 
    #include <raylib.h> 
}

#include "clocks/iclock.hpp"
#include "components/dial.hpp"
#include "components/hand.hpp"
#include "components/pin.hpp"
#include "components/tick_marks.hpp"

class CentisecondClock : public IClock
{
public:
    CentisecondClock(const Vector2& origin, float radius);
    void Update (const Utils::TimePoint& tp) override;
    void Draw() const override;

private:
    Dial      m_dial;
    TickMarks m_ticks;
    Hand      m_hand;
    Pin       m_hingePin;

};

#endif // CENTISECOND_CLOCK_HPP