#pragma once
#define NAC_RENDERER_WINDOW_H
#include <SDL.h>
#include <stdio.h>

namespace _NAC {
    // definition of class that creates a window and sets up the opengl context
    class Window
    {
    public:
        // constructor
        Window();
        // destructor
        ~Window();

        // creates the window and the opengl context
        bool Initialize(const char* windowTitle, int width, int height);
        // gets the width of the window
        int GetWidth();
        // gets the height of the window
        int GetHeight();
        // gets the window
        SDL_Window* Get_SDL_Window();
        // destroys the window and the opengl context
        void Shutdown();

    private:
        // the width of the window
        int m_Width;
        // the height of the window
        int m_Height;
        // the window
        static SDL_Window* m_Window;
        // the opengl context
        static SDL_GLContext m_Context;
        // the window flags
        static const SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    };

    #define g_pWindow _NAC::Window::GetWindow();
}