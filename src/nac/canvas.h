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
            const char* GetVertexShader();
            const char* GetFragmentShader();

            const Vertex* GetVertices() const {
                return vertices;
            }
            GLsizei GetVerticesSize() const {
                return sizeof(vertices);
            }
            GLsizei GetVerticesCount() const {
                return sizeof(vertices) / sizeof(Vertex);
            }
		private:
			static Canvas* m_pInstance;

            static const Vertex vertices[3];
        
            static const char* vertex_shader;
            static const char* fragment_shader;
    };
}