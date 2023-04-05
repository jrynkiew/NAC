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

	struct Position
	{
		float x;
		float y;
		float lastx;
		float lasty;
	};

	class Renderer
	{
		private:
			static SDL_Renderer* m_Renderer;
			static SDL_Window* m_Window;

			//array of textures
			static Texture* m_Textures[100];
			
			//move texture
			static int m_MoveX;
			static int m_MoveY;

			//static int counter
			static int m_Counter;
			
			//number of textures
			static int m_NumTextures;

			// float lastDeltaDifferenceX = 0;
			// float lastDeltaDifferenceY = 0;

		public:
			Renderer(SDL_Window* window);
			~Renderer();
			
			bool Initialize();
			SDL_Renderer* Get_SDL_Renderer();

			void Zoom_Decrement(double m_ZoomIncrement);
			void Zoom_Increment(double m_ZoomIncrement);

			Position mousePos;
			Position finger0Pos;
			Position finger1Pos;

			void Clear();
			void Present();
			void New_Frame();
			void Render();
			void Move_Screen();
			void Draw_Texture();

			void Add_Texture(int w, int h, int x, int y, const char* path);

			void Shutdown();
	};
	
}

#define g_pRenderer _NAC::Renderer::GetRenderer();