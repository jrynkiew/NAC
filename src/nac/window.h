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
        Window(const char* title, int width, int height);
        //destructor
        ~Window();

        //creates the window and the opengl context
        bool Initialize();
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
        //get the X mouse position
        double GetMouseX();
        //get the Y mouse position
        double GetMouseY();

    private:
        //the width of the window
        int m_Width;
        //the height of the window
        int m_Height;
        //the window
        static GLFWwindow* m_Window;
        //the window title
        char windowTitle[256];
        //the instance
        static Window* m_Instance;
        //the mouse position
        double m_MouseX, m_MouseY;
        //sets the mouse position
        void SetMousePosition(double x, double y);
    };

    #define g_sWindow _NAC::Window::GetInstance();
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void error_callback(int error, const char *description);