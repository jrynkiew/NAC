#pragma once
#define NAC_RENDERER_H

#include <renderer.h>
#include <window.h>

#include "imgui.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

namespace _NAC {
	//definition of class that creates a gui
	class Interface
	{
		private:
            static ImGuiIO* m_io;
			static SDL_Renderer* m_Renderer;
			static SDL_Window* m_Window;

		public:
			Interface(SDL_Window* window, SDL_Renderer* renderer);
			~Interface();
			
			bool Initialize();
			ImGuiIO* Get_ImGui_Interface();
	};
}
