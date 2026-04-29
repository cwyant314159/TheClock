#include "clocks/centisecond_clock.hpp"

#include "utils/constants.hpp"
#include "utils/time_point.hpp"

namespace {
    constexpr std::size_t DIAL_TICKS      = 100U;  // 100 centiseconds on the dial
    constexpr std::size_t ACCENT_INTERVAL = 10U;   // accent every 10th tick
    constexpr float       THICKNESS       = 2.0f;  // hand and tick thickness (px)
    constexpr float       TICK_SCALE      = 0.05f; // length of tick (% dial radius)
    constexpr float       HAND_SCALE      = 0.95f; // length of hand (% dial radius)
    constexpr float       PIN_SCALE       = 0.03f; // radius of the pin (% dial radius)
    
    // Degrees per centisecond
    constexpr float DEG_PER_TICK = Utils::DEGREES_PER_REVOLUTION / DIAL_TICKS;
}

CentisecondClock::CentisecondClock(const Vector2& origin, float radius)
    : m_dial{origin, radius, RAYWHITE}
    , m_ticks{origin, radius, DIAL_TICKS, ACCENT_INTERVAL, THICKNESS, TICK_SCALE, GRAY}
    , m_hand{origin, HAND_SCALE * radius, THICKNESS, LIGHTGRAY}
    , m_hingePin{origin, PIN_SCALE * radius, DARKGRAY}
{
}

void CentisecondClock::Update (const Utils::TimePoint& tp)
{
    const int   centiseconds = tp.milliseconds / 10;
    const float angle        = centiseconds * DEG_PER_TICK;
    m_hand.SetAngle(angle);
}

void CentisecondClock::Draw() const
{
    m_dial.DrawFace(m_ticks);
    m_dial.DrawHands(m_hand, m_hingePin);
}