#ifndef PAINTER_H
#define PAINTER_H

#include "SDL.h"

/**
 * @class Painter
 * @brief Basit cizim islerini kotarmasi icin kullanabilecegimiz sinif
 */
namespace basic_engine {
	class Painter {
	public:
		void AssignRenderer(SDL_Renderer* renderer);
	protected:
		SDL_Renderer* mRenderer{ nullptr };
	};
}
#endif // !PAINTER_H

