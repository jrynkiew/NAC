#pragma once

#define NAC_RENDERER_WINDOW_H

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#else
#include "glad/glad.h"
#endif

#include <functional>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>



namespace _NAC {
    //definition of class that creates a window and sets up the opengl context
    class Window
    {
    public:
        //constructor
        Window();
        //destructor
        ~Window();

        //creates the window and the opengl context
        bool Initialize(const char* windowTitle, int width, int height);
        //destroys the window and the opengl context
        void Shutdown();
        //gets the width of the window
        int GetWidth();
        //gets the height of the window
        int GetHeight();
        //gets the window
        GLFWwindow* GetGLFWwindow();
        //gets the instance
        Window* GetInstance();

    private:
        //the width of the window
        int m_Width;
        //the height of the window
        int m_Height;
        //the window
        static GLFWwindow* m_Window;
        //the instance
        static Window* m_Instance;
    };

    #define g_sWindow _NAC::Window::GetInstance();
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void error_callback(int error, const char *description);