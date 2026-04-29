#include "components/hand.hpp"

#include "utils/constants.hpp"
#include "utils/conversions.hpp"

#include <complex>

Hand::Hand(const Vector2& origin, float length, float thickness, Color color)
    : m_origin{origin}
    , m_length{length}
    , m_thickness{thickness}
    , m_color{color}
    , m_angle{0.0f}
{
}

void Hand::Draw() const
{
    const float   drawAngle = m_angle + Utils::TWELVE_OCLOCK_ANGLE_OFFSET;
    const Vector2 endPoint  = Utils::CartesianEndpoint(m_origin, m_length, drawAngle);
    DrawLineEx(m_origin, endPoint, m_thickness, m_color);
}

void Hand::SetAngle(float degrees)
{
    m_angle = degrees;
}