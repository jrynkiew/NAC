#pragma once

#include "linmath.h"

#include "canvas.h"
#include "interface.h"

namespace _NAC
{
	class Renderer 
	{
		public:
			Renderer();
			~Renderer();

			bool Initialize(GLFWwindow* window);
			void Shutdown();
			void Render(GLFWwindow* window);
			void BeginScene();
			void RenderCanvas();
			void RenderInterface();
			static Renderer* GetInstance();
			static Canvas* GetCanvas();
		private:
			static Renderer* m_pInstance;
			static Canvas* m_Canvas;
	};
}

#define g_sRenderer _NAC::Renderer::GetInstance()