#include <nac.h>

namespace _NAC
{
    Window* NAC::m_Window = nullptr;
    Renderer* NAC::m_Renderer = nullptr;

    NAC::NAC() {
    }

    NAC::~NAC() {
    }

    Renderer* NAC::GetRenderer() { 
        return m_Renderer;
    }

    Window* NAC::GetWindow() {
		return m_Window;
    }

    bool NAC::Initialize() {
        //initialize the window
        m_Window = new Window();
        if (!m_Window->Initialize("NAC", 1920, 1080))
            return false;
            
        #ifndef __EMSCRIPTEN__
            gladLoadGL();
        #endif

        glfwSwapInterval(1);
        printf("%s\n", glGetString(GL_VERSION));

        //initialize the renderer
        m_Renderer = new Renderer();
        if (!m_Renderer->Initialize(m_Window->GetGLFWwindow()))
            return false;

        //return success
        return true;
    }

    void NAC::Shutdown() {
        //delete the renderer
        if (m_Renderer)
            delete m_Renderer;

        //delete the window
        if (m_Window)
            delete m_Window;
    }
}