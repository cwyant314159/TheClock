#include "clocks/simple_clock.hpp"

#include "utils/constants.hpp"
#include "utils/time_point.hpp"

namespace {
    constexpr std::size_t DIAL_TICKS      = 60U;   // 60 minutes/seconds on the dial
    constexpr std::size_t ACCENT_INTERVAL = 5U;    // accent every 5th tick
    constexpr float       TICK_SCALE      = 0.1f;  // length of tick (% dial radius)
    constexpr float       PIN_SCALE       = 0.03f; // radius of the pin (% dial radius)
    
    // Degrees per unit time
    constexpr float DEG_PER_SEC = Utils::DEGREES_PER_REVOLUTION / 60.0f;
    constexpr float DEG_PER_MIN = Utils::DEGREES_PER_REVOLUTION / 60.0f;
    constexpr float DEG_PER_HR  = Utils::DEGREES_PER_REVOLUTION / 12.0f;
    

    // Hand scale (% dial radius) and thickness (px) values
    constexpr float SEC_HAND_SCALE     = 0.97f;
    constexpr float SEC_HAND_THICKNESS = 2.00f;
    
    constexpr float MIN_HAND_SCALE     = 0.90f;
    constexpr float MIN_HAND_THICKNESS = 2.00f * SEC_HAND_THICKNESS;

    constexpr float HR_HAND_SCALE      = 0.70f;
    constexpr float HR_HAND_THICKNESS  = 2.00f * MIN_HAND_THICKNESS;
}

SimpleClock::SimpleClock(const Vector2& origin, float radius)
    : m_dial{origin, radius, RAYWHITE}
    , m_ticks{origin, radius, DIAL_TICKS, ACCENT_INTERVAL, SEC_HAND_THICKNESS, TICK_SCALE, GRAY}
    , m_hands{
        Hand{origin, HR_HAND_SCALE  * radius, HR_HAND_THICKNESS,  RED},  // hours
        Hand{origin, MIN_HAND_SCALE * radius, MIN_HAND_THICKNESS, BLUE}, // minutes
        Hand{origin, SEC_HAND_SCALE * radius, SEC_HAND_THICKNESS, GOLD}  // seconds
    }
    , m_hoursHand{m_hands.at(0)}
    , m_minutesHand{m_hands.at(1)}
    , m_secondsHand{m_hands.at(2)}
    , m_hingePin{origin, PIN_SCALE * radius, DARKGRAY}
{
}

void SimpleClock::Update (const Utils::TimePoint& tp)
{
    const float secondsAngle = tp.seconds * DEG_PER_SEC;

    const float minutesRatio = secondsAngle / Utils::DEGREES_PER_REVOLUTION;
    const float minutesAngle = (tp.minutes + minutesRatio) * DEG_PER_MIN;

    const auto  hours      = tp.hours % 12;
    const float hoursRatio = minutesAngle / Utils::DEGREES_PER_REVOLUTION;
    const float hoursAngle = (hours + hoursRatio) * DEG_PER_HR;

    m_secondsHand.SetAngle(secondsAngle);
    m_minutesHand.SetAngle(minutesAngle);
    m_hoursHand.SetAngle(hoursAngle);
}

void SimpleClock::Draw() const
{
    DrawDial();
    DrawHands();
}

void SimpleClock::DrawDial() const
{
    m_dial.DrawFace(m_ticks);   
}

void SimpleClock::DrawHands() const
{
    m_dial.DrawHands(m_hands, m_hingePin);
}