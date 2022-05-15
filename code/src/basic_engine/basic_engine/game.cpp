#include "game.h"
#include "asset/asset_repository.h"

namespace basic_engine {
	AssetService& Game::AssetService() {
		static AssetRepository instance;
		return instance;
	}
}