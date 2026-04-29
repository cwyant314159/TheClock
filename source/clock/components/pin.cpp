#include "components/pin.hpp"

Pin::Pin(const Vector2& origin, float radius, Color color)
    : m_origin{origin}
    , m_radius{radius}
    , m_color{color}
{
}

void Pin::Draw() const
{
    DrawCircleV(m_origin, m_radius, m_color);
}