#include "window.h"

namespace _NAC {

    //static instance
    Window* Window::m_Instance = nullptr;
    GLFWwindow* Window::m_Window = nullptr;

	//constructor
	Window::Window(const char* title, int width, int height)
    {
        //set the instance
        m_Instance = this;

        //set the width and height
        m_Width = width;
        m_Height = height;

        // Copy the window title characters one by one
        size_t i = 0;
        while (title[i] != '\0' && i < sizeof(windowTitle) - 1) {
            windowTitle[i] = title[i];
            i++;
        }
        windowTitle[i] = '\0'; // Null-terminate the copied string
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
	bool Window::Initialize()
	{
        //set the error callback
        glfwSetErrorCallback(error_callback);

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
        //set the mouse move callback
        glfwSetCursorPosCallback(m_Window, mouse_callback);

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
        exit(EXIT_SUCCESS);
    }

    void Window::SetMousePosition(double x, double y)
	{
		m_MouseX = x;
		m_MouseY = y;
		#ifdef __EMSCRIPTEN__
        	emscripten_log(EM_LOG_CONSOLE, "mouseX: %f, mouseY: %f", m_MouseX, m_MouseY);
    	#else
			printf("mouseX: %f, mouseY: %f", m_MouseX, m_MouseY);
		#endif
	}

    double Window::GetMouseX()
    {
        return m_MouseX;
    }

    double Window::GetMouseY()
    {
        return m_MouseY;
    }

    void Window::mouse_callback(GLFWwindow *window, double xpos, double ypos)
    {
        m_Instance->SetMousePosition(xpos, ypos);
    }

    void Window::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    void Window::error_callback(int error, const char *description)
    {
        fprintf(stderr, "Error: %s\n", description);
    }
}

