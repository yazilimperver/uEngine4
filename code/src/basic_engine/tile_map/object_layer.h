#ifndef OBJECT_LAYER_H
#define OBJECT_LAYER_H

#include <cstdint>
#include <memory>
#include <vector>
#include <string_view>

#include "layer.h"

#include "basic_engine/sprite.h"

namespace tson {
	class Layer;
}

namespace basic_engine {
	class ObjectLayer : public Layer {
	public:
		ObjectLayer(std::string_view rootPath, tson::Layer& layer);
		virtual void Update(double deltaTimeInMsec) override;
		virtual void Display(SDL_Renderer* renderer) const override;
	protected:
		std::vector<std::unique_ptr<basic_engine::Sprite>> mObjectSprites;
	};
}

#endif // !OBJECT_LAYER_H

