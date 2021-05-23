/*--------------------------------------------------------------*
  Copyright (C) 2021 Rudy Castan

  This file is distributed WITHOUT ANY WARRANTY. See the file
  `License.md' for details.
*--------------------------------------------------------------*/
#pragma once


namespace doodle
{
    /**
     * \addtogroup Utility
     *  Helper functions to get random numbers.
     *  @{
     */

    /**
     * \brief Sets the seed value for random().
     *
     * By default, random() produces different results each time the program is run. Set the seed parameter to a
     * constant to return the same pseudo-random numbers each time the software is run.
     *
     * \param seed the seed value
     *
     */
    void seed_random(unsigned int seed) noexcept;
    /**
     * \brief Return a random floating-point number within the range [min,max)
     * \param min_inclusive the inclusive lower bound or the minimum value to be returned
     * \param max_exclusive the exclusive upper bound or the maximum value but won't be returned.
     * \return random number
     *
     *
     */
    double random(double min_inclusive, double max_exclusive) noexcept;
    /**
     * \brief Return a random floating-point number within the range [0,max)
     *
     */
    double random(double max_exclusive) noexcept;
    /**
     * \brief Return a random floating-point number within the range [0,1)
     *
     */
    double random() noexcept;
    /**
     * \brief Return a random integer number within the range [min,max)
     *
     * \param min_inclusive the inclusive lower bound or the minimum value to be returned
     * \param max_exclusive the exclusive upper bound or the maximum value but won't be returned.
     * \return random number
     *
     */
    int random(int min_inclusive, int max_exclusive) noexcept;
    /**
     * \brief Return a random integer number within the range [0,max)
     *
     */
    int random(int max_exclusive) noexcept;
    /** @} */
}
