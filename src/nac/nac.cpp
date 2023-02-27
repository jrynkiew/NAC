#include <nac.h>

namespace _NAC
{
    Window* NAC::m_pWindow = nullptr;
    Renderer* NAC::m_pRenderer = nullptr;

    void NAC::main_loop() { loop(); }

    NAC::NAC() {
        loop = [&] {
            m_pRenderer->DrawGUI();

            glfwPollEvents();

            m_pRenderer->Render(m_pWindow->GetGLFWwindow());
        }
    }

    NAC::~NAC() {
    }

    Renderer* NAC::GetRenderer() { 
        return m_pRenderer;
    }

    Window* NAC::GetWindow() {
		return m_pWindow;
    }

    bool NAC::Initialize() {
        //initialize the window
        m_pWindow = new Window();
        if (!m_pWindow->Initialize("NAC", 1920, 1080))
            return false;

        #ifndef __EMSCRIPTEN__
            gladLoadGL();
        #endif

        glfwSwapInterval(1);
        printf("%s\n", glGetString(GL_VERSION));

        //initialize the renderer
        m_pRenderer = new Renderer(m_pWindow->GetGLFWwindow());
        if (!m_pRenderer->Initialize())
            return false;

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        //return success
        return true;
    }

    void NAC::Shutdown() {
        //delete the renderer
        if (m_pRenderer)
            delete m_pRenderer;

        //delete the window
        if (m_pWindow)
            delete m_pWindow;
    }
}