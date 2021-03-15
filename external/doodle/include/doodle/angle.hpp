/*--------------------------------------------------------------*
  Copyright (C) 2021 Rudy Castan

  This file is distributed WITHOUT ANY WARRANTY. See the file
  `License.md' for details.
*--------------------------------------------------------------*/
#pragma once


namespace doodle
{
    /**
     *  * \defgroup Angles Angles
     *  Constants for common angles measured in radians. Also contains some helper functions related to angles.
     *  @{
     */
    /**
     * \brief \f$\pi\f$
     *
     * PI is a mathematical constant with the value ~3.1415. It is the ratio of the circumference of a
     * circle to its diameter. It is useful in combination with the trigonometric functions sin() and cos().
     */
    constexpr double PI = 3.1415926535897932384626433832795028;
    /**
     * \brief \f$\frac{\pi}{2}\f$
     *
     * HALF_PI is a mathematical constant with the value ~1.57079. It is half the ratio of the
     * circumference of a circle to its diameter. It is useful in combination with the trigonometric functions sin() and
     * cos().
     */
    constexpr double HALF_PI = PI / 2.0;
    /**
     * \brief \f$\frac{\pi}{4}\f$
     *
     * QUARTER_PI is a mathematical constant with the value ~0.7853982. It is one quarter the ratio of the circumference
     * of a circle to its diameter. It is useful in combination with the trigonometric functions sin() and cos().
     */
    constexpr double QUARTER_PI = PI / 4.0;
    /**
     * \brief \f$2\pi\f$
     *
     * TWO_PI is a mathematical constant with the value ~6.2831. It is twice the ratio of the
     * circumference of a circle to its diameter. It is useful in combination with the trigonometric functions sin() and
     * cos().
     */
    constexpr double TWO_PI = 2.0 * PI;

    /**
     * \brief Converts a degree measurement to its corresponding value in radians. Radians and degrees are two ways of
     * measuring the same thing. There are 360 degrees in a circle and \f$2\pi\f$ radians in a circle. For example,
     * \f$90^{\circ}=\frac{\pi}{2}=1.5707964\f$.
     *
     * \param angle_in_degrees an angle measured in degrees
     *
     * \return the corresponding angle measured in radians
     */
    constexpr double to_radians(double angle_in_degrees) noexcept { return angle_in_degrees * PI / 180.0; }
    /**
     * \brief Converts a radian measurement to its corresponding value in degrees. Radians and degrees are two ways of
     * measuring the same thing. There are 360 degrees in a circle and \f$2\pi\f$ radians in a circle. For example,
     * \f$90^{\circ}=\frac{\pi}{2}=1.5707964\f$.
     *
     * \param angle_in_radians an angle measured in radians
     *
     * \return the corresponding angle measured in degrees
     */
    constexpr double to_degrees(double angle_in_radians) noexcept { return angle_in_radians * 180.0 / PI; }

    /** @} */
}
