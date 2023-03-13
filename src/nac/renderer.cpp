#include "renderer.h"

namespace _NAC {
	SDL_Renderer* Renderer::m_Renderer = nullptr;
	SDL_Window* Renderer::m_Window = nullptr;
	Texture* Renderer::m_Textures[100] = { 0 };
	int Renderer::m_MoveX = 0;
	int Renderer::m_MoveY = 0;
	int Renderer::m_Counter = 0;
	int Renderer::m_NumTextures = 0;

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
			for (int i = 0; i < m_NumTextures; i++)
			{
				SDL_DestroyTexture(m_Textures[i]->Get_Texture());
				m_Textures[i] = NULL;
				m_NumTextures--;
			}
			ImGui_ImplSDLRenderer_Shutdown();
    		ImGui_ImplSDL2_Shutdown();
			SDL_DestroyRenderer(m_Renderer);
			m_Renderer = NULL;
		}
	}

	void Renderer::Zoom_Decrement(double m_ZoomIncrement)
	{
		for (int i = 0; i < m_NumTextures; i++)
		{
			if (m_Textures[i]->Get_Rect()->w < 100 || m_Textures[i]->Get_Rect()->h < 100)
				return;
			int xPos = m_Textures[i]->Get_Rect()->x;
			int yPos = m_Textures[i]->Get_Rect()->y;
			int width = m_Textures[i]->Get_Rect()->w;
			int height = m_Textures[i]->Get_Rect()->h;
			
			width = (width - (width/m_ZoomIncrement));
			height = (height - (height/m_ZoomIncrement));

			xPos += width/2;
			yPos += height/2;
			
			m_Textures[i]->Set_Rect({xPos, yPos, m_Textures[i]->Get_Rect()->w - width, m_Textures[i]->Get_Rect()->h - height});
		}
	}

	void Renderer::Zoom_Increment(double m_ZoomIncrement)
	{
		for (int i = 0; i < m_NumTextures; i++)
		{
			if (m_Textures[i]->Get_Rect()->w > 3000 || m_Textures[i]->Get_Rect()->h > 3000)
				return;
			int xPos = m_Textures[i]->Get_Rect()->x;
			int yPos = m_Textures[i]->Get_Rect()->y;
			int width = m_Textures[i]->Get_Rect()->w;
			int height = m_Textures[i]->Get_Rect()->h;
			
			width = (width*m_ZoomIncrement) - width;
		 	height = (height*m_ZoomIncrement) - height;

			xPos -= width/2;
			yPos -= height/2;
			
			m_Textures[i]->Set_Rect({xPos, yPos, m_Textures[i]->Get_Rect()->w + width, m_Textures[i]->Get_Rect()->h + height});
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

		Add_Texture(363, 288, 20, 200, "logo.png");

		// m_Textures[1] = new Texture( 1330, 900, 1920/3, 1080/3, "logo2.png", m_Renderer);

		return true;
	}

	void Renderer::Add_Texture(int w, int h, int x, int y, const char* path)
	{
		m_Textures[m_NumTextures] = new Texture(w, h, x, y, path, m_Renderer);
		m_NumTextures++;
	}

	// draw the texture on the screen
	void Renderer::Draw_Texture()
	{
		for (int i = 0; i < m_NumTextures; i++)
		{
			SDL_RenderCopy(m_Renderer, m_Textures[i]->Get_Texture(), NULL, m_Textures[i]->Get_Rect());
		}
	}

	// write a function that will move the texture on mouse drag
	void Renderer::Move_Screen()
	{
		ImGuiIO& io = ImGui::GetIO();
		for (int i = 0; i < m_NumTextures; i++)
		{
			m_MoveX = m_Textures[i]->Get_Rect()->x + io.MouseDelta.x;
			m_MoveY = m_Textures[i]->Get_Rect()->y + io.MouseDelta.y;
			m_Textures[i]->Set_Rect({m_MoveX, m_MoveY, m_Textures[i]->Get_Rect()->w, m_Textures[i]->Get_Rect()->h});
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
		if (ImGui::GetIO().MouseDown[0] == true && !io.WantCaptureMouse && ImGui::GetIO().MouseDown[1] == false) 
		{
			// short delay before the texture starts moving
			if (m_Counter > 1)
				Move_Screen();
			else
				Draw_Texture();
		}
		// if two fingers are touching the screen, then the texture will be zoomed in or out
		else if (ImGui::GetIO().MouseDown[0] == true && ImGui::GetIO().MouseDown[1] == true && !io.WantCaptureMouse)
		{
			// if finger 0 x is less than finger 1 x, then most likely the left thumb is touching the screen as finger 0
			if ((finger0Pos.x < finger0Pos.lastx && finger1Pos.x > finger0Pos.x && finger1Pos.x > finger1Pos.lastx) || (finger0Pos.x > finger0Pos.lastx && finger1Pos.x < finger0Pos.x && finger1Pos.x < finger1Pos.lastx) || (finger0Pos.y < finger0Pos.lasty && finger1Pos.y > finger0Pos.y && finger1Pos.y > finger1Pos.lasty) || (finger0Pos.y > finger0Pos.lasty && finger1Pos.y < finger0Pos.y && finger1Pos.y < finger1Pos.lasty))
				Zoom_Increment(1.02);
			if ((finger0Pos.x > finger0Pos.lastx && finger1Pos.x > finger0Pos.x && finger1Pos.x < finger1Pos.lastx) || (finger0Pos.x < finger0Pos.lastx && finger1Pos.x < finger0Pos.x && finger1Pos.x > finger1Pos.lastx) || (finger0Pos.y > finger0Pos.lasty && finger1Pos.y > finger0Pos.y && finger1Pos.y < finger1Pos.lasty) || (finger0Pos.y < finger0Pos.lasty && finger1Pos.y < finger0Pos.y && finger1Pos.y > finger1Pos.lasty))
				Zoom_Decrement(1.02);

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

		finger0Pos.lastx = finger0Pos.x;
		finger0Pos.lasty = finger0Pos.y;
		finger1Pos.lastx = finger1Pos.x;
		finger1Pos.lasty = finger1Pos.y;
	}
}