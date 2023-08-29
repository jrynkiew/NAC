#pragma once
#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
    #define GL_GLEXT_PROTOTYPES
    #define EGL_EGLEXT_PROTOTYPES
#else
    #include "glad/glad.h"
#endif
#include <GLFW/glfw3.h>
#include <vector>

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
            Canvas* GetInstance();
            const Vertex* GetVertices() const;
            GLsizei GetVerticesSize() const;
            void SetVertexShaderText(const char* text);
            const char*& GetVertexShaderText() const;
            void SetFragmentShaderText(const char* text);
            const char*& GetFragmentShaderText() const;
            void check_shader_error(GLuint shader);

		private:
			static Canvas* m_pInstance;
            static const Vertex vertices[3];
            static const char* vertex_shader_text;       
            static const char* fragment_shader_text;
    };
}