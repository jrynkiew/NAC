#include "window.h"

namespace _NAC {

    //static instance
    SDL_GLContext m_Context = nullptr;
    SDL_Window* Window::m_Window = nullptr;

	//constructor
	Window::Window()
    {
    }

	//destructor
	Window::~Window()
	{
        Shutdown();
	}

    //gets the width of the window
    int Window::GetWidth() {
        return m_Width;
    }

    //gets the height of the window
    int Window::GetHeight() {
        return m_Height;
    }

    //gets the Window
    SDL_Window* Window::Get_SDL_Window() {
        return m_Window;
    }

	//creates the window and the opengl context
	bool Window::Initialize(const char* windowTitle, int width, int height)
	{
        // Setup SDL
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
        {
            printf("Error: %s\n", SDL_GetError());
            return false;
        }

        // From 2.0.18: Enable native IME.
        #ifdef SDL_HINT_IME_SHOW_UI
            SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
        #endif

        // Create window with SDL_Renderer graphics context
        
        m_Window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags);
        if (m_Window == NULL)
        {
            printf("Error: %s\n", SDL_GetError());
            return false;
        }

        return true;
	}

    //destroys the window and the opengl context
    void Window::Shutdown()
    {
        //destroy the window
        if (m_Window)
        {
            SDL_DestroyWindow(m_Window);
            SDL_Quit();
            m_Window = nullptr;
        }
    }
}
