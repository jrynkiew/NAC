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
			void RenderCanvas();
			void RenderInterface();
			static Renderer* GetInstance();
			static Canvas* GetCanvas();
			static Interface* GetInterface();
		private:
			static Renderer* m_pInstance;
			static Canvas* m_Canvas;
			static Interface* m_Interface;
	};
}

#define g_sRenderer _NAC::Renderer::GetInstance()