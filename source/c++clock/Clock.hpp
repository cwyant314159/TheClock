#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <array>
#include <chrono>

extern "C" {
#include <raylib.h>
}

class Clock
{
public:
    Clock(const Vector2& center, float radius);
    void Update(std::chrono::hh_mm_ss<std::chrono::seconds> currTime);
    void Draw() const;

private:
    // Number of hands on the clock face. It might be possible to
    // add a millisecond hand depedning on time library resolution.
    static constexpr std::size_t NUM_HANDS{3};

    const Vector2 m_center;
    const float   m_radius;
    const float   m_hingePinRadius;
    Color         m_faceColor;
    Color         m_tickColor;
    Color         m_hingePinColor;
    std::array<Color, NUM_HANDS> m_handsColor;
    std::array<float, NUM_HANDS> m_handsAngleDegrees;

    void DrawTicks() const;
    void DrawHand(std::size_t handIdx) const;
};

#endif // CLOCK_HPP