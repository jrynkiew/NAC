#pragma once
#define NAC_RENDERER_H
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include "texture.h"

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

			//array of sdl_rects
			static SDL_Rect m_Rects[100];

			//array of last sdl_rects
			static SDL_Rect m_LastRects[100];

			//array of textures
			static Texture* m_Textures[100];

			//mouse position
			static int m_MouseX;
			static int m_MouseY;

			//static int counter
			static int m_Counter;

		public:
			Renderer(SDL_Window* window);
			~Renderer();
			
			bool Initialize();
			SDL_Renderer* Get_SDL_Renderer();

			void Clear();
			void Present();
			void New_Frame();
			void Render();
			void Move_Screen();
			void Draw_Texture();

			void Shutdown();
	};
	
}

#define g_pRenderer _NAC::Renderer::GetRenderer();