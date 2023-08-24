#pragma once
#include <GLFW/glfw3.h>

namespace _NAC
{
	class Canvas
	{
		public:
			Canvas();
			~Canvas();

			bool Initialize(GLFWwindow* window);
			void Shutdown();
			void Draw();

            static Canvas* GetInstance();
            const char* GetVertexShader();
            const char* GetFragmentShader();
            const struct { float x, y; float r, g, b; }* GetVertices();

		private:
			static Canvas* m_pInstance;
        
            static const char* vertex_shader;
            static const char* fragment_shader;
            static const struct { float x, y; float r, g, b; } vertices[3] = {
                {-0.6f, -0.6f, 1.f, 0.f, 0.f},
                {0.6f, -0.6f, 0.f, 1.f, 0.f},
                {0.f, 0.6f, 0.f, 0.f, 1.f}};
            };
}