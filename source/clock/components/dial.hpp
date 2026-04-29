#ifndef DIAL_HPP
#define DIAL_HPP

#include <cstdint>
#include <optional>
#include <vector>

extern "C" { 
    #include <raylib.h> 
}

#include "components/pin.hpp"

class Hand;
class TickMarks;

class Dial
{
public:
    Dial(const Vector2& origin, float radius, Color color);
    void DrawFace(const TickMarks& tickMarks) const;
    void DrawHands(const Hand& hand, std::optional<Pin> pin = std::nullopt) const;
    void DrawHands(const std::vector<Hand>& hands, std::optional<Pin> pin = std::nullopt) const;

private:
    const Vector2 m_origin;
    const float   m_radius;
    const Color   m_color;
};

#endif // DIAL_HPP