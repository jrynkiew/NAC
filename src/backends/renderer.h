#pragma once

#include <functional>
#include <vector>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include "linmath.h"
#include <stdlib.h>
#include <stdio.h>

namespace NAC
{
	class Renderer 
	{
		protected:
			Renderer();
			~Renderer();

		public:
			void Initialize(GLFWwindow* window);

			void BeginScene();
			// void EndScene();
			void Render(GLFWwindow* window);
			// // float RenderText(const std::string& text, const ImVec2& position, float size, uint32_t color, bool center = false);
			// void RenderLine(const ImVec2& from, const ImVec2& to, uint32_t color, float thickness = 1.0f);
			// void RenderCircle(const ImVec2& position, float radius, uint32_t color, float thickness = 1.0f, uint32_t segments = 16);
			// void RenderCircleFilled(const ImVec2& position, float radius, uint32_t color, uint32_t segments = 16);
			// void RenderRect(const ImVec2& from, const ImVec2& to, uint32_t color, float rounding = 0.0f, uint32_t roundingCornersFlags = ImDrawCornerFlags_All, float thickness = 1.0f);
			// void RenderRectFilled(const ImVec2& from, const ImVec2& to, uint32_t color, float rounding = 0.0f, uint32_t roundingCornersFlags = ImDrawCornerFlags_All);
			// void RenderImage(GLuint * pTexture, const ImVec2& from, const ImVec2& to, uint32_t color);
			// void RenderImageRounded(GLuint * pTexture, const ImVec2& from, const ImVec2& to, uint32_t color, float rounding = 0.0f, uint32_t roundingCornersFlags = ImDrawCornerFlags_All);
			static Renderer* GetInstance();
		private:
			// ImFont* m_pFont;
			static Renderer* m_pInstance;			
	};
}

#define g_sRenderer NAC::Renderer::GetInstance()