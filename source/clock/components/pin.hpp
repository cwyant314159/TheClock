#ifndef PIN_HPP
#define PIN_HPP

extern "C" { 
    #include <raylib.h> 
}

class Pin
{
public:
    Pin(const Vector2& origin, float radius, Color color);
    void Draw() const;

private:
    const Vector2 m_origin;
    const float   m_radius;
    const Color   m_color;
};

#endif // PIN_HPP