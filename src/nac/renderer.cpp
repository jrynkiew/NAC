#include "renderer.h"

namespace _NAC {
	SDL_Renderer* Renderer::m_Renderer = nullptr;
	SDL_Window* Renderer::m_Window = nullptr;
	SDL_Texture* Renderer::m_Textures[100] = { 0 };
	SDL_Surface* Renderer::m_Surfaces[100] = { nullptr };
	SDL_Rect Renderer::m_Rects[100] = { 0 };
	SDL_Rect Renderer::m_LastRects[100] = { 0 };
	Texture* Renderer::m_Textures2[100] = { 0 };

	Renderer::Renderer(SDL_Window* window)
	{
		m_Window = window;
		m_Rects[0] = { 0, 0, 100, 100 };
	}

	Renderer::~Renderer()
	{
		Shutdown();
	}

	void Renderer::Shutdown()
	{
		if (m_Renderer != NULL)
		{
			for (int i = 0; i < 2; i++)
			{
				SDL_DestroyTexture(m_Textures[i]);
			}
			ImGui_ImplSDLRenderer_Shutdown();
    		ImGui_ImplSDL2_Shutdown();
			SDL_DestroyRenderer(m_Renderer);
			m_Renderer = NULL;
		}
	}

	SDL_Renderer* Renderer::Get_SDL_Renderer()
	{
		return m_Renderer;
	}

	// initialize the renderer
	bool Renderer::Initialize()
	{
		if (m_Window == NULL)
		{
			SDL_Log("Error during renderer initialization!");
			return false;
		}
		m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
		if (m_Renderer == NULL)
		{
			SDL_Log("Error creating SDL_Renderer!");
			return false;
		}
		SDL_RendererInfo info;
		SDL_GetRendererInfo(m_Renderer, &info);
		SDL_Log("Current SDL_Renderer: %s", info.name);

		SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);

		m_Textures2[0] = new Texture( 100, 180, 960, 540, "logo2.png", m_Renderer);
		m_Textures2[1] = new Texture( 960, 540, 1100, 1100, "logo.png", m_Renderer);

		
		// SDL_RenderCopy(m_Renderer, m_Texture, NULL, &rect);
		// for (int i = 0; i < 2; i++)
		// {
		// 	SDL_RenderCopy(m_Renderer, m_Textures2[i]->Get_Texture(), NULL, {960 , 540, 100, 180 });
		// }

		return true;
	}

	// draw the texture on the screen
	void Renderer::Draw_Texture()
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		for (int i = 0; i < 2; i++)
		{
			m_Textures2[i]->Set_Rect({x , y, 100, 180 });
			SDL_RenderCopy(m_Renderer, m_Textures2[i]->Get_Texture(), NULL, m_Textures2[i]->Get_Rect());
		}
	}

	// write a function that will move the texture on mouse drag
	void Renderer::Move_Screen()
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		for (int i = 0; i < 2; i++)
		{
			m_Rects[0] = {x , y, 100, 180 };
			m_Rects[1] = { x, y, 1100, 1100 };
			SDL_RenderCopy(m_Renderer, m_Textures2[i]->Get_Texture(), NULL, m_Textures2[i]->Get_Rect());
		}
	}

	void Renderer::New_Frame()
	{
		ImGui_ImplSDL2_NewFrame(m_Window);
		ImGui_ImplSDLRenderer_NewFrame();
		ImGui::NewFrame();
	}

	void Renderer::Render()
	{
        SDL_RenderClear(m_Renderer);
		Move_Screen();
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
		SDL_RenderPresent(m_Renderer);
		// if the mouse is pressed, then the texture will be drawn at the mouse position
		if (ImGui::GetIO().MouseDown[0] == true)
		{
			Move_Screen();
		}
		// if the mouse is not pressed, then the texture will be drawn at the last position
		else 
		{
			Draw_Texture();
		}
		
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(m_Renderer);
	}
}