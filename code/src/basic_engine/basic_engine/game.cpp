#include "game.h"
#include "asset/asset_repository.h"

namespace basic_engine {
	WindowParameter Game::mActiveWinParameters = WindowParameter{};

	AssetService& Game::AssetService() {
		static AssetRepository instance;
		return instance;
	}
	
	void Game::AssignWindowParameters(const WindowParameter& parameters) {
		mActiveWinParameters = parameters;
	}
	const WindowParameter& Game::WindowParameters() {
		return mActiveWinParameters;
	}
}