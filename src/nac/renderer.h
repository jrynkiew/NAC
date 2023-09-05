#pragma once
#include "linmath.h"
#include "canvas.h"
#include "interface.h"

namespace _NAC
{
	class Renderer 
	{
		public:
			Renderer(GLFWwindow* window);
			~Renderer();

			bool Initialize();
			void Shutdown();
			void Render();
			void Clear();
			void RenderCanvas();
			void RenderInterface();
			static Renderer* GetInstance();
			static Canvas* GetCanvas();
			static Interface* GetInterface();
			void SetMousePosition(double x, double y);
		private:
			static Renderer* m_pInstance;
			static Canvas* m_Canvas;
			static Interface* m_Interface;
			static GLFWwindow* m_pWindow;
	};
}

#define g_sRenderer _NAC::Renderer::GetInstance()