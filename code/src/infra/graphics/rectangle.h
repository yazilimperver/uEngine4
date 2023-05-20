/**
 * @file rectangle.h.
 * @date 15.05.2022
 * @author Yazilimperver
 * @brief  Temel dikdörtgen sýnýfýmýz
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "common.h"

namespace infra {
    template <typename T>
    struct Rectangle {
        Rectangle()
            : Left(0),
            Top(0),
            Width(0),
            Height(0) {
        }
        Rectangle(T rectLeft, T rectTop, T rectWidth, T rectHeight);
        template <typename U>
        explicit Rectangle(const Rectangle<U>& rectangle);

        bool Contains(T x, T y) const;
        bool Intersects(const Rectangle<T>& rectangle) const;
        bool Intersects(const Rectangle<T>& rectangle, Rectangle<T>& intersection) const;

        T GetLeft() const {
            return Left;
        }
        T GetRight() const {
            return (Left + Width);
        }
        T GetTop() const {
            return Top;
        }

        T GetBottom() const {
            return (Top + Height);
        }

        T Left;
        T Top;
        T Width;
        T Height;
    };

    template <typename T>
    Rectangle<T>::Rectangle(T rectLeft, T rectTop, T rectWidth, T rectHeight) :
        Left(rectLeft),
        Top(rectTop),
        Width(rectWidth),
        Height(rectHeight) {
    }

    template <typename T>
    template <typename U>
    Rectangle<T>::Rectangle(const Rectangle<U>& rectangle) :
        Left(static_cast<T>(rectangle.Left)),
        Top(static_cast<T>(rectangle.Top)),
        Width(static_cast<T>(rectangle.Width)),
        Height(static_cast<T>(rectangle.Height)) {
    }



    template <typename T>
    bool Rectangle<T>::Contains(T x, T y) const {
        T minX = std::min(Left, static_cast<T>(Left + Width));
        T maxX = std::max(Left, static_cast<T>(Left + Width));
        T minY = std::min(Top, static_cast<T>(Top + Height));
        T maxY = std::max(Top, static_cast<T>(Top + Height));

        return (x >= minX) && (x < maxX) && (y >= minY) && (y < maxY);
    }

    template <typename T>
    bool Rectangle<T>::Intersects(const Rectangle<T>& rectangle) const
    {
        Rectangle<T> intersection;
        return intersects(rectangle, intersection);
    }

    template <typename T>
    bool Rectangle<T>::Intersects(const Rectangle<T>& rectangle, Rectangle<T>& intersection) const {

        T r1MinX = std::min(Left, static_cast<T>(Left + Width));
        T r1MaxX = std::max(Left, static_cast<T>(Left + Width));
        T r1MinY = std::min(Top, static_cast<T>(Top + Height));
        T r1MaxY = std::max(Top, static_cast<T>(Top + Height));

        T r2MinX = std::min(rectangle.Left, static_cast<T>(rectangle.Left + rectangle.Width));
        T r2MaxX = std::max(rectangle.Left, static_cast<T>(rectangle.Left + rectangle.Width));
        T r2MinY = std::min(rectangle.Top, static_cast<T>(rectangle.Top + rectangle.Height));
        T r2MaxY = std::max(rectangle.Top, static_cast<T>(rectangle.Top + rectangle.Height));

        T interLeft = std::max(r1MinX, r2MinX);
        T interTop = std::max(r1MinY, r2MinY);
        T interRight = std::min(r1MaxX, r2MaxX);
        T interBottom = std::min(r1MaxY, r2MaxY);

        if ((interLeft < interRight) && (interTop < interBottom)) {
            intersection = Rectangle<T>(interLeft, interTop, interRight - interLeft, interBottom - interTop);
            return true;
        }
        else {
            intersection = Rectangle<T>(0, 0, 0, 0);
            return false;
        }
    }

    template <typename T>
    inline bool operator ==(const Rectangle<T>& Left, const Rectangle<T>& right) {
        return (Left.Left == right.Left) && (Left.Width == right.Width) &&
            (Left.Top == right.Top) && (Left.Height == right.Height);
    }

    template <typename T>
    inline bool operator !=(const Rectangle<T>& Left, const Rectangle<T>& right) {
        return !(Left == right);
    }
}
#endif

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
