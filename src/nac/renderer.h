#pragma once

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#else
#include "glad/glad.h"
#endif

#include <vector>

#include <GLFW/glfw3.h>

#include "linmath.h"

#include "canvas.h"
#include "interface.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace _NAC
{
	class Renderer 
	{
		public:
			Renderer();
			~Renderer();

			bool Initialize(GLFWwindow* window);
			void Shutdown();
			void BeginScene();
			void Render(GLFWwindow* window);
			static Renderer* GetInstance();
		private:
			static Renderer* m_pInstance;	
	};
}

#define g_sRenderer _NAC::Renderer::GetInstance()