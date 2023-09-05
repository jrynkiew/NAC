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
#include <stdio.h>
#include "linmath.h"

namespace _NAC
{
	class Canvas
	{
		public:
			Canvas(GLFWwindow* window);
			~Canvas();

			bool Initialize();
			void Shutdown();
			void Draw();
		private:
            GLint model_location, view_location, projection_location;
            GLuint vertexShader, fragmentShader, shaderProgram;
            mat4x4 model, view, projection;
            unsigned int VAO, VBO, EBO;
            static const char* fragmentShaderSource;       
            static const char* vertexShaderSource;
            GLFWwindow* m_pWindow;
            int width, height;
            float ratio;

            void run_program();

            static float cubeVertices[];
            static unsigned int cubeIndices[];
    };
}
