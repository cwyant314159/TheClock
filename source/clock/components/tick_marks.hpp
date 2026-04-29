#ifndef TICK_MARKS_HPP
#define TICK_MARKS_HPP

#include <cstdint>

extern "C" { 
    #include <raylib.h> 
}

class TickMarks
{
public:
    TickMarks(const Vector2& origin, float radius, std::size_t tickCount, std::size_t accentInterval, float tickThickness, float tickScale, Color color);
    void Draw() const;

private:
    const Vector2     m_origin;
    const float       m_radius;
    const std::size_t m_count;
    const std::size_t m_accentInterval;
    const float       m_thickness;
    const float       m_scale;
    const Color       m_color;
    const float       m_degreesPerTick;
};

#endif // TICK_MARKS_HPP