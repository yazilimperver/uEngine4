/**
 * @file   tile_name_calculator.h
 * @date   4/21/2023
 * @author Yazilimperver
 * @brief  Pafta isimlerini ve bunlarin yollarini hesaplamak icin kullanilacak olan temel siniftir.
 *         Bu siniftan turetilmis siniflar kullanilarak, internet uzerinden pafta indirme veya diskten pafta okumak icin kullanilacaktir
 * @remark
 */

#ifndef INC_TILE_NAME_CALCULATOR_H
#define INC_TILE_NAME_CALCULATOR_H

#include <string>
#include <string_view>

namespace gis {
    class TileNameCalculator {
    public:
        TileNameCalculator(std::string_view  extension, std::string_view root );

        /** @brief Paftalarin ismini almak icin kullanilacak olan fonksiyondur */
        virtual std::string Path(uint32_t zoomLevel, uint32_t row, uint32_t col) const = 0;

        /** @brief Hangi katman tipi icin hangi isimlendirme kullanilacagini belirlemek icin donulecek isim */
        virtual std::string LayerType() const = 0;

        std::string Root() const;
        std::string Extension() const;

        void SetRoot(std::string_view root);
        void SetExtension(std::string_view extension);
    protected:
        /** @brief Paftalarin uzantisi */
        std::string mExtension;

        /** @brief Pafta isimlerinin basina eklenecek olan ortak isimlendirme */
        std::string mRoot;
    };
}

#endif	// INC_TILE_NAME_CALCULATOR_H

/**
Copyright (c) [2023][Yazilimperver - yazilimpervergs@gmail.com]

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


