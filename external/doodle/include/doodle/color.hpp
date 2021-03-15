/*--------------------------------------------------------------*
  Copyright (C) 2021 Rudy Castan

  This file is distributed WITHOUT ANY WARRANTY. See the file
  `License.md' for details.
*--------------------------------------------------------------*/
#pragma once


namespace doodle
{
    /**
     *  * \addtogroup Color
     *  Classes to represent colors.
     *  @{
     */

    /**
     * \class Color color.hpp doodle/color.hpp
     * \brief Color is a color represented with four unsigned bytes.
     *
     * It has the red, green, blue, and alpha color channels in the range of 0 to 255, where 255 is full intensity of
     * the color channel, 128 is roughly half intensity and 0 is no intensity of the color channel. The alpha channel
     * doesn't contribute light intensity but is used to define transparency. The alpha value also uses the range 0 to
     * 255 to set the amount of transparency. The value 0 defines the color as entirely transparent (it won't display),
     * the value 255 is entirely opaque, and the values between these extremes cause the colors to mix on the screen.
     */
    struct [[nodiscard]] Color
    {
    public:
        double red   = 0;
        double green = 0;
        double blue  = 0;
        double alpha = 255;

    public:
        /**
         * \brief The default color is black with full opacity.
         */
        constexpr Color() noexcept = default;
        /**
         * \brief Note that if only one value is provided to Color, it will be interpreted as a grayscale value. Add
         * a second value, and it will be used for alpha transparency.
         *
         * \param grey number specifying value between white and black
         * \param alpha alpha value relative to color range 0-255
         *
         */
        explicit constexpr Color(double grey, double alpha = 255) noexcept
            : red(grey), green(grey), blue(grey), alpha(alpha)
        {
        }
        /**
         * \brief When three values are specified, they are interpreted as RGB. Adding a fourth value applies
         * alpha transparency.
         *
         * \param red red value relative to the color range 0-255
         * \param green value relative to the color range 0-255
         * \param blue value relative to the color range 0-255
         * \param alpha alpha value relative to color range 0-255
         *
         */
        constexpr Color(double red, double green, double blue, double alpha = 255) noexcept
            : red(red), green(green), blue(blue), alpha(alpha)
        {
        }
    };

    /**
     * \class HexColor color.hpp doodle/color.hpp
     * \brief This is a helper class to easily represent an RGBA color as an int with hexadecimal notation.
     */
    class [[nodiscard]] HexColor
    {
    public:
        unsigned rgba = 0x000000ff;

        /**
         * \brief The default color is black with full opacity.
         */
        constexpr HexColor() noexcept = default;
        /**
         * \brief Implicitly convert from an unsigned int into a Hex Color.
         *
         * \param hex unsigned number to read as RGBA
         *
         */
        constexpr HexColor(unsigned hex) noexcept : rgba(hex) {}
        /**
         * \brief Implicitly convert from an int into a Hex Color
         *
         * \param hex int number to read as RGBA
         *
         */
        constexpr HexColor(int hex) noexcept : rgba(static_cast<unsigned>(hex)) {}
        /**
         * \brief Implicitly convert from a HexColor to a Color.
         *
         * This is really the reason why this class exists. This allows us to implicitly specify an RGBA color with a
         * single int and store it as a Color.
         */
        constexpr operator Color() const noexcept
        {
            return Color{static_cast<double>((rgba & 0xff000000) >> 24),
                static_cast<double>((rgba & 0x00ff0000) >> 16),
                static_cast<double>((rgba & 0x0000ff00) >> 8),
                         static_cast<double>((rgba & 0x000000ff) >> 0)};
        }
    };
    /** @} */
}
