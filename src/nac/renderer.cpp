#include "renderer.h"

namespace _NAC {
	SDL_Renderer* Renderer::m_Renderer = nullptr;
	SDL_Window* Renderer::m_Window = nullptr;
	SDL_Rect Renderer::m_Rects[100] = { {0} };
	SDL_Rect Renderer::m_LastRects[100] = { {0} };
	Texture* Renderer::m_Textures[100] = { 0 };
	int Renderer::m_MouseX = 0;
	int Renderer::m_MouseY = 0;
	int Renderer::m_Counter = 0;

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
			for (int i = 0; i < 1; i++)
			{
				SDL_DestroyTexture(m_Textures[i]->Get_Texture());
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

		m_Textures[0] = new Texture( 997, 720, 0, 0, "logo.png", m_Renderer);
		// m_Textures[1] = new Texture( 1330, 900, 1920/3, 1080/3, "logo2.png", m_Renderer);

		return true;
	}

	// draw the texture on the screen
	void Renderer::Draw_Texture()
	{
		for (int i = 0; i < 1; i++)
		{
			SDL_RenderCopy(m_Renderer, m_Textures[i]->Get_Texture(), NULL, m_Textures[i]->Get_Rect());
		}
	}

	// write a function that will move the texture on mouse drag
	void Renderer::Move_Screen()
	{
		ImGuiIO& io = ImGui::GetIO();
		// io.MousePos.y = event.motion.y;
		for (int i = 0; i < 1; i++)
		{
			m_MouseX = m_Textures[i]->Get_Rect()->x + io.MouseDelta.x;
			m_MouseY = m_Textures[i]->Get_Rect()->y + io.MouseDelta.y;
			// m_Rects[0] = {io.MouseDelta.x, io.MouseDelta.y, 100, 180 };
			// m_Rects[1] = { x, y, 1100, 1100 };
			m_Textures[i]->Set_Rect({m_MouseX, m_MouseY, m_Textures[i]->Get_Rect()->w, m_Textures[i]->Get_Rect()->h});
			SDL_RenderCopy(m_Renderer, m_Textures[i]->Get_Texture(), NULL, m_Textures[i]->Get_Rect());
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
		m_Counter++;
		ImGuiIO& io = ImGui::GetIO();
        SDL_RenderClear(m_Renderer);

		// if the mouse is pressed, then the texture will be drawn at the mouse position ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)
		if (ImGui::GetIO().MouseDown[0] == true && !io.WantCaptureMouse) 
		{
			// short delay before the texture starts moving
			if (m_Counter > 1)
				Move_Screen();
			else
				Draw_Texture();
		}
		// if the mouse is not pressed, then the texture will be drawn at the last position
		else 
		{
			m_Counter = 0;
			Draw_Texture();
		}

        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(m_Renderer);
	}
}