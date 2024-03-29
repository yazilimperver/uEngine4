/**
 * @file camera.h.
 * @date 11.06.2022
 * @author Yazilimperver
 * @brief Oyun motoru kutuphanesi icerisinde hareketi ele almak icin kullanilacak olan siniftir.
 * 		  Mevcut durumda, sprite, sprite sheet ve tilemap'ler bu sinif araciligi ile hareket ettirilmektedir
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef CAMERA
#define CAMERA

#include "common.h"
#include "graphics/rectangle.h"

#include "application_base/window_parameter.h"

namespace basic_engine {
	class Camera {
	public:
		void Initialize(const WindowParameter& winParameters);
		void Update(double deltaTimeInMsec);

		infra::Rectangle<float> ViewBox() const;
		Vector2f Center() const;
		Vector2f Target() const;
		void ResetTarget();
		void SetTarget(Vector2f val);
		void DisplayInfo();
	protected:
		/** @brief Kameranưn izleyecegi nokta */
		bool mIsTargetAssigned{ false };
		Vector2f mTarget;

		/** @brief Kamera merkezi */
		Vector2f mCenter;

		/** @brief Kameranin goruntuleme alani */
		infra::Rectangle<float> mViewBox;
		
		/** @brief Pencere genisligi */
		uint32_t mWidth{ 640 };

		/** @brief Pencere yuksekligi  */
		uint32_t mHeight{ 480 };
		
		/** @brief Kamera sinirlari */
		float mCameraLeftBoundary;
		float mCameraRightBoundary;
		float mCameraTopBoundary;
		float mCameraBottomBoundary;
	};
}

#endif // !CAMERA

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