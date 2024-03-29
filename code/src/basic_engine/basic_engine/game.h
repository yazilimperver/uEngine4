/**
 * @file game.h.
 * @date 12.05.2022
 * @author Yazilimperver
 * @brief  Asset service, kamera gibi servislere kolay erisim icin singleton yaklasimi kullanan oyun s�n�f� (detaylar icin google :)
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef GAME_H
#define GAME_H

#include "asset/asset_service.h"
#include "application_base/window_parameter.h"

#include "camera.h"

namespace basic_engine {
	class Game {
	public:
		static infra::AssetService& GetAssetService();
		static Camera& GameCamera();
		static void AssignWindowParameters(const WindowParameter& parameters);
		static const WindowParameter& WindowParameters();

		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;
	private:
		Game() = default;
		~Game() = default;

		static WindowParameter mActiveWinParameters;
	};
}
#endif // !GAME_H

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
