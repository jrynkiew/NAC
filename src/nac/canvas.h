#pragma once
#include <GLFW/glfw3.h>

struct Vertex {
    float x, y;
    float r, g, b;
};

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
            const Vertex* GetVertices() const;
            GLsizei GetVerticesSize() const;
            void SetVertexShaderText(const char* text);
            const char* GetVertexShaderText() const;
            void SetFragmentShaderText(const char* text);
            const char* GetFragmentShaderText() const;

		private:
			static Canvas* m_pInstance;
            static const Vertex vertices[3];
            const char* vertex_shader_text;          
            const char* fragment_shader_text;
    };
}