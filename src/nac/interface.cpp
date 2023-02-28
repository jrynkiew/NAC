
#include "interface.h"

namespace _NAC {
    ImGuiIO* Interface::m_io = nullptr;
    SDL_Renderer* Interface::m_Renderer = nullptr;
	SDL_Window* Interface::m_Window = nullptr;

    // constructor
    Interface::Interface(SDL_Window* window, SDL_Renderer* renderer) 
    {
        m_Renderer = renderer;
        m_Window = window;
    }
    
    Interface::~Interface() 
    {
    }

    bool Interface::Initialize()
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        m_io = &ImGui::GetIO(); (void)m_io;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // Setup Platform/Renderer backends
        ImGui_ImplSDL2_InitForSDLRenderer(m_Window, m_Renderer);
        ImGui_ImplSDLRenderer_Init(m_Renderer);

        return true;
    }

    ImGuiIO* Interface::Get_ImGui_Interface() 
    { 
        return m_io; 
    }
}