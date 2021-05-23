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
    enum class MouseButtons
    {
        None,   //!< Unhandled Button
        Left,   //!< Left Mouse Button
        Middle, //!< Middle Mouse Button
        Right,  //!< Right Mouse Button
        Count   //!< the total number of mouse button keys
    };

    enum class KeyboardButtons
    {
        None,         //!< Unhandled key
        _0,           //!< The 0 key
        _1,           //!< The 1 key
        _2,           //!< The 2 key
        _3,           //!< The 3 key
        _4,           //!< The 4 key
        _5,           //!< The 5 key
        _6,           //!< The 6 key
        _7,           //!< The 7 key
        _8,           //!< The 8 key
        _9,           //!< The 9 key
        A,            //!< The A key
        B,            //!< The B key
        C,            //!< The C key
        D,            //!< The D key
        E,            //!< The E key
        F,            //!< The F key
        G,            //!< The G key
        H,            //!< The H key
        I,            //!< The I key
        J,            //!< The J key
        K,            //!< The K key
        L,            //!< The L key
        M,            //!< The M key
        N,            //!< The N key
        O,            //!< The O key
        P,            //!< The P key
        Q,            //!< The Q key
        R,            //!< The R key
        S,            //!< The S key
        T,            //!< The T key
        U,            //!< The U key
        V,            //!< The V key
        W,            //!< The W key
        X,            //!< The X key
        Y,            //!< The Y key
        Z,            //!< The Z key
        NumPad_0,     //!< The numpad 0 key
        NumPad_1,     //!< The numpad 1 key
        NumPad_2,     //!< The numpad 2 key
        NumPad_3,     //!< The numpad 3 key
        NumPad_4,     //!< The numpad 4 key
        NumPad_5,     //!< The numpad 5 key
        NumPad_6,     //!< The numpad 6 key
        NumPad_7,     //!< The numpad 7 key
        NumPad_8,     //!< The numpad 8 key
        NumPad_9,     //!< The numpad 9 key
        Escape,       //!< The Escape key
        Control,      //!< The Control key
        Shift,        //!< The Shift key
        CapsLock,     //!< The Caps Lock key
        LeftSystem,   //!< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
        RightSystem,  //!< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
        Menu,         //!< The Menu key
        LeftBracket,  //!< The [ key
        RightBracket, //!< The ] key
        Semicolon,    //!< The ; key
        Comma,        //!< The , key
        Period,       //!< The . key
        Quote,        //!< The ' key
        Slash,        //!< The / key
        Backslash,    //!< The \ key
        Tilde,        //!< The ~ key
        Equal,        //!< The = key
        Hyphen,       //!< The - key (hyphen)
        Space,        //!< The Space key
        Enter,        //!< The Enter/Return keys
        Backspace,    //!< The Backspace key
        Tab,          //!< The Tabulation key
        PageUp,       //!< The Page up key
        PageDown,     //!< The Page down key
        End,          //!< The End key
        Home,         //!< The Home key
        PrintScreen,  //!< The Print Screen key
        Insert,       //!< The Insert key
        Delete,       //!< The Delete key
        Add,          //!< The + key
        Subtract,     //!< The - key (minus, usually from numpad)
        Multiply,     //!< The * key
        Divide,       //!< The / key
        Left,         //!< Left arrow
        Right,        //!< Right arrow
        Up,           //!< Up arrow
        Down,         //!< Down arrow
        F1,           //!< The F1 key
        F2,           //!< The F2 key
        F3,           //!< The F3 key
        F4,           //!< The F4 key
        F5,           //!< The F5 key
        F6,           //!< The F6 key
        F7,           //!< The F7 key
        F8,           //!< The F8 key
        F9,           //!< The F9 key
        Pause,        //!< The Pause key
        Count         //!< the total number of keyboard keys
    };


    /**
     * \addtogroup Utility
     *  Helper functions to convert the input enums to strings.
     *  @{
     */
    /**
     * \brief Convert MouseButtons enum to std::string
     * \param button mouse button
     * \return The name of the button as a std::string
     */
    std::string to_string(MouseButtons button) noexcept;
    /**
     * \brief Convert KeboardButtons enum to std::string
     * \param button keyboard button
     * \return The name of the button as a std::string
     */
    std::string to_string(KeyboardButtons button) noexcept;
    /**
     * \brief Convert MouseButtons enum to std::wstring
     * \param button mouse button
     * \return The name of the button as a std::wstring
     */
    std::wstring to_wstring(MouseButtons button) noexcept;
    /**
     * \brief Convert KeboardButtons enum to std::wstring
     * \param button keyboard button
     * \return The name of the button as a std::wstring
     */
    std::wstring to_wstring(KeyboardButtons button) noexcept;
    /** @} */

    /**
     *  * \addtogroup Events
     *  global variables related to input Events
     *  @{
     */
    /**
     * \brief The boolean system variable MouseIsPressed is true if the mouse is pressed and false if not.
     *
     *
     */
    extern bool MouseIsPressed;
    /**
     * \brief The boolean system variable KeyIsPressed is true if any key is pressed and false if no keys are pressed.
     *
     *
     */
    extern bool KeyIsPressed;
    /**
     * \brief The system variable key always contains the value of the most recent key on the keyboard that was typed.
     *
     *
     */
    extern KeyboardButtons Key;
    /**
     * \brief doodle automatically tracks if the mouse button is pressed and which button is pressed. The value of
     * the system variable MouseButton is either LEFT, RIGHT, or CENTER depending on which button was pressed last.
     *
     *
     */
    extern MouseButtons MouseButton;
    /** @} */
    /**
     * \addtogroup Events
     *  You can register callback functions so you can immediately respond to input events. Also provides helper
     * functions to get the mouse position.
     *  @{
     */
    /**
     * \brief Get the mouse's X position relative to the currently set doodle::FrameOfReference
     * \return the current horizontal position of the mouse, relative to the currently set doodle::FrameOfReference
     *
     */
    int get_mouse_x() noexcept;

    /**
     * \brief Get the mouse's Y position relative to the currently set doodle::FrameOfReference
     * \return the current vertical position of the mouse, relative to the currently set doodle::FrameOfReference
     *
     */
    int get_mouse_y() noexcept;
    /**
     * \brief Get the previous mouse's X position relative to the currently set doodle::FrameOfReference
     *
     * \return the previous horizontal position of the mouse, relative to the currently set doodle::FrameOfReference
     *
     */
    int get_previous_mouse_x() noexcept;
    /**
     * \brief Get the previous mouse's Y position relative to the currently set doodle::FrameOfReference
     * \return Get the previous mouse's Y position relative to the currently set doodle::FrameOfReference
     *
     */
    int get_previous_mouse_y() noexcept;
    /**
     * \brief The provided callback function is called once every time a key is pressed.
     *
     * It takes in a [std::function](https://en.cppreference.com/w/cpp/utility/functional/function) with a signature of
     * something that returns nothing and takes in a doodle::KeyboardButtons. Something like
     */
    void set_callback_key_pressed(std::function<void(KeyboardButtons)>&& callback) noexcept;
    /**
     * \brief The provided callback function is called once every time a key is released.
     *
     * It takes in a [std::function](https://en.cppreference.com/w/cpp/utility/functional/function) with a signature of
     * something that returns nothing and takes in a doodle::KeyboardButtons. Something like
     */
    void set_callback_key_released(std::function<void(KeyboardButtons)>&& callback) noexcept;
    /**
     * \brief The provided callback function is called every time the mouse moves.
     *
     * It takes in a [std::function](https://en.cppreference.com/w/cpp/utility/functional/function) with a signature of
     * something that returns nothing and takes in a two integers. Something like
     */
    void set_callback_mouse_moved(std::function<void(int, int)>&& callback) noexcept;
    /**
     * \brief The provided callback is called whenever a mouse button is pressed.
     *
     * It takes in a [std::function](https://en.cppreference.com/w/cpp/utility/functional/function) with a signature of
     * something that returns nothing and takes in a doodle::MouseButtons. Something like
     */
    void set_callback_mouse_pressed(std::function<void(MouseButtons)>&& callback) noexcept;
    /**
     * \brief The provided callback is called whenever a mouse button is released.
     *
     * It takes in a [std::function](https://en.cppreference.com/w/cpp/utility/functional/function) with a signature of
     * something that returns nothing and takes in a doodle::MouseButtons. Something like
     */
    void set_callback_mouse_released(std::function<void(MouseButtons)>&& callback) noexcept;
    /**
     * \brief The provided callback is called whenever the mouse wheel is scrolled.
     *
     * It takes in a [std::function](https://en.cppreference.com/w/cpp/utility/functional/function) with a signature of
     * something that returns nothing and takes in an integer. Something like
     */
    void set_callback_mouse_wheel(std::function<void(int)>&& callback) noexcept;
    /** @} */
}

/**
 *  * \addtogroup Events
 *  global variables related to input Events
 *  @{
 */
/**
 * \brief The declaration of the optional on_key_pressed function to implement in your doodle program.
 *
 * If you define the function definition of this function then it will be called when a keyboard button is pressed.
 *
 * \param button which button is being pressed
 *
 *
 *
 */
EVENT_HOOK void on_key_pressed(doodle::KeyboardButtons button);
/**
 * \brief The declaration of the optional on_key_released function to implement in your doodle program.
 *
 * If you define the function definition of this function then it will be called when a keyboard button is released.
 *
 * \param button which button was released
 *
 */
EVENT_HOOK void on_key_released(doodle::KeyboardButtons button);
/**
 * \brief The declaration of the optional on_mouse_moved function to implement in your doodle program.
 *
 * If you define the function definition of this function then it will be called whenever the mouse moves to a new
 * position.
 *
 * \param mouse_x mouse x position relative to the current doodle::FrameOfReference
 * \param mouse_y mouse y position relative to the current doodle::FrameOfReference
 *
 */
EVENT_HOOK void on_mouse_moved(int mouse_x, int mouse_y);
/**
 * \brief The declaration of the optional on_mouse_pressed function to implement in your doodle program.
 *
 * If you define the function definition of this function then it will be called whenever a mouse button is pressed.
 *
 * \param button which button is being pressed
 *
 *
 */
EVENT_HOOK void on_mouse_pressed(doodle::MouseButtons button);
/**
 * \brief The declaration of the optional on_mouse_released function to implement in your doodle program.
 *
 * If you define the function definition of this function then it will be called whenever a mouse button was
 * released.
 *
 * \param button which button was released
 *
 *
 */
EVENT_HOOK void on_mouse_released(doodle::MouseButtons button);
/**
 * \brief The declaration of the optional on_mouse_wheel function to implement in your doodle program.
 *
 * If you define the function definition of this function then it will be called whenever the mouse wheel scrolls.
 *
 * \param scroll_amount Positive for scroll up and negative for scroll down.
 *
 */
EVENT_HOOK void on_mouse_wheel(int scroll_amount);
/** @} */
