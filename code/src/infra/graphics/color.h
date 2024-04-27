/**
 * @file color.h.
 * @date 30.04.2022
 * @author Yazilimperver
 * @brief  Renkleri temsil etmek icin kullanacagimiz siniftir
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */

#ifndef COLOR
#define COLOR

#include <cstdint>

class Color {
public:
    constexpr Color();
    constexpr Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);
    constexpr explicit Color(uint32_t color);

    constexpr uint32_t ToInteger() const;

    // Static member data
    static const Color Black;       
    static const Color White;       
    static const Color Red;         
    static const Color Green;       
    static const Color Blue;        
    static const Color Yellow;      
    static const Color Magenta;
    static const Color Orange;
    static const Color Cyan;        
    static const Color Transparent; 

    inline float GetRedF() const {
        return static_cast<float>(R) / 255.0F;
    }

    inline float GetGreenF() const {
        return static_cast<float>(G) / 255.0F;
    }

    inline float GetBlueF() const {
        return static_cast<float>(B) / 255.0F;
    }

    inline float GetAlphaF() const{
        return static_cast<float>(A) / 255.0F;
    }

    // Member data
    uint8_t R; 
    uint8_t G; 
    uint8_t B; 
    uint8_t A; 
};

[[nodiscard]] constexpr bool operator ==(const Color& left, const Color& right);
[[nodiscard]] constexpr bool operator !=(const Color& left, const Color& right);
[[nodiscard]] constexpr Color operator +(const Color& left, const Color& right);
[[nodiscard]] constexpr Color operator -(const Color& left, const Color& right);
[[nodiscard]] constexpr Color operator *(const Color& left, const Color& right);
[[nodiscard]] constexpr Color& operator +=(Color& left, const Color& right);
[[nodiscard]] constexpr Color& operator -=(Color& left, const Color& right);
[[nodiscard]] constexpr Color& operator *=(Color& left, const Color& right);

constexpr Color::Color() :
    R(0),
    G(0),
    B(0),
    A(255) {

}

constexpr Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) :
    R(red),
    G(green),
    B(blue),
    A(alpha) {

}

constexpr Color::Color(uint32_t color) :
    R(static_cast<uint8_t>((color & 0xff000000) >> 24)),
    G(static_cast<uint8_t>((color & 0x00ff0000) >> 16)),
    B(static_cast<uint8_t>((color & 0x0000ff00) >> 8)),
    A(static_cast<uint8_t>(color & 0x000000ff)) {

}

constexpr uint32_t Color::ToInteger() const {
    return static_cast<uint32_t>((R << 24) | (G << 16) | (B << 8) | A);
}

constexpr bool operator ==(const Color& left, const Color& right) {
    return (left.R == right.R) &&
        (left.G == right.G) &&
        (left.B == right.B) &&
        (left.A == right.A);
}

constexpr bool operator !=(const Color& left, const Color& right) {
    return !(left == right);
}

constexpr Color operator +(const Color& left, const Color& right)
{
    const auto clampedAdd = [](uint8_t lhs, uint8_t rhs) -> uint8_t {
        const int intResult = static_cast<int>(lhs) + static_cast<int>(rhs);
        return static_cast<uint8_t>(intResult < 255 ? intResult : 255);
    };

    return Color(clampedAdd(left.R, right.R),
        clampedAdd(left.G, right.G),
        clampedAdd(left.B, right.B),
        clampedAdd(left.A, right.A));
}

constexpr Color operator -(const Color& left, const Color& right) {
    const auto clampedSub = [](uint8_t lhs, uint8_t rhs) -> uint8_t {
        const int intResult = static_cast<int>(lhs) - static_cast<int>(rhs);
        return static_cast<uint8_t>(intResult > 0 ? intResult : 0);
    };

    return Color(clampedSub(left.R, right.R),
        clampedSub(left.G, right.G),
        clampedSub(left.B, right.B),
        clampedSub(left.A, right.A));
}

constexpr Color operator *(const Color& left, const Color& right) {
    const auto scaledMul = [](uint8_t lhs, uint8_t rhs) -> uint8_t {
        const auto uint16Result = static_cast<uint16_t>(static_cast<uint16_t>(lhs) * static_cast<uint16_t>(rhs));
        return static_cast<uint8_t>(uint16Result / 255u);
    };

    return Color(scaledMul(left.R, right.R),
        scaledMul(left.G, right.G),
        scaledMul(left.B, right.B),
        scaledMul(left.A, right.A));
}

constexpr Color& operator +=(Color& left, const Color& right) {
    return left = left + right;
}

constexpr Color& operator -=(Color& left, const Color& right) {
    return left = left - right;
}

constexpr Color& operator *=(Color& left, const Color& right) {
    return left = left * right;
}

// Note: the 'inline' keyword here is technically not required, but VS2019 fails
// to compile with A bogus "multiple definition" error if not explicitly used.
inline constexpr Color Color::Black(0, 0, 0);
inline constexpr Color Color::White(255, 255, 255);
inline constexpr Color Color::Red(255, 0, 0);
inline constexpr Color Color::Green(0, 255, 0);
inline constexpr Color Color::Blue(0, 0, 255);
inline constexpr Color Color::Orange(255, 128, 0);
inline constexpr Color Color::Yellow(255, 255, 0);
inline constexpr Color Color::Magenta(255, 0, 255);
inline constexpr Color Color::Cyan(0, 255, 255);
inline constexpr Color Color::Transparent(0, 0, 0, 0);


#endif /* COLOR */

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
