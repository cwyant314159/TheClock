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
    void Update(std::chrono::hh_mm_ss<std::chrono::milliseconds> currTime);
    void Draw() const;

private:
    // Number of hands on the clock face (including the subface).
    static constexpr std::size_t NUM_HANDS{4};

    const Vector2 m_center;
    const float   m_radius;
    const float   m_hingePinRadius;
    const Vector2 m_subfaceCenter;
    const float   m_subfaceRadius;
    const float   m_subfaceHingePinRadius;
    Color         m_faceColor;
    Color         m_tickColor;
    Color         m_hingePinColor;
    std::array<Color, NUM_HANDS> m_handsColor;
    std::array<float, NUM_HANDS> m_handsAngleDegrees;

    void DrawTicks(Vector2 center, float radius, int tickCount, int accentInterval) const;
    void DrawHand(std::size_t handIdx) const;
    void DrawHand(Vector2 center, float radius, float angle, float thickness, Color color) const;
};

#endif // CLOCK_HPP