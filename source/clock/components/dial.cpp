#include "components/dial.hpp"

#include "components/hand.hpp"
#include "components/tick_marks.hpp"

Dial::Dial(const Vector2& origin, float radius, Color color)
    : m_origin{origin}
    , m_radius{radius}
    , m_color{color}
{}

void Dial::DrawFace(const TickMarks& tickMarks) const
{
    DrawCircleV(m_origin, m_radius, m_color);
    tickMarks.Draw();
}

void Dial::DrawHands(const Hand& hand, std::optional<Pin> pin) const
{
    hand.Draw();
    
    if (pin.has_value()) {
        pin.value().Draw();
    }
}

void Dial::DrawHands(const std::vector<Hand>& hands, std::optional<Pin> pin) const
{
    for (const Hand& h : hands) {
        h.Draw();
    }

    if (pin.has_value()) {
        pin.value().Draw();
    }
}