#include <nac.h>

namespace _NAC
{
    Window* NAC::m_pWindow = nullptr;
    Renderer* NAC::m_pRenderer = nullptr;
    Interface* NAC::m_pInterface = nullptr;
    NAC* NAC::m_pNAC = nullptr;

    static void main_loop() 
    { 
        loop(); 
    }

    NAC::NAC() {
        m_pNAC = this;
        done = false;
        loop = [&] {
            GetEvents();
            Draw();
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

    void NAC::GetEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
            {
                Shutdown();
            }
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(m_pWindow->Get_SDL_Window()))
            {
                Shutdown();
            }
            // on mouse move get delta mouse movement from the center of the screen and send it to the interface
            if (event.type == SDL_MOUSEMOTION)
            {
                // ImGuiIO& io = ImGui::GetIO();
                // io.MousePos.x = event.motion.x;
                // io.MousePos.y = event.motion.y;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    ImGui::GetIO().MouseDown[0] = true;
                }
                    
                if (event.button.button == SDL_BUTTON_RIGHT)
                    ImGui::GetIO().MouseDown[1] = true;
            }
            if (event.type == SDL_MOUSEBUTTONUP)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                    ImGui::GetIO().MouseDown[0] = false;
                    
                if (event.button.button == SDL_BUTTON_RIGHT)
                    ImGui::GetIO().MouseDown[1] = false;
            }
            if (event.type == SDL_MOUSEWHEEL)
            {
                ImGui::GetIO().MouseWheel = event.wheel.y;
            }
            if (event.type == SDL_KEYDOWN)
            {
                ImGui::GetIO().KeysDown[event.key.keysym.scancode] = true;
            }
            if (event.type == SDL_KEYUP)
            {
                ImGui::GetIO().KeysDown[event.key.keysym.scancode] = false;
            }
            if (event.type == SDL_TEXTINPUT)
            {
                ImGui::GetIO().AddInputCharactersUTF8(event.text.text);
            }
            // if mouse delta 
            
        }
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

        //initialize the interface
        m_pInterface = new Interface(GetWindow(), GetRenderer());
        if (!m_pInterface->Initialize())
            return false;

        //return success
        return true;
    }

    void NAC::Shutdown() {
        //delete the renderer
        if (m_pRenderer)
        {
            m_pRenderer->Shutdown();
            delete m_pRenderer;
        }

        //delete the window
        if (m_pWindow)
        {
            m_pWindow->Shutdown();
            delete m_pWindow;
        }

        //delete the interface
        if (m_pInterface)
        {
            m_pInterface->Shutdown();
            delete m_pInterface;
        }

        //quit the main_loop
        done = true;
    }

    void NAC::Run() {
        #ifdef __EMSCRIPTEN__
            emscripten_set_main_loop(main_loop, 0, true);
        #else
            while (!done)
                main_loop();
        #endif
    }

    void NAC::Draw() {
        m_pRenderer->New_Frame();
        m_pInterface->Draw_Interface();
        m_pRenderer->Render();       
    }
}