#include "components/pin.hpp"

Pin::Pin(const Vector2& origin, float radius, Color color)
    : m_origin{origin}
    , m_radius{radius}
    , m_color{color}
{
}

void Pin::Draw() const
{
    DrawCircleSector(m_origin, m_radius, 0, 360, 90, m_color);
}