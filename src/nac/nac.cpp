#include <nac.h>

namespace _NAC
{
    Window* NAC::m_pWindow = nullptr;
    Renderer* NAC::m_pRenderer = nullptr;
    Interface* NAC::m_pInterface = nullptr;

    void NAC::main_loop() { loop(); }

    NAC::NAC() {
        loop = [&] {
            while (true) {
                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        return;
                    }
                }
            }
        };
    }

    NAC::~NAC() {
    }

    SDL_Renderer* NAC::GetRenderer() { 
        return m_pRenderer->Get_SDL_Renderer();
    }

    SDL_Window* NAC::GetWindow() {
		return m_pWindow->Get_SDL_Window();
    }

    ImGuiIO* NAC::GetInterface() {
        return m_pInterface->Get_ImGui_Interface();
    }

    bool NAC::Initialize() {
        //initialize the window
        m_pWindow = new Window();
        if (!m_pWindow->Initialize("NAC", 1920, 1080))
            return false;

        //initialize the renderer
        m_pRenderer = new Renderer(GetWindow());
        if (!m_pRenderer->Initialize())
            return false;
        
        m_pInterface = new Interface(GetWindow(), GetRenderer());
        if (!m_pInterface->Initialize())
            return false;

        //return success
        return true;
    }

    void NAC::Shutdown() {
        //delete the renderer
        if (m_pRenderer)
            delete m_pRenderer;

        //delete the window
        if (m_pWindow)
            delete m_pWindow;
    }
}