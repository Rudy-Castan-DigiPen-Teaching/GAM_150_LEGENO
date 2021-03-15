/*--------------------------------------------------------------*
  Copyright (C) 2021 Rudy Castan

  This file is distributed WITHOUT ANY WARRANTY. See the file
  `License.md' for details.
*--------------------------------------------------------------*/
#pragma once


namespace doodle
{
    /**
     *  \addtogroup Environment
     *  global variables related to the state of the doodle
     *  @{
     */
    /**
     * \brief The system variable FrameCount contains the number of frames that have been displayed since the program
     * started. The first call to update_window() will set the value to 1 and subsequent calls increment the value.
     *
     */
    extern int FrameCount;
    /**
     * \brief The system variable DeltaTime contains the time difference between the beginning of the previous frame and
     * the beginning of the current frame in seconds.
     *
     * This variable is useful for creating time sensitive animation or physics calculation that should stay constant
     * regardless of frame rate.
     *
     */
    extern double DeltaTime;
    /**
     * \brief Returns the number of seconds since starting the program. This information is often used for timing events
     * and animation sequences.
     *
     */
    extern double ElapsedTime;
    /**
     * \brief System variable that stores the width of the drawing canvas. This value is set by the **desired_width**
     * parameter of the create_window() function. For example, the function call create_window(320, 240) sets the width
     * variable to the value 320.
     *
     */
    extern int Width;
    /**
     * \brief System variable that stores the height of the drawing canvas. This value is set by the **desired_height**
     * parameter of the create_window() function. For example, the function call create_window(320, 240) sets the height
     * variable to the value 240.
     *
     */
    extern int Height;
    /** @} */
}
