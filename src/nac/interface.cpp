#include "interface.h"

namespace _NAC
{
    Interface* Interface::m_pInstance = nullptr;
    GLFWwindow* Interface::m_pWindow = nullptr;
    ImGuiContext* Interface::m_pImGuiContext = nullptr;
    ImGuiIO* Interface::m_pImGuiIO = nullptr;
    ImGuiStyle* Interface::m_pImGuiStyle = nullptr;

    Interface::Interface() {
    }

    Interface::~Interface() {
    }

    bool Interface::Initialize(GLFWwindow* window) {
        IMGUI_CHECKVERSION();
		ImGui::CreateContext();

        m_pImGuiIO = &ImGui::GetIO(); (void)m_pImGuiIO;
        m_pImGuiStyle = &ImGui::GetStyle();

        SetConfig();
        SetStyle();

        m_pWindow = window;
		ImGui_ImplGlfw_InitForOpenGL(m_pWindow, true);

		#ifdef __EMSCRIPTEN__
			ImGui_ImplOpenGL3_Init("#version 300 es");
		#else
			ImGui_ImplOpenGL3_Init("#version 410 core");
		#endif

        return true;
    }

    void Interface::SetStyle() {
        m_pImGuiStyle->Colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_TextDisabled]           = ImVec4(0.35f, 0.44f, 0.27f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_WindowBg]               = ImVec4(0.00f, 0.00f, 0.00f, 0.54f);
		m_pImGuiStyle->Colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		m_pImGuiStyle->Colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
		m_pImGuiStyle->Colors[ImGuiCol_Border]                 = ImVec4(0.00f, 0.86f, 0.61f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_BorderShadow]           = ImVec4(0.06f, 0.94f, 0.53f, 0.56f);
		m_pImGuiStyle->Colors[ImGuiCol_FrameBg]                = ImVec4(0.15f, 0.15f, 0.15f, 0.56f);
		m_pImGuiStyle->Colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.00f, 0.86f, 0.61f, 0.23f);
		m_pImGuiStyle->Colors[ImGuiCol_FrameBgActive]          = ImVec4(0.33f, 0.53f, 0.34f, 0.00f);
		m_pImGuiStyle->Colors[ImGuiCol_TitleBg]                = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_TitleBgActive]          = ImVec4(1.00f, 0.74f, 0.00f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.12f, 0.82f, 0.49f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_MenuBarBg]              = ImVec4(0.02f, 0.02f, 0.02f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		m_pImGuiStyle->Colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.12f, 0.82f, 0.49f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(1.00f, 0.74f, 0.00f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_CheckMark]              = ImVec4(1.00f, 0.74f, 0.00f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_SliderGrab]             = ImVec4(0.12f, 0.82f, 0.49f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_SliderGrabActive]       = ImVec4(1.00f, 0.74f, 0.00f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_Button]                 = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_ButtonHovered]          = ImVec4(0.12f, 0.82f, 0.49f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_ButtonActive]           = ImVec4(1.00f, 0.74f, 0.00f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_Header]                 = ImVec4(0.00f, 0.00f, 0.00f, 0.67f);
		m_pImGuiStyle->Colors[ImGuiCol_HeaderHovered]          = ImVec4(0.12f, 0.82f, 0.49f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_HeaderActive]           = ImVec4(1.00f, 0.74f, 0.00f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_Separator]              = ImVec4(0.35f, 0.44f, 0.27f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.18f, 0.23f, 0.20f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_SeparatorActive]        = ImVec4(1.00f, 0.74f, 0.00f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_ResizeGrip]             = ImVec4(0.12f, 0.82f, 0.49f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.12f, 0.82f, 0.49f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_ResizeGripActive]       = ImVec4(1.00f, 0.74f, 0.00f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_Tab]                    = ImVec4(1.00f, 0.74f, 0.00f, 0.12f);
		m_pImGuiStyle->Colors[ImGuiCol_TabHovered]             = ImVec4(0.12f, 0.82f, 0.49f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_TabActive]              = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_TabUnfocused]           = ImVec4(0.00f, 0.00f, 0.00f, 0.97f);
		m_pImGuiStyle->Colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.01f, 0.77f, 0.46f, 0.16f);
		m_pImGuiStyle->Colors[ImGuiCol_DockingPreview]         = ImVec4(0.26f, 0.59f, 0.98f, 0.22f);
		m_pImGuiStyle->Colors[ImGuiCol_DockingEmptyBg]         = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.78f, 0.87f, 0.98f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.57f, 0.57f, 0.64f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_TableBorderLight]       = ImVec4(0.68f, 0.68f, 0.74f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		m_pImGuiStyle->Colors[ImGuiCol_TableRowBgAlt]          = ImVec4(0.30f, 0.30f, 0.30f, 0.09f);
		m_pImGuiStyle->Colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		m_pImGuiStyle->Colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		m_pImGuiStyle->Colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		m_pImGuiStyle->Colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		m_pImGuiStyle->Colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		m_pImGuiStyle->Colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

        m_pImGuiStyle->WindowPadding = ImVec2(15.0f, 15.0f);
		m_pImGuiStyle->FrameRounding = 3.0f;
		m_pImGuiStyle->ItemSpacing = ImVec2(6.0f, 6.0f);
    }

    void Interface::SetConfig() {
		m_pImGuiIO->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		m_pImGuiIO->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		#ifndef __EMSCRIPTEN__
			m_pImGuiIO->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
			if (m_pImGuiIO->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				m_pImGuiStyle->WindowRounding = 0.0f;
				m_pImGuiStyle->Colors[ImGuiCol_WindowBg].w = 1.0f;
			}
		#endif
    }

    void Interface::Shutdown() {
    }

    void Interface::Draw() {
		ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		static bool show_demo_window = true;
		static bool show_another_window = false;
		static bool showDemo = false;
        static float f = 0.0f;
        static int counter = 0;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
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

   
		ImVec2 window_pos = ImGui::GetWindowPos(); 
        ImVec2 window_size = ImGui::GetWindowSize(); 
        ImVec2 window_center = ImVec2(window_pos.x + window_size.x * 0.5f, window_pos.y + window_size.y * 0.5f); 
        ImGui::GetBackgroundDrawList()->AddCircle(window_center, window_size.x * 0.6f, IM_COL32(255, 0, 0, 200), 0, 10 + 4); 
        ImGui::GetForegroundDrawList()->AddCircle(window_center, window_size.y * 0.6f, IM_COL32(0, 255, 0, 200), 0, 10);
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        static float sz = 36.0f; 
        static float thickness = 4.0f; 
        static ImVec4 col = ImVec4(1.0f, 1.0f, 0.4f, 1.0f); 
        const ImVec2 p = ImGui::GetCursorScreenPos(); 
        const ImU32 col32 = ImColor(col); 
        float x = p.x + 4.0f, y = p.y + 4.0f;
        draw_list->AddCircle(ImVec2(x+sz*0.5f, y+sz*0.5f), sz*0.5f, col32, 6, thickness);

		ImGui::Begin("Example");
        if (ImGui::Button("Show/Hide ImGui demo"))
        showDemo = !showDemo;
        ImGui::End();
        if (showDemo)
        ImGui::ShowDemoWindow(&showDemo);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if (m_pImGuiIO->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    Interface* Interface::GetInstance() {
        if (!m_pInstance)
            m_pInstance = new Interface();

        return m_pInstance;
    }

    GLFWwindow* Interface::GetWindow() {
        return m_pWindow;
    }

    ImGuiContext* Interface::GetImGuiContext() {
        return m_pImGuiContext;
    }

    ImGuiIO* Interface::GetImGuiIO() {
        return m_pImGuiIO;
    }

    ImGuiStyle* Interface::GetImGuiStyle() {
        return m_pImGuiStyle;
    }
}

