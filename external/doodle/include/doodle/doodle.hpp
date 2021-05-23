/*--------------------------------------------------------------*
  Copyright (C) 2021 Rudy Castan

  This file is distributed WITHOUT ANY WARRANTY. See the file
  `License.md' for details.
*--------------------------------------------------------------*/
#pragma once

#include <doodle/angle.hpp>
#include <doodle/color.hpp>
#include <doodle/drawing.hpp>
#include <doodle/environment.hpp>
#include <doodle/eventhook.hpp>
#include <doodle/image.hpp>
#include <doodle/input.hpp>
#include <doodle/noise.hpp>
#include <doodle/random.hpp>
#include <doodle/version.hpp>
#include <doodle/window.hpp>

/**
 * \mainpage
 *  \section Angles
 *      \subsection Constants
 *          - doodle::PI
 *          - doodle::HALF_PI
 *          - doodle::QUARTER_PI
 *          - doodle::TWO_PI
 *      \subsection Functions
 *          - to_degrees()
 *          - to_radians()
 *
 *  \section Color
 *      \subsection classes Creating Color
 *          - doodle::Color
 *          - doodle::HexColor
 *      \subsection function Setting Color
 *          - clear_background()
 *          - set_fill_color()
 *          - no_fill()
 *          - set_outline_color()
 *          - no_outline()
 *
 *  \section Shape
 *      \subsection drawing 2D Primitives
 *          - draw_ellipse()
 *          - draw_line()
 *          - draw_quad()
 *          - draw_rectangle()
 *          - draw_triangle()
 *      \subsection settings Attributes
 *          - set_ellipse_mode()
 *          - set_rectangle_mode()
 *          - set_frame_of_reference()
 *          - smooth_drawing()
 *          - no_smoothing()
 *          - set_outline_width()
 *          - push_settings()
 *          - pop_settings()
 *
 *  \section Environment
 *      \subsection globals Environment Globals
 *          - doodle::FrameCount
 *          - doodle::DeltaTime
 *          - doodle::ElapsedTime
 *          - doodle::Width
 *          - doodle::Height
 *      \subsection window Window
 *          - create_window()
 *          - is_window_closed()
 *          - update_window()
 *          - close_window()
 *          - set_window_title()
 *          - is_full_screen()
 *          - toggle_full_screen()
 *          - doodle::WindowIsFocused
 *          - on_window_resized()
 *          - set_callback_window_resized()
 *          - on_window_closed()
 *          - set_callback_window_closed()
 *          - on_window_focus_changed()
 *          - set_callback_window_focus_changed()
 *          - show_cursor()
 *
 *   \section Events
 *      \subsection Keyboard
 *          - doodle::KeyIsPressed
 *          - doodle::Key
 *          - on_key_pressed()
 *          - set_callback_key_pressed()
 *          - on_key_released()
 *          - set_callback_key_released()
 *      \subsection Mouse
 *          - doodle::MouseIsPressed
 *          - doodle::MouseButton
 *          - get_mouse_x()
 *          - get_mouse_y()
 *          - get_previous_mouse_x()
 *          - get_previous_mouse_y()
 *          - on_mouse_moved()
 *          - set_callback_mouse_moved()
 *          - on_mouse_pressed()
 *          - set_callback_mouse_pressed()
 *          - on_mouse_released()
 *          - set_callback_mouse_released()
 *          - on_mouse_wheel()
 *          - set_callback_mouse_wheel()
 *
 *   \section Image
 *      \subsection creating Creating Images
 *          - doodle::Image
 *          - capture_screenshot_to_image()
 *          - begin_drawing_to_image()
 *          - end_drawing_to_image()
 *      \subsection display Displaying Images
 *          - draw_image()
 *          - set_tint_color()
 *          - no_tint()
 *          - set_image_mode()
 *
 *  \section Typography
 *      - draw_text()
 *      - create_distance_field_bitmap_font()
 *      - set_font()
 *      - set_font_size()
 *      - set_font_fade_out_interval()
 *      - set_font_backdrop_fade_out_interval()
 *      - set_font_backdrop_offset()
 *
 *  \section Transform
 *      - apply_scale()
 *      - apply_rotate()
 *      - apply_translate()
 *      - apply_matrix()
 *
 *  \section Utility
 *      - seed_random()
 *      - random()
 *      - seed_noise()
 *      - noise()
 *      - set_noise_detail()
 *      - to_string()
 *      - to_wstring()
 *
 */
