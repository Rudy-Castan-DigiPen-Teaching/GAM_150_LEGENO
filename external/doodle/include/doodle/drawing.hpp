/*--------------------------------------------------------------*
  Copyright (C) 2021 Rudy Castan

  This file is distributed WITHOUT ANY WARRANTY. See the file
  `License.md' for details.
*--------------------------------------------------------------*/
#pragma once
#include <doodle/color.hpp>

#include <doodle/image.hpp>
#include <string>

namespace doodle
{
    /**
     *  * \addtogroup Color
     *  Functions to Set Color
     *  @{
     */
    /**
     * \brief Clear the background to black.
     *
     * The clear_background() function sets the color used for the background of the canvas. The default
     * background is black. This function is typically used within draw loop to clear the display window at the
     * beginning of each frame, but it can be used outside the loop to set the background on the first frame of
     * animation or if the background need only be set once.
     *
     *
     */
    void clear_background() noexcept;
    /**
     * \brief Clear the background to the specified HexColor
     *
     * The clear_background() function sets the color used for the background of the canvas. The default
     * background is black. This function is typically used within draw loop to clear the display window at the
     * beginning of each frame, but it can be used outside the loop to set the background on the first frame of
     * animation or if the background need only be set once.
     *
     * \param color HexColor to clear the screen to.
     *
     *
     */
    void clear_background(HexColor color) noexcept;
    /**
     * \brief Clear the background to the specified Color.
     *
     * The clear_background() function sets the color used for the background of the canvas. The default
     * background is black. This function is typically used within draw loop to clear the display window at the
     * beginning of each frame, but it can be used outside the loop to set the background on the first frame of
     * animation or if the background need only be set once.
     *
     * \param color Color to clear the screen to
     *
     *
     */
    void clear_background(Color color) noexcept;
    /**
     * \brief Clear the background to a grey color.
     *
     * The clear_background() function sets the color used for the background of the canvas. The default
     * background is black. This function is typically used within draw loop to clear the display window at the
     * beginning of each frame, but it can be used outside the loop to set the background on the first frame of
     * animation or if the background need only be set once.
     *
     * \param grey specifies a value between white and black
     * \param alpha optional opacity value of the background between 0-255. The default value is 255.
     *
     *
     */
    void clear_background(double grey, double alpha = 255) noexcept;
    /**
     * \brief Clear the background to a specified RGBA color.
     *
     * The clear_background() function sets the color used for the background of the canvas. The default
     * background is black. This function is typically used within draw loop to clear the display window at the
     * beginning of each frame, but it can be used outside the loop to set the background on the first frame of
     * animation or if the background need only be set once.
     *
     * \param red value between 0-255
     * \param green value between 0-255
     * \param blue value between 0-255
     * \param alpha optional opacity value of the background between 0-255. The default value is 255.
     *
     *
     */
    void clear_background(double red, double green, double blue, double alpha = 255) noexcept;

    /**
     * \brief Sets the color used to fill shapes to the specified HexColor.
     *
     * For example, if you run set_fill_color(HexColor{0xffaaeeff}), all shapes drawn after the fill command will be
     * filled with the color pink. The color space is RGBA, with each value in the range from 0 to 255.
     *
     * \param color HexColor to apply
     *
     */
    void set_fill_color(HexColor color) noexcept;
    /**
     * \brief Sets the color used to fill shapes to the specified Color.
     *
     * For example, if you run set_fill_color(Color{0,255,0,64}), all shapes drawn after the fill command will be
     * filled with a translucent green color. The color space is RGBA, with each value in the range from 0 to 255.
     *
     * \param color Color to apply
     *
     */
    void set_fill_color(Color color) noexcept;
    /**
     * \brief Sets the color used to fill shapes to a grey.
     *
     * For example, if you run set_fill_color(51), all shapes drawn after the fill command will be filled with the color
     * dark dark grey. The color space is RGBA, with each value in the range from 0 to 255.
     *
     * \param grey specifies a value between white and black
     * \param alpha optional opacity value of the background between 0-255. The default value is 255.
     *
     */
    void set_fill_color(double grey, double alpha = 255) noexcept;
    /**
     * \brief Sets the color used to fill shapes to the specified RGBA values.
     *
     * For example, if you run set_fill_color(138,43,226), all shapes drawn after the fill command will be filled with
     * the color purple. The color space is RGBA, with each value in the range from 0 to 255.
     *
     * \param red value between 0-255
     * \param green value between 0-255
     * \param blue value between 0-255
     * \param alpha optional opacity value of the background between 0-255. The default value is 255.
     *
     */
    void set_fill_color(double red, double green, double blue, double alpha = 255) noexcept;
    /**
     * \brief Disables filling geometry.
     *
     * If both no_outline() and no_fill() are called, nothing will be drawn to the screen.
     *
     */
    void no_fill() noexcept;
    /**
     * \brief Set the outline and lines of shapes to the specified HexColor.
     *
     * Sets the color used to draw lines and borders around shapes. The color space is RGBA, with each value in the
     * range from 0 to 255.
     *
     * \param color HexColor to apply
     *
     */
    void set_outline_color(HexColor color) noexcept;
    /**
     * \brief Set the outline and lines of shapes to the specified Color.
     *
     * Sets the color used to draw lines and borders around shapes. The color space is RGBA, with each value in the
     * range from 0 to 255.
     *
     * \param color Color to apply
     *
     */
    void set_outline_color(Color color) noexcept;
    /**
     * \brief Set the outline and lines of shapes to a grey color.
     *
     * Sets the color used to draw lines and borders around shapes. The color space is RGBA, with each value in the
     * range from 0 to 255.
     *
     * \param grey specifies a value between white and black
     * \param alpha optional opacity value of the background between 0-255. The default value is 255.
     *
     */
    void set_outline_color(double grey, double alpha = 255) noexcept;
    /**
     * \brief Set the outline and lines of shapes to an RGBA color.
     *
     * Sets the color used to draw lines and borders around shapes. The color space is RGBA, with each value in the
     * range from 0 to 255.
     *
     * \param red value between 0-255
     * \param green value between 0-255
     * \param blue value between 0-255
     * \param alpha optional opacity value of the background between 0-255. The default value is 255.
     *
     */
    void set_outline_color(double red, double green, double blue, double alpha = 255) noexcept;
    /**
     * \brief Disables drawing the outline.
     *
     * If both no_outline() and no_fill() are called, nothing will be drawn to the screen.
     *
     */
    void no_outline();
    /** @} */

    /**
     *  * \addtogroup Shape
     *  2D Primitive shape drawing and Attributes about the shapes.
     *  @{
     */

    /**
     * \brief Draws an ellipse (oval) to the screen.
     *
     * An ellipse with equal width and height is a circle. By default, the first two parameters set the location, and
     * the third and fourth parameters set the shape's width and height. If no height is specified, the value of width
     * is used for both the width and height. The origin may be changed with the set_ellipse_mode() function. By default
     * the (x,y) location is in the center of the ellipse.
     *
     * \param x x-coordinate of the ellipse.
     * \param y y-coordinate of the ellipse.
     * \param width width of the ellipse.
     * \param height height of the ellipse.
     *
     */
    void draw_ellipse(double x, double y, double width, double height = 0) noexcept;
    /**
     * \brief Draws a line (a direct path between two points) to the screen.
     *
     * To color a line, use the set_outline_color() function. A line cannot be filled, therefore the set_fill_color()
     * function will not affect the color of a line. Lines are drawn with a width of one pixel by default, but this can
     * be changed with the set_outline_width() function.
     *
     * \param x1 the x-coordinate of the first point
     * \param y1 the y-coordinate of the first point
     * \param x2 the x-coordinate of the second point
     * \param y2 the y-coordinate of the second point
     *
     */
    void draw_line(double x1, double y1, double x2, double y2) noexcept;
    /**
     * \brief Draw a quad.
     *
     * A quad is a quadrilateral, a four sided polygon. It is similar to a rectangle, but the angles between its edges
     * are not constrained to ninety degrees. The first pair of parameters (x1,y1) sets the first vertex and the
     * subsequent pairs should proceed clockwise or counter-clockwise around the defined shape.
     *
     * \param x1 the x-coordinate of the first point
     * \param y1 the y-coordinate of the first point
     * \param x2 the x-coordinate of the second point
     * \param y2 the y-coordinate of the second point
     * \param x3 the x-coordinate of the third point
     * \param y3 the y-coordinate of the third point
     * \param x4 the x-coordinate of the fourth point
     * \param y4 the y-coordinate of the forth point
     *
     */
    void draw_quad(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) noexcept;
    /**
     * \brief Draws a rectangle to the screen.
     *
     * A rectangle is a four-sided shape with every angle at ninety degrees. By default, the first two parameters set
     * the location of a corner, the third sets the width, and the fourth sets the height. The way these parameters are
     * interpreted, however, may be changed with the set_rectangle_mode() function. If the height is omitted then the
     * height will be set to the width, thus creating a square.
     *
     * \param x x-coordinate of the rectangle.
     * \param y y-coordinate of the rectangle.
     * \param width width of the rectangle.
     * \param height height of the rectangle.
     *
     */
    void draw_rectangle(double x, double y, double width, double height = 0) noexcept;
    /**
     * \brief Draw a triangle to the screen.
     *
     * A triangle is a plane created by connecting three points. The first two arguments specify the first point, the
     * middle two arguments specify the second point, and the last two arguments specify the third point.
     *
     * \param x1 the x-coordinate of the first point
     * \param y1 the y-coordinate of the first point
     * \param x2 the x-coordinate of the second point
     * \param y2 the y-coordinate of the second point
     * \param x3 the x-coordinate of the third point
     * \param y3 the y-coordinate of the third point
     *
     */
    void draw_triangle(double x1, double y1, double x2, double y2, double x3, double y3) noexcept;

    /**
     * \brief With set_ellipse_mode(), modifies the location from which ellipses are drawn by changing the way in which
     * parameters given to draw_ellipse() are interpreted.
     */
    enum class EllipseMode
    {
        /**
         * \brief Interprets the first two parameters of draw_ellipse() as the shape's center point
         */
        Center,
        /**
         * \brief Interprets the first two parameters of draw_ellipse() as the upper-left or bottom-left corner of the
         * shape in a left handed doodle::FrameOfReference and right handed doodle::FrameOfReference respectively
         */
        Corner
    };
    /**
     * \brief Modifies the location from which ellipses are drawn by changing the way in which parameters given to
     * draw_ellipse() are interpreted.
     *
     * The default mode is EllipseMode::CENTER, which interprets the first two parameters of draw_ellipse() as the
     * shape's center point, while the third and fourth parameters are its width and height.
     *
     * EllipseMode::CORNER
     * interprets the first two parameters of draw_ellipse() as the upper-left or bottom-left corner of the shape in a
     * left handed doodle::FrameOfReference and right handed doodle::FrameOfReference respectively, while the third and
     * fourth
     * parameters are its width and height.
     *
     * \param mode either CENTER or CORNER
     *
     */
    void set_ellipse_mode(EllipseMode mode) noexcept;
    /**
     * \brief With set_rectangle_mode(), modifies the location from which rectangles are drawn by changing the way in
     * which parameters given to draw_rectangle() are interpreted.
     */
    enum class RectMode
    {
        /**
         * \brief The default mode is RectMode::CORNER, which interprets the first two parameters of draw_rectangle() as
         * the upper-left or bottom-left corner of the shape in a left handed doodle::FrameOfReference and right handed
         * doodle::FrameOfReference respectively
         */
        Corner,
        /**
         * \brief RectMode::CENTER interprets the first two parameters of draw_rectangle() as the shape's center point.
         */
        Center
    };
    /**
     * \brief Modifies the location from which rectangles are drawn by changing the way in which parameters given to
     * draw_rectangle() are interpreted.
     *
     * The default mode is RectMode::CORNER, which interprets the first two parameters of draw_rectangle() as upper-left
     * or bottom-left corner of the shape in a left handed doodle::FrameOfReference and right handed
     * doodle::FrameOfReference respectively, while the third and fourth parameters are its width and height.
     *
     * RectMode::CENTER interprets the first two parameters of draw_rectangle() as the shape's center point, while the
     * third and fourth parameters are its width and height.
     *
     * \param mode either CORNER or CENTER
     *
     *
     */
    void set_rectangle_mode(RectMode mode) noexcept;
    /**
     * \brief Used to define the coordinate system you would like to reference.
     *
     */
    enum class FrameOfReference
    {
        /**
         * \brief The Origin (0,0) is always in the center of the screen. Positive x goes to the right and Positive y
         * goes up. This is the default reference frame.
         *
         * \verbatim
           W = Width, H = Height
                      (W/2,H/2)
                +--------o
                |        |
                |  0,0   |
                |        |
                o--------+
           (-W/2,-H/2)
           \endverbatim
         */
        RightHanded_OriginCenter,
        /**
         * \brief The Origin (0,0) is always in the bottom left of the screen. Positive x goes to the right and Positive
         * y goes up.
         *
         * \verbatim
           W = Width, H = Height
                       (W,H)
                +--------o
                |        |
                |        |
                |        |
                o--------+
              (0,0)
           \endverbatim
         */
        RightHanded_OriginBottomLeft,
        /**
         * \brief The Origin (0,0) is always in the top left of the screen. Positive x goes to the right and Positive y
         * goes down.
         *
         * \verbatim
           W = Width, H = Height
              (0,0)
                o--------+
                |        |
                |        |
                |        |
                +--------o
                       (W,H)
           \endverbatim
         */
        LeftHanded_OriginTopLeft
    };
    /**
     * \brief Change the coordinate system you would like to use when describing your primitives.
     *
     * \param frame_of_reference The coordinate system you would like to use.
     *
     */
    void set_frame_of_reference(FrameOfReference frame_of_reference) noexcept;
    /**
     * \brief Draws all geometry with smooth (anti-aliased) edges.
     *
     * Note that smooth_drawing() is active by default in; no_smoothing() can be used to disable smoothing of geometry,
     * images, and fonts.
     *
     */
    void smooth_drawing() noexcept;
    /**
     * \brief Draws all geometry with jagged (aliased) edges.
     *
     * Note that smooth_drawing() is active by default in; no_smoothing() can be used to disable smoothing of geometry,
     * images, and fonts.
     *
     */
    void no_smoothing() noexcept;
    /**
     * \brief Sets the width of the outline used for lines and the border around shapes. All widths are set in units of
     * pixels.
     *
     * \param line_width how thick to make lines
     *
     */
    void set_outline_width(double line_width) noexcept;

    /**
     * \brief The push_settings() function saves the current drawing style settings and transformations, while
     * pop_settings() restores these settings.
     *
     * Note that these functions are always used together. They allow you to change the style and transformation
     * settings and later return to what you had. When a new state is started with push_settings(), it builds on the
     * current style and transform information. The push_settings() and pop_settings() functions can be embedded to
     * provide more control.
     *
     * push_settings() stores information related to the current transformation (apply_scale(), apply_rotate(),
     * apply_translate(), apply_matrix()) state and style settings controlled by the following functions:
     * set_fill_color(), no_fill(), set_outline_color(), no_outline(), set_ellipse_mode(), set_rectangle_mode(),
     * smooth_drawing(), no_smoothing(), set_outline_width(), set_tint_color(), no_tint(), set_image_mode(),
     * set_font(), set_frame_of_reference()
     *
     */
    void push_settings() noexcept;
    /**
     * \brief The pop_settings() function restores to the previous style settings and transformations, while
     * push_settings() saves a new set these settings.
     *
     * Note that these functions are always used together. They allow you to change the style and transformation
     * settings and later return to what you had. When a new state is started with push_settings(), it builds on the
     * current style and transform information. The push_settings() and pop_settings() functions can be embedded to
     * provide more control.
     *
     * push_settings() stores information related to the current transformation (apply_scale(), apply_rotate(),
     * apply_translate(), apply_matrix()) state and style settings controlled by the following functions:
     * set_fill_color(), no_fill(), set_outline_color(), no_outline(), set_ellipse_mode(), set_rectangle_mode(),
     * smooth_drawing(), no_smoothing(), set_outline_width(), set_tint_color(), no_tint(), set_image_mode(),
     * set_font(), set_frame_of_reference()
     *
     */
    void pop_settings() noexcept;
    /** @} */

    /**
     *  * \addtogroup Typography
     *  Functions for drawing text using Distance Field Text Rendering.
     *  You can generate a Distance Field Bitmap Font using the [Hiero
     * tool](https://github.com/libgdx/libgdx/wiki/Hiero) [Here is a video](https://youtu.be/d8cfgcJR9Tk) that explains
     * Distance Field Text Rendering and how to generate the font with Hiero.
     *  @{
     */
    /**
     * \brief Draws wide character based text to the screen.
     *
     * Using wide characters allows us to draw characters not just for the English language but for other languages like
     * Korean too.
     *
     * A default font will be used unless a font is set with the set_font() function and a default size will be used
     * unless a font is set with set_font_size(). Change the color of the text with the set_fill_color() function.
     * Change the color of the backdrop with the set_outline_color() function.
     *
     * \param str the text to be displayed
     * \param x x-coordinate of text
     * \param y y-coordinate of text
     *
     * The following example built the distance field bitmap font with the [Hiero
     * tool](https://github.com/libgdx/libgdx/wiki/Hiero). Here is the [Hiero Setting
     * File](images\typography\examplefonts\Gaegu.hiero) configured to build with the [Gaegu
     * Font](https://fonts.google.com/specimen/Gaegu). This generated the relevant [Gaegu.fnt
     * file](images\typography\examplefonts\Gaegu.fnt) and it's partner [Gaegu.png
     * file](images\typography\examplefonts\Gaegu.png).
     *
     */
    void draw_text(const std::wstring& str, double x, double y) noexcept;
    /**
     * \brief Draws text to the screen.
     *
     * A default font will be used unless a font is set with the set_font() function and a default size will be used
     * unless a font is set with set_font_size(). Change the color of the text with the set_fill_color() function.
     * Change the color of the backdrop with the set_outline_color() function.
     *
     * \param str the text to be displayed
     * \param x x-coordinate of text
     * \param y y-coordinate of text
     *
     */
    void draw_text(const std::string& str, double x, double y) noexcept;
    /**
     * \brief Given a file path to a *.fnt file it will create a distance field bitmap font.
     *
     * It will parse that file to get all of the Bitmap information and create GPU texture instances of all the image
     * files listed. It assumes that the image files are in the same folder directory as the provided *.fnt file. It
     * will return a positive value on success and a negative value if it failed to parse the *.fnt file for whatever
     * reason.
     *
     * The default font, provided with doodle has a font ID of \f$0\f$ and is specified by doodle::DEFAULT_FONT_ID.
     *
     * The original bitmap font file definition comes from [AngleCode's
     * BMFont](http://www.angelcode.com/products/bmfont/). However BMFont does not generate distance field bitmap fonts,
     * so the suggested tool to use is the [Hiero tool](https://github.com/libgdx/libgdx/wiki/Hiero). Hiero can create
     * distance field bitmap fonts and save it in the AngelCode file format. [Here is a
     * video](https://youtu.be/d8cfgcJR9Tk) that explains Distance Field Text Rendering and how to generate the font
     * with Hiero.
     *
     * \param fnt_filepath Path to a fnt file in the BMFont text file format.
     * \return ID for the created font. Use this ID to actively select and use this font.
     *
     * The following example built the distance field bitmap font with the [Hiero
     * tool](https://github.com/libgdx/libgdx/wiki/Hiero). Here is the [Hiero Setting
     * File](images\typography\examplefonts\Gaegu.hiero) configured to build with the [Gaegu
     * Font](https://fonts.google.com/specimen/Gaegu). This generated the relevant [Gaegu.fnt
     * file](images\typography\examplefonts\Gaegu.fnt) and it's partner [Gaegu.png
     * file](images\typography\examplefonts\Gaegu.png).
     *
     *
     */
    int create_distance_field_bitmap_font(const std::filesystem::path& fnt_filepath) noexcept;
    /**
     * \brief Holds the ID value for the provided font that comes with doodle. \sa set_font()
     */
    constexpr int DEFAULT_FONT_ID = 0;
    /**
     * \brief Changes the font type to be used when drawing text.
     *
     * The default font provided with doodle is defined by doodle::DEFAULT_FONT_ID.
     *
     * \param font_id ID of a font that was previsouly created with create_distance_field_bitmap_font().
     *
     * The following example built the distance field bitmap font with the [Hiero
     * tool](https://github.com/libgdx/libgdx/wiki/Hiero). Here is the [Hiero Setting
     * File](images\typography\examplefonts\Gaegu.hiero) configured to build with the [Gaegu
     * Font](https://fonts.google.com/specimen/Gaegu). This generated the relevant [Gaegu.fnt
     * file](images\typography\examplefonts\Gaegu.fnt) and it's partner [Gaegu.png
     * file](images\typography\examplefonts\Gaegu.png).
     *
     */
    void set_font(int font_id) noexcept;
    /**
     * \brief Sets the current font size. This size will be used in all subsequent calls to the draw_text() function.
     * \param font_size the desired font size
     *
     *
     */
    void set_font_size(double font_size) noexcept;
    /**
     * \brief Defines the distance interval to draw font characters and how to fade them out from opaque to translucent.
     *
     * The inside_distance defines the distance that is considered completely inside a font character. The
     * outside_distance defines the distance that is considered completely outside a font character. The distance value
     * that are in between theses two values will be smoothed out.
     *
     * The distance is measured in a normalized space, so must be between [0,1]. Values outside of this will be clamped.
     * If the given outside_distance is less than the inside_distance it will be replaced to match the inside_distance.
     *
     * ![Illustration of the normalized space with the letter S](images\typography\explain\fadout_intervals.png)
     *
     * In this example the inside_distance is 0.5 and the outside_distance is 0.6. Anything inside 0.5 is considered
     * completely inside the letter and will be colored opaquely. Anything outside 0.6 is considered completely outside
     * and will be colored transparently.
     *
     * \param inside_distance The normalized distance the defines what is completely **inside** a character font.
     * Clamped to [0,1].
     * \param outside_distance The normalized distance the defines what is completely **outside** a
     * character font. Clamped to [0,1].
     *
     */
    void set_font_fade_out_interval(double inside_distance, double outside_distance) noexcept;
    /**
     * \brief Defines the distance interval to draw the backdrop of font characters and how to fade them out from opaque
     * to translucent.
     *
     * The inside_distance defines the distance that is considered completely inside a font character. The
     * outside_distance defines the distance that is considered completely outside a font character. The distance value
     * that are in between theses two values will be smoothed out. It is the same logic as set_font_fade_out_interval(),
     * however this will draw the character based off of the outline color and will be behind the fill colored part.
     *
     * The distance is measured in a normalized space, so must be between [0,1]. Values outside of this will be clamped.
     * If the given outside_distance is less than the inside_distance it will be replaced to match the inside_distance.
     *
     * ![Illustration of the normalized space with the letter S](images\typography\explain\fadout_intervals.png)
     *
     * In this example the inside_distance is 0.5 and the outside_distance is 0.6. Anything inside 0.5 is considered
     * completely inside the letter and will be colored opaquely. Anything outside 0.6 is considered completely outside
     * and will be colored transparently.
     *
     * \param inside_distance The normalized distance the defines what is completely **inside** a character font for the
     * backdrop. Clamped to [0,1].
     * \param outside_distance The normalized distance the defines what is completely **outside** a character font for
     * the backdrop. Clamped to [0,1].
     *
     */
    void set_font_backdrop_fade_out_interval(double inside_distance, double outside_distance) noexcept;
    /**
     * \brief Repositions the backdrop of the font characters. Useful for creating a custom drop shadow effect.
     *
     * The distance to offset the backdrop is measured in texels relative to the image defining the Bitmap Font. The
     * texel coordinate system is left handed where the origin is the very top left and positive y goes down.
     *
     * \param texel_x How far to horizontally offset the backdrop character in texels
     * \param texel_y How far to vertically offset the backdrop character in texels
     *
     */
    void set_font_backdrop_offset(double texel_x, double texel_y) noexcept;
    /** @} */


    /**
     *  * \addtogroup Image
     *  Functions for drawing images and taking a screenshot.
     *  @{
     */
    /**
     * \brief Captures a screenshot of the whole screen.
     *
     * \return The screenshot is saved into an Image object, which can be used to save it to a file if desired.
     *
     */
    Image capture_screenshot_to_image();

    /**
     * \brief Captures a screenshot of a subsection of the screen.
     *
     * Useful if you only want to save a portion of the screen.
     *
     * The coordinates you give are assumed to be in the RightHanded_OriginBottomLeft frame of reference.
     *
     * \param left_x x-coordinate for the left part of the box containing the screenshot
     * \param bottom_y y-coordinate for the bottom part of the box containing the screenshot
     * \param pixels_width width of the box containing the screenshot
     * \param pixels_height height of the box containing the screenshot
     * \return The screenshot is saved into an Image object, which can be used to save it to a file if desired.
     *
     */
    Image capture_screenshot_to_image(int left_x, int bottom_y, int pixels_width, int pixels_height) noexcept;

    /**
     * \brief Draw an entire image to the screen.
     *
     * The width and height of the image will be based off of the image width and image height.
     *
     * \param image image object to draw
     * \param x x-coordinate of the rectangle to draw the image.
     * \param y y-coordinate of the rectangle to draw the image.
     *
     *
     */
    void draw_image(const Image& image, double x, double y) noexcept;
    /**
     * \brief Draw an entire image to the screen and resize it to a custom size.
     * \param image image object to draw
     * \param x x-coordinate of the rectangle to draw the image.
     * \param y y-coordinate of the rectangle to draw the image.
     * \param width how wide to draw the image
     * \param height how tall to draw the image
     *
     *
     */
    void draw_image(const Image& image, double x, double y, double width, double height) noexcept;
    /**
     * \brief Draw a subsection of the image to the screen.
     *
     * The subsection is defined is defined by the box
     *
     * \verbatim
      Image
        (0,0)
          +---------------------------------------------------------------------+
          |                                                                     |
          |(texel_x,texel_y)                                                    |
          |        o--------------------------------+                           |
          |        |                                |                           |
          |        |                                |                           |
          |        |                                |                           |
          |        |                                |                           |
          |        |                                |                           |
          |        +--------------------------------o                           |
          |                           (texel_x+width,texel_y+height)            |
          |                                                                     |
          |                                                                     |
          |                                                                     |
          +---------------------------------------------------------------------+
                                                                    (image_width,image_height)
       \endverbatim
     *
     * \param image image object to draw
     * \param x x-coordinate of the rectangle to draw the image.
     * \param y y-coordinate of the rectangle to draw the image.
     * \param width how wide to draw the image
     * \param height how tall to draw the image
     * \param texel_x Horizontally, where in image to start reading colors from the image. 0 is the far left and
     * image width is the far right.
     * \param texel_y Vertically, where in image to start reading colors from the
     * image. 0 is the far top and image height is the far bottom.
     *
     *
     */
    void draw_image(const Image& image, double x, double y, double width, double height, int texel_x,
                    int texel_y) noexcept;
    /**
     * \brief Draw a subsection of the image to the screen.
     *
     * The subsection is defined is defined by the box
     *
     * \verbatim
      Image
    (0,0)
      +---------------------------------------------------------------------+
      |                                                                     |
      |(texel_x,texel_y)                                                    |
      |        o--------------------------------+                           |
      |        |                                |                           |
      |        |                                |                           |
      |        |                                |                           |
      |        |                                |                           |
      |        |                                |                           |
      |        +--------------------------------o                           |
      |                     (texel_x+texel_width,texel_y+texel_height)      |
      |                                                                     |
      |                                                                     |
      |                                                                     |
      +---------------------------------------------------------------------+
                                                                (image_width,image_height)
       \endverbatim
     *
     * \param image image object to draw
     * \param x x-coordinate of the rectangle to draw the image.
     * \param y y-coordinate of the rectangle to draw the image.
     * \param width how wide to draw the image
     * \param height how tall to draw the image
     * \param texel_x Horizontally, where in image to start reading colors from the image. 0 is the far left and
     * image width is the far right.
     * \param texel_y Vertically, where in image to start reading colors from the
     * image. 0 is the far top and image height is the far bottom.
     * \param texel_width width of image subsection to read the colors from
     * \param texel_height height of image subsection to read the colors from
     *
     *
     */
    void draw_image(const Image& image, double x, double y, double width, double height, int texel_x, int texel_y,
                    int texel_width, int texel_height) noexcept;
    /**
     * \brief Sets the fill value for displaying images to the specified HexColor.
     *
     * Images can be tinted to specified colors or made transparent by including an alpha value.
     *
     * \param color HexColor to apply to images
     *
     *
     */
    void set_tint_color(HexColor color) noexcept;
    /**
     * \brief Sets the fill value for displaying textures to the specified Color.
     *
     * Textures can be tinted to specified colors or made transparent by including an alpha value.
     *
     * \param color Color to apply to textures
     *
     *
     */
    void set_tint_color(Color color) noexcept;
    /**
     * \brief Sets the fill value for displaying textures to the specified grey color.
     *
     * Textures can be tinted to specified colors or made transparent by including an alpha value.
     *
     * \param grey specifies a value between white and black
     * \param alpha optional opacity value of the background between 0-255. The default value is 255.
     *
     *
     */
    void set_tint_color(double grey, double alpha = 255) noexcept;
    /**
     * \brief Sets the fill value for displaying textures to the specified RGBA color.
     *
     * Textures can be tinted to specified colors or made transparent by including an alpha value.
     *
     * \param red value between 0-255
     * \param green value between 0-255
     * \param blue value between 0-255
     * \param alpha optional opacity value of the background between 0-255. The default value is 255.
     *
     *
     */
    void set_tint_color(double red, double green, double blue, double alpha = 255) noexcept;
    /**
     * \brief Removes the current fill value for displaying images and reverts to displaying textures with their
     *        original colors.
     *
     *
     */
    void no_tint() noexcept;
    /**
     * \brief Modifies the location from which textures are drawn by changing the way in which parameters given to
     * draw_image() are interpreted.
     *
     * The default mode is RectMode::CORNER, which interprets the first two parameters of draw_image() as upper-left
     * or bottom-left corner of the shape in a left handed doodle::FrameOfReference and right handed
     * doodle::FrameOfReference respectively, while the third and fourth parameters are its width and height.
     *
     * RectMode::CENTER interprets the first two parameters of draw_image() as the shape's center point, while the
     * third and fourth parameters are its width and height.
     *
     * \param mode either CORNER or CENTER
     *
     */
    void set_image_mode(RectMode mode) noexcept;
    /** @} */

    /**
     *  * \addtogroup Transform
     *  Functions for transforming shapes
     *  @{
     */
    /**
     * \brief Uniformly increases or decreases the size of a shape by expanding and contracting vertices.
     *
     * Objects always scale from their relative origin to the coordinate system. Scale values are specified as decimal
     * percentages. For example, the function call apply_scale(2.0) increases the dimension of a shape by 200%.
     *
     * Transformations apply to everything that happens after and subsequent calls to the function multiply the effect.
     * For example, calling apply_scale(2.0) and then apply_scale(1.5) is the same as apply_scale(3.0). The
     * transformation is reset when update_window() is called.
     *
     * \param scale percent to scale the object
     *
     */
    void apply_scale(double scale) noexcept;
    /**
     * \brief  Increases or decreases the size of a shape by expanding and contracting vertices.
     *
     * Objects always scale from their relative origin to the coordinate system. Scale values are specified as decimal
     * percentages. For example, the function call apply_scale(2.0, 0.5) increases the dimension of a shape horizontally
     * by 200% and vertically bu 50%.
     *
     * Transformations apply to everything that happens after and subsequent calls to the function multiply the effect.
     * For example, calling apply_scale(2.0, 1.0) and then apply_scale(1.5, 2.0) is the same as apply_scale(3.0, 2.0).
     * The transformation is reset when update_window() is called.
     *
     * \param scale_x percentage to scale the object in the x-axis
     * \param scale_y percentage to scale the object in the y-axis
     *
     *
     */
    void apply_scale(double scale_x, double scale_y) noexcept;
    /**
     * \brief Rotates a shape the amount specified by the angle in radians.
     *
     * Objects are always rotated around their relative position to the origin. If the doodle::FrameOfReference is
     * right-handed then positive angles rotate counter-clockwise and if it is left-handed then positive angles rotate
     * clockwise. Transformations apply to everything that happens after and subsequent calls to the function
     * accumulates the effect. For example, calling apply_rotate(HALF_PI) and then apply_rotate(HALF_PI) is the same as
     * apply_rotate(PI). All transformations are reset when update_window() is called.
     *
     * Technically, apply_rotate() multiplies the current transformation matrix by a rotation matrix. This function can
     * be further controlled by the push_settings() and pop_settings().
     *
     * \param angle_in_radians the angle of rotation
     *
     */
    void apply_rotate(double angle_in_radians) noexcept;
    /**
     * \brief Specifies an amount to displace objects within the display window.
     *
     * The x parameter specifies left/right translation, the y parameter specifies up/down translation.
     *
     * Transformations are cumulative and apply to everything that happens after and subsequent calls to the function
     * accumulates the effect. For example, calling apply_translate(50, 0) and then apply_translate(20, 0) is the same
     * as apply_translate(70, 0). All transformations are reset when update_window() is called. This function can be
     * further controlled by the push_settings() and pop_settings().
     *
     * \param translate_x left/right translation
     * \param translate_y up/down translation
     *
     */
    void apply_translate(double translate_x, double translate_y) noexcept;
    /**
     * \brief Multiplies the current matrix by the one specified through the parameters.
     *
     * This is a powerful operation that can perform the equivalent of translate, scale, shear and rotate all at once.
     * You can learn more about transformation matrices on
     * [Wikipedia](https://en.wikipedia.org/wiki/Transformation_matrix).
     *
     * The naming of the arguments here follows the naming of the [WHATWG
     * specification](https://html.spec.whatwg.org/multipage/canvas.html#dom-context-2d-transform) and corresponds to a
     * transformation matrix of the form:
     *
     * \f$ \begin{bmatrix} a & c & e \\ b & d & f \\ 0 & 0 & 1 \end{bmatrix} \f$
     *
     * \param a 1st Column 1 Row
     * \param b 1st Column 2nd Row
     * \param c 2nd Column 1st  Row
     * \param d 2nd Column 2nd Row
     * \param e 3rd Column 1st Row
     * \param f 3rd Column 2nd Row
     *
     */
    void apply_matrix(double a, double b, double c, double d, double e, double f) noexcept;

    /** @} */

    /**
     *  * \addtogroup Image
     *  Functions for drawing to an Image.
     *  @{
     */

    /**
     * \brief Redirect all draw command to draw to an image
     * \param image_width The desired width of the image
     * \param image_height The desired height of the image
     * \param apply_antialiasing Should multi-sample anti-aliasing be applied?
     *
     * \include begin_drawing_to_image.cpp
     *
     */
    void begin_drawing_to_image(int image_width, int image_height, bool apply_antialiasing = true);

    /**
     * \brief End a session of drawing to an image
     * \param smooth_texture Should the texture use a smooth filtering when being drawn
     * \return An Image representing what was drawn.
     *
     * \include end_drawing_to_image.cpp
     *
     */
    Image end_drawing_to_image(bool smooth_texture = false);

    /** @} */

}
