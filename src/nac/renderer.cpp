#include "renderer.h"

namespace _NAC
{
	Renderer* Renderer::m_pInstance = nullptr;
    Canvas* Renderer::m_Canvas = nullptr;
	Interface* Renderer::m_Interface = nullptr;
	GLFWwindow* Renderer::m_pWindow = nullptr;

	Renderer::Renderer(GLFWwindow* window)
	{
		//set window
		m_pWindow = window;

		//set the instance
		m_pInstance = this;
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
			m_pInstance = new Renderer(m_pWindow);

		return m_pInstance;
	}

    Canvas* Renderer::GetCanvas()
    {
        if (!m_Canvas)
            m_Canvas = new Canvas(m_pWindow);

        return m_Canvas;
    }

	Interface* Renderer::GetInterface()
	{
		if (!m_Interface)
			m_Interface = new Interface(m_pWindow);

		return m_Interface;
	}

	bool Renderer::Initialize()
	{
		//initialize Interface
		m_Interface = new Interface(m_pWindow);
		if(!m_Interface->Initialize())
		{
			printf("Error during NAC gui initialization!\n");
			m_Interface->Shutdown();
			return false;
		}

		glEnable(GL_DEPTH_TEST); // Enable depth testing

		//initialize Canvas
		m_Canvas = new Canvas(m_pWindow);
		if(!m_Canvas->Initialize())
		{
			printf("Error during NAC canvas initialization!\n");
			m_Canvas->Shutdown();
			return false;
		}

		return true;
	}

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::RenderCanvas()
	{
		int width, height;
		glfwGetFramebufferSize(m_pWindow, &width, &height);
		m_Canvas->Draw(width, height);
	}

	void Renderer::RenderInterface()
	{
		m_Interface->Draw();
	}

	void Renderer::Render()
	{
		Clear();
		RenderCanvas();
		RenderInterface();
		glfwPollEvents();
        glfwSwapBuffers(m_pWindow);
	}
}