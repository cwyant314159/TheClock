#include "components/tick_marks.hpp"

#include <cmath>
#include <limits>
#include <stdexcept>

#include "utils/constants.hpp"
#include "utils/conversions.hpp"

TickMarks::TickMarks(const Vector2& origin, float radius, std::size_t tickCount, std::size_t accentInterval, float tickThickness, float tickScale, Color color)
    : m_origin{origin}
    , m_radius{radius}
    , m_count{tickCount}
    , m_accentInterval{accentInterval}
    , m_thickness{tickThickness}
    , m_scale{tickScale}
    , m_color{color}
    , m_degreesPerTick{Utils::DEGREES_PER_REVOLUTION / m_count}
{
    // The tick scale, which is a percentage of the radius, is used to compute
    // the white space between the origin and tick mark start. For the
    // rendering to work right, the tickScale must be <= 1.0f (the full radius).
    constexpr float lo_limit = 0.0f;
    constexpr float hi_limit = 1.0f + std::numeric_limits<float>::epsilon();

    if ((m_scale < lo_limit) || (m_scale> hi_limit)) {
        throw std::runtime_error("Tick scale must be 0.0f <= scale <= 1.0f");
    }
}

void TickMarks::Draw() const
{
    // Accent tick marks are twice as big as regular tick marks.
    constexpr float ACCENT_FACTOR = 2.0f;


    for (std::size_t tickMark = 0; tickMark < m_count; ++tickMark) {
        const float angle = (tickMark * m_degreesPerTick) + Utils::TWELVE_OCLOCK_ANGLE_OFFSET;

        // Appropriatly modify the tick mark on the accent ticks.
        float thickness = m_thickness;
        float scale     = m_scale;
        if ((tickMark % m_accentInterval) == 0) {
            thickness *= ACCENT_FACTOR;
            scale     *= ACCENT_FACTOR;
        }

        // Compute the end points of the tick mark line. The line starts inside
        // the radius by a factor of the scale and ends exactly on the radius.
        const float startRadius = m_radius * (1.0f - scale);

        const Vector2 start = Utils::CartesianEndpoint(m_origin, startRadius, angle);
        const Vector2 end   = Utils::CartesianEndpoint(m_origin, m_radius,    angle);

        DrawLineEx(start, end, thickness, m_color);
    }
}