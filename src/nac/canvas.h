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

            const Vertex* getVertices() const {
                return vertices;
            }
		private:
			static Canvas* m_pInstance;

            static const Vertex vertices[3];
        
            static const char* vertex_shader;
            static const char* fragment_shader;
    };
}