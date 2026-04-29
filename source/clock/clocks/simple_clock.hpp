#ifndef SIMPLE_CLOCK_HPP
#define SIMPLE_CLOCK_HPP

#include <vector>

extern "C" { 
    #include <raylib.h> 
}

#include "clocks/iclock.hpp"
#include "components/dial.hpp"
#include "components/hand.hpp"
#include "components/pin.hpp"
#include "components/tick_marks.hpp"

class SimpleClock : public IClock
{
public:
    SimpleClock(const Vector2& origin, float radius);
    void Update (const Utils::TimePoint& tp) override;
    void Draw() const override;
    void DrawDial() const;
    void DrawHands() const;

private:
    Dial              m_dial;
    TickMarks         m_ticks;
    std::vector<Hand> m_hands;
    Hand&             m_hoursHand;
    Hand&             m_minutesHand;
    Hand&             m_secondsHand;
    Pin               m_hingePin;
};

#endif // SIMPLE_CLOCK_HPP