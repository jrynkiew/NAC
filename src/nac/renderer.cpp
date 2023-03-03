#include "renderer.h"

namespace _NAC {
	SDL_Renderer* Renderer::m_Renderer = nullptr;
	SDL_Window* Renderer::m_Window = nullptr;
	SDL_Texture* Renderer::m_Texture = nullptr;
	SDL_Surface* Renderer::m_Surface = nullptr;

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
			SDL_DestroyTexture(m_Texture);
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

		m_Surface = IMG_Load("logo.png");
        if (m_Surface == NULL) {
            printf("Error loading image: %s\n", SDL_GetError());
            return 5;
        }

        m_Texture = SDL_CreateTextureFromSurface(m_Renderer, m_Surface);
        if (m_Texture == NULL) {
            printf("Error creating image: %s\n", SDL_GetError());
            return 6;
        }

		SDL_FreeSurface(m_Surface);

		return true;
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
		SDL_RenderCopy(m_Renderer, m_Texture, NULL, NULL);
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(m_Renderer);
	}
}