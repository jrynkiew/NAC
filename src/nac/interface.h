#pragma once
#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
    #define GL_GLEXT_PROTOTYPES
    #define EGL_EGLEXT_PROTOTYPES
#else
    #include "glad/glad.h"
#endif
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace _NAC
{
	class Interface
	{
		public:
			Interface();
			~Interface();

            bool Initialize(GLFWwindow* window);
            void Shutdown();
            void Draw();
            // void SetWindow(GLFWwindow* window);
            void SetTheme();
            void SetStyle();
            void SetConfig();

            Interface* GetInstance();
            GLFWwindow* GetWindow();
            ImGuiContext* GetImGuiContext();
            ImGuiIO* GetImGuiIO();
            ImGuiStyle* GetImGuiStyle();
        
        private:
            static Interface* m_pInstance;
            static GLFWwindow* m_pWindow;
            static ImGuiContext* m_pImGuiContext;
            static ImGuiIO* m_pImGuiIO;
            static ImGuiStyle* m_pImGuiStyle;
            static ImVec4* m_pImGuiColors;
    };
}

// needs to be first:
//initialized
//then config set
//then style and colors set (if needed)

