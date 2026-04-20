#include "Clock.hpp"

#include <complex>
#include <cstdio>

namespace {
    // Indices into the hands arrays
    constexpr std::size_t SECONDS_IDX = 0;
    constexpr std::size_t MINUTES_IDX = 1;
    constexpr std::size_t HOURS_IDX   = 2;

    // Percentage scale of the hinge pin radius relative to the clock radius
    constexpr float HINGE_PIN_SCALE = 0.03;

    // Global angle offset
    //
    // To make working with the time and angle of the hands, this angle
    // offset is applied to all angle measurements to shift 0 degrees to
    // be full vertical (12 o'clock position). To make things consistent,
    // the offset should be applied at the point nearest drawing.
    constexpr float DEG_ANGLE_OFFSET = -90.0f;

    // Number of degrees between the units of time
    constexpr float DEG_PER_SECOND = 360.0f / 60.0f;
    constexpr float DEG_PER_MINUTE = DEG_PER_SECOND;
    constexpr float DEG_PER_HOUR   = 360.0f / 12.0f;
}

Clock::Clock(const Vector2& center, float radius)
    : m_center{center}
    , m_radius{radius}
    , m_hingePinRadius{radius * HINGE_PIN_SCALE}
    , m_faceColor{RAYWHITE}
    , m_tickColor{GRAY}
    , m_hingePinColor{DARKGRAY}
    , m_handsColor{GOLD, BLUE, RED}
    , m_handsAngleDegrees{0.0f, 0.0f, 0.0f}
{
}

void Clock::Update(std::chrono::hh_mm_ss<std::chrono::seconds> currTime)
{
    // const int milliseconds = currTime.subseconds().count();
    const int seconds      = currTime.seconds().count();
    const int minutes      = currTime.minutes().count();
    const int hours        = currTime.hours().count() % 12;

    m_handsAngleDegrees[SECONDS_IDX] = seconds * DEG_PER_SECOND;
 
    // The minutes and hours hand will move between marks based on where the
    // lower magnitude hand is located. As an approximation, the additional
    // angle is computed as the ratio of the magnitude. The ratio is based off
    // the lower magnitude hand angle over 360 degrees. To prevent small
    // rounding errors from causing jitter on the hand, the lower magnitude
    // component is checked directly when close to the 12 o'clock position.
    
    // minutes
    float minutesRatio = m_handsAngleDegrees.at(SECONDS_IDX) / 360.0f;
    if (0 == seconds)
    {
        minutesRatio = 0.0f;
    }

    m_handsAngleDegrees[MINUTES_IDX] = (minutes + minutesRatio)* DEG_PER_MINUTE;

    // hours
    float hoursRatio = m_handsAngleDegrees.at(MINUTES_IDX) / 360.0;
    if (0 == minutes)
    {
        hoursRatio = 0.0f;
    }

    m_handsAngleDegrees[HOURS_IDX] = (hours + hoursRatio)* DEG_PER_HOUR;
}

void Clock::Draw() const
{
    DrawCircleV(m_center, m_radius, m_faceColor);   
    DrawTicks();
    DrawHand(SECONDS_IDX);
    DrawHand(MINUTES_IDX);
    DrawHand(HOURS_IDX);
    DrawCircleV(m_center, m_hingePinRadius, m_hingePinColor);
}

void Clock::DrawTicks() const
{
    // Draw the 60 minute markers around the clock face.
    for (int minuteMark = 0; minuteMark < 60; ++minuteMark)
    {
        // Compute the angle of the minute mark with 0 degrees at the
        // 12 o'clock position.
        const float angle = (minuteMark * DEG_PER_MINUTE) + DEG_ANGLE_OFFSET;

        // Minute ticks at the 5 minute marks are thicker and longer than the
        // other ticks.
        float tickThickness = 2.0f;
        float tickScale     = 0.05f; // percent length of the radius
        if (0 == (minuteMark % 5)) {
            tickThickness = 4.0f;
            tickScale     = 0.1f;
        }

        // Compute the tick mark's start and end x/y-coordinates by abusing the
        // Complex type to do polar to rectangular conversions.
        const float angleRad = angle * DEG2RAD;
        const std::complex<float> startOffsetPolar = std::polar(m_radius, angleRad);
        const Vector2 start{
            .x = m_center.x + startOffsetPolar.real(),
            .y = m_center.y + startOffsetPolar.imag()
        };
        
        const std::complex<float> endOffsetPolar = std::polar(m_radius * (1.0f - tickScale), angleRad);
        const Vector2 end{
            .x = m_center.x + endOffsetPolar.real(),
            .y = m_center.y + endOffsetPolar.imag()
        };

        // Draw the tick marks from the starting to the ending coordinate
        DrawLineEx(start, end, tickThickness, m_tickColor);
    }
}

void Clock::DrawHand(std::size_t handIdx) const
{
    // Thickness of the clock face hands.
    constexpr std::array<float, NUM_HANDS> thickness{2.0f, 4.0f, 8.0f};
    
    // Percentage length of the radius of the clock face hands.
    constexpr std::array<float, NUM_HANDS> scale{0.97f, 0.90f, 0.70f};

    // Compute the length of the hand
    const float length = m_radius * scale.at(handIdx);

    // Adjust the hands angle by the global angle offset.
    const float drawAngle = m_handsAngleDegrees.at(handIdx) + DEG_ANGLE_OFFSET;

    // Compute the hand's endpoint by abusing the Complex type to do polar to
    // rectangular conversions.
    const std::complex<float> offsetPolar = std::polar(length, drawAngle * DEG2RAD);
    const Vector2 end {
        .x = m_center.x + offsetPolar.real(),
        .y = m_center.y + offsetPolar.imag()
    };

    // Draw the hand starting from the center
    DrawLineEx(m_center, end, thickness.at(handIdx), m_handsColor.at(handIdx));
}

