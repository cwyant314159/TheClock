#include "utils/conversions.hpp"

#include <complex>

Vector2 Utils::CartesianEndpoint(const Vector2& origin, float length, float angleDegrees)
{
    // Compute the endpoint by abusing the Complex type to do polar to
    // rectangular conversions.
    const std::complex<float> offsetPolar = std::polar(length, angleDegrees * DEG2RAD);
    return Vector2{
        .x = origin.x + offsetPolar.real(),
        .y = origin.y + offsetPolar.imag()
    };
}