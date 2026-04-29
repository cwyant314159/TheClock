#ifndef CONVERSIONS_HPP
#define CONVERSIONS_HPP

extern "C" {
    #include <raylib.h>
}

namespace Utils {

/**
 * @brief Compute the x/y coordinates of the end of a line segment
 * 
 * @param origin Segement origin point
 * @param radius Radius (length) of the segment
 * @param angleDegrees Angle relative to the x-axis in degrees
 * @return Vector2 x/y coordinates of the endpoint
 */
Vector2 CartesianEndpoint(const Vector2& origin, float length, float angleDegrees);

} // namespace Utils

#endif // CONVERSIONS_HPP