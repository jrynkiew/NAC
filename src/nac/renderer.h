#pragma once
#define NAC_RENDERER_H
#include <SDL.h>
#include <stdio.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "imgui_impl_sdlrenderer.h"
#include "imgui_impl_sdl2.h"

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

namespace _NAC {

	class Renderer
	{
		private:
			static SDL_Renderer* m_Renderer;
			static SDL_Window* m_Window;

		public:
			Renderer(SDL_Window* window);
			~Renderer();
			
			bool Initialize();
			SDL_Renderer* Get_SDL_Renderer();
			void Shutdown();
	};
}
