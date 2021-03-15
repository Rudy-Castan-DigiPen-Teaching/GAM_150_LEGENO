/*--------------------------------------------------------------*
  Copyright (C) 2021 Rudy Castan

  This file is distributed WITHOUT ANY WARRANTY. See the file
  `License.md' for details.
*--------------------------------------------------------------*/
#pragma once

#include <doodle/eventhook.hpp>

#include <functional>
#include <string>

namespace doodle
{
    /**
     *  * \addtogroup Environment
     *  Window related functions, The window hosts the doodle.
     *  @{
     */

    /**
     * \brief Create a default window.
     *
     * Creates a window in the middle of the screen, roughly 75% the width & height of the monitor.
     *
     * \return True if window was create, false otherwise
     *
     * On a 1920x1080 monitor:
     */
    bool create_window() noexcept;
    /**
     * \brief Create a default window with a custom window title
     * \param title custom title for the window
     * \return True if window was create, false otherwise
     *
     * On a 1920x1080 monitor:
     */
    bool create_window(const std::string& title) noexcept;
    /**
     * \brief Create a window with a desired screen size.
     * \param desired_width how wide you'd like the screen space to be
     * \param desired_height how tall you'd like the screen space to be
     * \return True if window was create, false otherwise
     *
     */
    bool create_window(int desired_width, int desired_height) noexcept;
    /**
     * \brief Create a window with a custom window title and a desired screen size.
     * \param title custom title for the window
     * \param desired_width how wide you'd like the screen space to be
     * \param desired_height how tall you'd like the screen space to be
     * \return True if window was create, false otherwise
     *
     */
    bool create_window(const std::string& title, int desired_width, int desired_height) noexcept;

    /**
     * \brief Create a window with a custom window title and a desired screen size.
     * \param title custom title for the window
     * \param desired_width how wide you'd like the screen space to be
     * \param desired_height how tall you'd like the screen space to be
     * \param screen_x with respect to the top left of the window, defines where to position the window on the monitor
     * screen
     * \param screen_y with respect to the top left of the window, defines where to position the window on the
     * monitor screen
     * \return True if window was create, false otherwise
     *
     */
    bool create_window(const std::string& title, int desired_width, int desired_height, int screen_x,
                       int screen_y) noexcept;

    /**
     * \brief Is the window closed?
     *
     * Should be used to drive the applications main loop. If the user closes the window through the operating system
     * then you need to end your loop.
     *
     * \return true if the window closed, false if it is still open
     *
     */
    bool is_window_closed() noexcept;

    /**
     * \brief Update the doodle application.
     *
     * This needs to be called once every frame of the main loop. This is where events and drawing logic is updated.
     *
     */
    void update_window() noexcept;

    /**
     * \brief Programmatically close the window.
     *
     */
    void close_window() noexcept;

    /**
     * \brief Set a new title for the window
     * \param new_title a new title for the window
     *
     */
    void set_window_title(const std::string& new_title) noexcept;
    /**
     * \brief Is the window a fullscreen window?
     * \return true if the window is fullscreen, false if it is windowed
     *
     */
    bool is_full_screen() noexcept;
    /**
     * \brief Switch back and forth between fullscreen and windowed mode.
     *
     */
    void toggle_full_screen() noexcept;
    /**
     * \brief Confirms if the window a doodle program is in is "focused," meaning that the doodle will accept mouse or
     * keyboard input. This variable is "true" if the window is focused and "false" if not.
     *
     */
    extern bool WindowIsFocused;
    /**
     * \brief The provided callback function is called whenever the window is resized by the user.
     *
     * It takes in a [std::function](https://en.cppreference.com/w/cpp/utility/functional/function) with a signature of
     * something that returns nothing and takes in two integers. Something like
     */
    void set_callback_window_resized(std::function<void(int, int)>&& callback) noexcept;
    /**
     * \brief The provided callback function will be called when the user uses the OS to close the window.
     *
     * It takes in a [std::function](https://en.cppreference.com/w/cpp/utility/functional/function) with a signature of
     * something that returns nothing and takes in nothing. Something like
     *
     * Prints the following:
     */
    void set_callback_window_closed(std::function<void(void)>&& callback) noexcept;
    /**
     * \brief THe provided callback function will be called when the window gains or loses focus.
     *
     * It takes in a [std::function](https://en.cppreference.com/w/cpp/utility/functional/function) with a signature of
     * something that returns nothing and takes in a boolean. Something like
     */
    void set_callback_window_focus_changed(std::function<void(bool)>&& callback) noexcept;

    /**
     * \brief This function will allow you to hide or show the mouse cursor.
     * \param show_it should the cursor be visible or not
     *
     */
    void show_cursor(bool show_it = true) noexcept;

}


/**
 *  * \addtogroup Environment
 *  Window related functions, The window hosts the doodle.
 *  @{
 */
/**
 * \brief The declaration of the optional on_window_resized function to implement in your doodle program.
 *
 * If you define the function definition of this function then it will be called when the window resizes.
 *
 * \param new_width  Width of the new window resolution
 * \param new_height Height of the new window resolution
 *
 */
EVENT_HOOK void on_window_resized(int new_width, int new_height);
/**
 * \brief The declaration of the optional on_window_closed function to implement in your doodle program.
 *
 * If you define the function definition of this function then it will be called when the window closes.
 *
 *
 * Prints the following:
 *
 */
EVENT_HOOK void on_window_closed();
/**
 * \brief The declaration of the optional on_window_focus_changed function to implement in your doodle program.
 *
 * If you define the function definition of this function then it will be called when the window changes it's focus.
 *
 * \param is_focused true when window has focus and false otherwise
 *
 *
 */
EVENT_HOOK void on_window_focus_changed(bool is_focused);
/** @} */
