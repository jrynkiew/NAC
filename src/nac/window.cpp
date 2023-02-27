#include "window.h"

namespace _NAC {

    //static instance
    Window* Window::m_Instance = nullptr;
    GLFWwindow* Window::m_Window = nullptr;

	//constructor
	Window::Window()
    {
    }

	//destructor
	Window::~Window()
	{
	}

    //gets the Window
    GLFWwindow* Window::GetGLFWwindow() {
        return m_Window;
    }

    //gets the Instance
    Window* Window::GetInstance() {
        return m_Instance;
    }

	//creates the window and the opengl context
	bool Window::Initialize(const char* windowTitle, int width, int height)
	{
        //set the error callback
        glfwSetErrorCallback(error_callback);

		//set the width and height
		m_Width = width;
		m_Height = height;

		//initialize glfw
		if (!glfwInit())
			return false;

        //set the opengl version
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

		//create the window
		m_Window = glfwCreateWindow(m_Width, m_Height, windowTitle, NULL, NULL);
		if (!m_Window)
		{
			glfwTerminate();
			return false;
		}
        
        //set the key callback
        glfwSetKeyCallback(m_Window, key_callback);

		//make the window the current context
		glfwMakeContextCurrent(m_Window);

		//return success
		return true;
	}

    //destroys the window and the opengl context
    void Window::Shutdown()
    {

        //destroy the window
        if (m_Window)
        {
            glfwDestroyWindow(m_Window);
            m_Window = nullptr;
        }

        //terminate glfw
        glfwTerminate();
    }
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}