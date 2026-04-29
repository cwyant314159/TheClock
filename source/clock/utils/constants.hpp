#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace Utils {

/**
 * @brief Degrees per revolution of a circle
 */
inline constexpr float DEGREES_PER_REVOLUTION{360.0f};

/**
 * @brief 12'oclock angle offset
 * 
 * To make working with the angle of clock hands on a dial easier, it is
 * helpful to have 12'oclock be the 0 degree position. Graphics libraries
 * however tend to make 0 degrees the positive x-axis. This -90 degree offset
 * can be used to convert 12'oclock relative angles (in degrees) to x-axis
 * relative angles (in degrees).
 */
inline constexpr float TWELVE_OCLOCK_ANGLE_OFFSET{-90.0f};

} // namespace Utils

#endif // CONSTANTS_HPP