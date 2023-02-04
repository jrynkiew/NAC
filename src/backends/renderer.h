#pragma once

#include "imgui.h"
#if defined(__EMSCRIPTEN__)
// #include "imgui_impl_sdl.h"
#include <emscripten.h>
// #include <SDL.h>
// #include <SDL_opengles2.h>
#else
#include "imgui_impl_glfw.h"
#endif
#include "imgui_impl_opengl3.h"
#include <stdio.h>

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>            // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>          // Initialize with gladLoadGL()
#endif
#include <math.h>


namespace NAC
{
	class Renderer 
	{
		protected:
			Renderer();
			~Renderer();

		public:
			// void Initialize();

			void BeginScene();
			// void EndScene();
			void drawCircle();
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