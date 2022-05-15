#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "common.h"

namespace basic_engine {
    template <typename T>
    class Rectangle {
    public:
        Rectangle() 
            : mLeft(0),
            mTop(0),
            mWidth(0),
            mHeight(0) {
        }
        Rectangle(T rectLeft, T rectTop, T rectWidth, T rectHeight);
        template <typename U>
        explicit Rectangle(const Rectangle<U>& rectangle);

        bool Contains(T x, T y) const;
        bool Intersects(const Rectangle<T>& rectangle) const;
        bool Intersects(const Rectangle<T>& rectangle, Rectangle<T>& intersection) const;

        T mLeft;   
        T mTop;    
        T mWidth;  
        T mHeight; 
    };

    template <typename T>
    Rectangle<T>::Rectangle(T rectLeft, T rectTop, T rectWidth, T rectHeight) :
        mLeft(rectLeft),
        mTop(rectTop),
        mWidth(rectWidth),
        mHeight(rectHeight) {
    }

    template <typename T>
    template <typename U>
    Rectangle<T>::Rectangle(const Rectangle<U>& rectangle) :
        mLeft(static_cast<T>(rectangle.mLeft)),
        mTop(static_cast<T>(rectangle.mTop)),
        mWidth(static_cast<T>(rectangle.mWidth)),
        mHeight(static_cast<T>(rectangle.mHeight)) {
    }



    template <typename T>
    bool Rectangle<T>::Contains(T x, T y) const {
        T minX = std::min(mLeft, static_cast<T>(mLeft + mWidth));
        T maxX = std::max(mLeft, static_cast<T>(mLeft + mWidth));
        T minY = std::min(mTop, static_cast<T>(mTop + mHeight));
        T maxY = std::max(mTop, static_cast<T>(mTop + mHeight));

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

        T r1MinX = std::min(mLeft, static_cast<T>(mLeft + mWidth));
        T r1MaxX = std::max(mLeft, static_cast<T>(mLeft + mWidth));
        T r1MinY = std::min(mTop, static_cast<T>(mTop + mHeight));
        T r1MaxY = std::max(mTop, static_cast<T>(mTop + mHeight));

        T r2MinX = std::min(rectangle.mLeft, static_cast<T>(rectangle.mLeft + rectangle.mWidth));
        T r2MaxX = std::max(rectangle.mLeft, static_cast<T>(rectangle.mLeft + rectangle.mWidth));
        T r2MinY = std::min(rectangle.mTop, static_cast<T>(rectangle.mTop + rectangle.mHeight));
        T r2MaxY = std::max(rectangle.mTop, static_cast<T>(rectangle.mTop + rectangle.mHeight));

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
    inline bool operator ==(const Rectangle<T>& mLeft, const Rectangle<T>& right) {
        return (mLeft.mLeft == right.mLeft) && (mLeft.mWidth == right.mWidth) &&
            (mLeft.mTop == right.mTop) && (mLeft.mHeight == right.mHeight);
    }

    template <typename T>
    inline bool operator !=(const Rectangle<T>& mLeft, const Rectangle<T>& right) {
        return !(mLeft == right);
    }


}  // basic_engine

#endif