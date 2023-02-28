#include "renderer.h"

namespace _NAC {
	SDL_Renderer* Renderer::m_Renderer = nullptr;
	SDL_Window* Renderer::m_Window = nullptr;

	Renderer::Renderer(SDL_Window* window)
	{
		m_Window = window;
	}

	Renderer::~Renderer()
	{
		Shutdown();
	}

	void Renderer::Shutdown()
	{
		if (m_Renderer != NULL)
		{
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

		return true;
	}

	
}