#include "renderer.h"

namespace _NAC
{
	Renderer* Renderer::m_pInstance = nullptr;
    Canvas* Renderer::m_Canvas = nullptr;

	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::Shutdown() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		glfwTerminate();
	}

	Renderer* Renderer::GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new Renderer();

		return m_pInstance;
	}

    Canvas* Renderer::GetCanvas()
    {
        if (!m_Canvas)
            m_Canvas = new Canvas();

        return m_Canvas;
    }

	Interface* Renderer::GetInterface()
	{
		if (!m_Interface)
			m_Interface = new Interface();

		return m_Interface;
	}

	bool Renderer::Initialize(GLFWwindow* window)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		ImGuiStyle* style = &ImGui::GetStyle();

		#ifndef __EMSCRIPTEN__
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				style->WindowRounding = 0.0f;
				style->Colors[ImGuiCol_WindowBg].w = 1.0f;
			}
		#endif

		ImGui_ImplGlfw_InitForOpenGL(window, true);

		#ifdef __EMSCRIPTEN__
			ImGui_ImplOpenGL3_Init("#version 300 es");
		#else
			ImGui_ImplOpenGL3_Init("#version 410 core");
		#endif

		// ImGui::StyleColorsDark();

		ImVec4* colors = style->Colors;
		colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled]           = ImVec4(0.35f, 0.44f, 0.27f, 1.00f);
		colors[ImGuiCol_WindowBg]               = ImVec4(0.00f, 0.00f, 0.00f, 0.54f);
		colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
		colors[ImGuiCol_Border]                 = ImVec4(0.00f, 0.86f, 0.61f, 1.00f);
		colors[ImGuiCol_BorderShadow]           = ImVec4(0.06f, 0.94f, 0.53f, 0.56f);
		colors[ImGuiCol_FrameBg]                = ImVec4(0.15f, 0.15f, 0.15f, 0.56f);
		colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.00f, 0.86f, 0.61f, 0.23f);
		colors[ImGuiCol_FrameBgActive]          = ImVec4(0.33f, 0.53f, 0.34f, 0.00f);
		colors[ImGuiCol_TitleBg]                = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_TitleBgActive]          = ImVec4(1.00f, 0.74f, 0.00f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.12f, 0.82f, 0.49f, 1.00f);
		colors[ImGuiCol_MenuBarBg]              = ImVec4(0.02f, 0.02f, 0.02f, 1.00f);
		colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.12f, 0.82f, 0.49f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(1.00f, 0.74f, 0.00f, 1.00f);
		colors[ImGuiCol_CheckMark]              = ImVec4(1.00f, 0.74f, 0.00f, 1.00f);
		colors[ImGuiCol_SliderGrab]             = ImVec4(0.12f, 0.82f, 0.49f, 1.00f);
		colors[ImGuiCol_SliderGrabActive]       = ImVec4(1.00f, 0.74f, 0.00f, 1.00f);
		colors[ImGuiCol_Button]                 = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_ButtonHovered]          = ImVec4(0.12f, 0.82f, 0.49f, 1.00f);
		colors[ImGuiCol_ButtonActive]           = ImVec4(1.00f, 0.74f, 0.00f, 1.00f);
		colors[ImGuiCol_Header]                 = ImVec4(0.00f, 0.00f, 0.00f, 0.67f);
		colors[ImGuiCol_HeaderHovered]          = ImVec4(0.12f, 0.82f, 0.49f, 1.00f);
		colors[ImGuiCol_HeaderActive]           = ImVec4(1.00f, 0.74f, 0.00f, 1.00f);
		colors[ImGuiCol_Separator]              = ImVec4(0.35f, 0.44f, 0.27f, 1.00f);
		colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.18f, 0.23f, 0.20f, 1.00f);
		colors[ImGuiCol_SeparatorActive]        = ImVec4(1.00f, 0.74f, 0.00f, 1.00f);
		colors[ImGuiCol_ResizeGrip]             = ImVec4(0.12f, 0.82f, 0.49f, 1.00f);
		colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.12f, 0.82f, 0.49f, 1.00f);
		colors[ImGuiCol_ResizeGripActive]       = ImVec4(1.00f, 0.74f, 0.00f, 1.00f);
		colors[ImGuiCol_Tab]                    = ImVec4(1.00f, 0.74f, 0.00f, 0.12f);
		colors[ImGuiCol_TabHovered]             = ImVec4(0.12f, 0.82f, 0.49f, 1.00f);
		colors[ImGuiCol_TabActive]              = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_TabUnfocused]           = ImVec4(0.00f, 0.00f, 0.00f, 0.97f);
		colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.01f, 0.77f, 0.46f, 0.16f);
		colors[ImGuiCol_DockingPreview]         = ImVec4(0.26f, 0.59f, 0.98f, 0.22f);
		colors[ImGuiCol_DockingEmptyBg]         = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.78f, 0.87f, 0.98f, 1.00f);
		colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.57f, 0.57f, 0.64f, 1.00f);
		colors[ImGuiCol_TableBorderLight]       = ImVec4(0.68f, 0.68f, 0.74f, 1.00f);
		colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_TableRowBgAlt]          = ImVec4(0.30f, 0.30f, 0.30f, 0.09f);
		colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

		style->FrameRounding = 3.0f;
		style->ItemSpacing = ImVec2(6.0f, 6.0f);

    	glEnable(GL_CULL_FACE);

		return true;
	}

	void Renderer::Render(GLFWwindow* window)
	{
		ImGui::Render();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
        glfwSwapBuffers(window);
	}

	void Renderer::BeginScene()
	{
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
	}
}