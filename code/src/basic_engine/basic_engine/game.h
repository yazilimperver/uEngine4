/**
 * @file game.h.
 * @date 12.05.2022
 * @author Yazilimperver
 * @brief  Asset service Meyer'in thread-safe singleton yaklasimi (detaylar icin google :)
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef GAME_H
#define GAME_H

#include "asset/asset_service.h"

namespace basic_engine {
	class Game {
	public:
		static AssetService& AssetService();

		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;
	private:
		Game() = default;
		~Game() = default;
	};
}
#endif // !GAME_H

