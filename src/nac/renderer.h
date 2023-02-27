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
			void Draw();
			void NewFrame();
			// void EndScene();
			void Render(GLFWwindow* window);
			void DisplayImage(GLuint * pTexture, const ImVec2& from, const ImVec2& to, uint32_t color);
			void LoadTexture(const char* path, GLuint* pTexture);
			// // float RenderText(const std::string& text, const ImVec2& position, float size, uint32_t color, bool center = false);
			// void RenderLine(const ImVec2& from, const ImVec2& to, uint32_t color, float thickness = 1.0f);
			// void RenderCircle(const ImVec2& position, float radius, uint32_t color, float thickness = 1.0f, uint32_t segments = 16);
			// void RenderCircleFilled(const ImVec2& position, float radius, uint32_t color, uint32_t segments = 16);
			// void RenderRect(const ImVec2& from, const ImVec2& to, uint32_t color, float rounding = 0.0f, uint32_t roundingCornersFlags = ImDrawCornerFlags_All, float thickness = 1.0f);
			// void RenderRectFilled(const ImVec2& from, const ImVec2& to, uint32_t color, float rounding = 0.0f, uint32_t roundingCornersFlags = ImDrawCornerFlags_All);
			// void RenderImage(GLuint * pTexture, const ImVec2& from, const ImVec2& to, uint32_t color);
			// void RenderImageRounded(GLuint * pTexture, const ImVec2& from, const ImVec2& to, uint32_t color, float rounding = 0.0f, uint32_t roundingCornersFlags = ImDrawCornerFlags_All);
			static Renderer* GetInstance();
			static const char* GetFragmentShaderText();
			static const char* GetVertexShaderText();
			void check_error(GLuint shader);
			void main_loop();
			void loop();
			static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
			static void error_callback(int error, const char *description);
			static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
			static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
			static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
			static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
			static void char_callback(GLFWwindow *window, unsigned int c);
		private:
			// ImFont* m_pFont;
			static Renderer* m_pInstance;
			static const char* fragment_shader_text;
			static const char* vertex_shader_text;		
	};
}

#define g_sRenderer _NAC::Renderer::GetInstance()