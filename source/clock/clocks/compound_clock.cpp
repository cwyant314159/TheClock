#include "clocks/compound_clock.hpp"

#include "utils/constants.hpp"
#include "utils/time_point.hpp"

namespace {
    // Percentage scale of the subface relative to the clock radius
    constexpr float SUBFACE_SCALE = 0.25f;

    // Percentage offset of the subface center relative to the clock radius
    constexpr float SUBFACE_CENTER_OFFSET = 0.5f;
}

CompoundClock::CompoundClock(const Vector2& origin, float radius)
    : m_mainClock{origin, radius}
    , m_subClock{
        Vector2{origin.x, origin.y + (radius * SUBFACE_CENTER_OFFSET)},
        radius * SUBFACE_SCALE
    }
{
}

void CompoundClock::Update(const Utils::TimePoint& tp)
{
    m_mainClock.Update(tp);
    m_subClock.Update(tp);
}

void CompoundClock::Draw() const
{
    m_mainClock.DrawDial();
    m_subClock.Draw();
    m_mainClock.DrawHands();
}