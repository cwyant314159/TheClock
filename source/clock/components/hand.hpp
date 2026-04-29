#ifndef HAND_HPP
#define HAND_HPP

extern "C" {
    #include <raylib.h>
}

class Hand
{
public:
    Hand(const Vector2& origin, float length, float thickness, Color color);
    void Draw() const;
    void SetAngle(float degrees);

private:
    const Vector2 m_origin;
    const float   m_length;
    const float   m_thickness;
    const Color   m_color;

    float m_angle;
};

#endif // HAND_HPP