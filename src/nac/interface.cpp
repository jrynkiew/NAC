
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
        Shutdown();
    }

    bool Interface::Initialize()
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        m_io = &ImGui::GetIO(); (void)m_io;
        m_io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        m_io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport

        #ifndef __EMSCRIPTEN__
			m_io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		
			ImGuiStyle& style = ImGui::GetStyle();
			if (m_io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				style.WindowRounding = 0.0f;
				style.Colors[ImGuiCol_WindowBg].w = 1.0f;
			}
		#endif

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // Setup Platform/Renderer backends
        ImGui_ImplSDL2_InitForSDLRenderer(m_Window, m_Renderer);
        ImGui_ImplSDLRenderer_Init(m_Renderer);

        show_demo_window = true;
        show_another_window = false;
        clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        return true;
    }

    ImGuiIO* Interface::Get_ImGui_Interface() 
    { 
        return m_io; 
    }

    void Interface::Draw_Interface()
    {
        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        ImGui::Render();
        SDL_RenderSetScale(m_Renderer, m_io->DisplayFramebufferScale.x, m_io->DisplayFramebufferScale.y);
        SDL_SetRenderDrawColor(m_Renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
    
        return;
    }

	void Interface::Shutdown() 
    {
        ImGui::DestroyContext();
        return;
    }
}