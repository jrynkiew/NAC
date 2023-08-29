#include "renderer.h"

namespace _NAC
{
	Renderer* Renderer::m_pInstance = nullptr;
    Canvas* Renderer::m_Canvas = nullptr;
	Interface* Renderer::m_Interface = nullptr;

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
		//initialize Interface
		m_Interface = new Interface();
		if(!m_Interface->Initialize(window))
		{
			printf("Error during NAC gui initialization!\n");
			m_Interface->Shutdown();
			return false;
		}

    	glEnable(GL_CULL_FACE);

		//initialize Canvas
		m_Canvas = new Canvas();
		if(!m_Canvas->Initialize(window))
		{
			printf("Error during NAC canvas initialization!\n");
			m_Canvas->Shutdown();
			return false;
		}

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