/**
* @file window_parameter.h
* @date  2015/10/11 22:33
* @brief Auto generated config content data
* @author Mehmet Fatih ULUAT
*
* @details
*
* Copyright © 2015, uEngine V3.0 Mehmet Fatih ULUAT <fatihuluat@gmail.com>
*/
#pragma once
#include <cstdint>
#include <string>

#include "graphics/color.h"

/**
 * @struct WindowParameter
 * @brief A window parameter.
 */
struct WindowParameter {
    //! Title of application window
    /** @brief The title */
    std::string Title{"Default uEngine 4 Window"};

    //! The width of window
    /** @brief The width */
    uint32_t Width{640};

    //! The height of window
    /** @brief The height */
    uint32_t Height{480};

    //! The initial top position of application window
    /** @brief The top */
    uint32_t Top{0};

    //! The initial left position of application window
    /** @brief The left */
    uint32_t Left{0};

    //! The clear color of application window
    /** @brief The clear color */
    Color ClearColor{180, 50, 79};

    //! The initial fullscreen status of window
    /** @brief The is full screen */
    bool IsFullScreen{false};

    //! Will VSync enabled for given application window
    /** @brief The is vsync enabled */
    bool IsVSYNCEnabled{ false };
};

/**
Copyright (c) [2022][Yazilimperver - yazilimpervergs@gmail.com]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */
