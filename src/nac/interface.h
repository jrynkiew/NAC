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
			// the interface pointer
            static ImGuiIO* m_io;
			// the renderer pointer
			static SDL_Renderer* m_Renderer;
			// the window pointer
			static SDL_Window* m_Window;
			// the interface flags
			bool show_demo_window;
			// the interface flags
			bool show_another_window;

		public:
			// constructor
			Interface(SDL_Window* window, SDL_Renderer* renderer);
			// destructor
			~Interface();
			// create the interface
			bool Initialize();
			// get the interface
			ImGuiIO* Get_ImGui_Interface();
			// draw the interface
			void Draw_Interface();
			// destroy the interface
			void Shutdown();
	};
}
