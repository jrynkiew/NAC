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

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::RenderCanvas()
	{
		m_Canvas->Draw();
	}

	void Renderer::RenderInterface()
	{
		m_Interface->Draw();
	}

	void Renderer::Render(GLFWwindow* window)
	{
		Clear();
		RenderCanvas();
		RenderInterface();
		glfwPollEvents();
        glfwSwapBuffers(window);
	}
}