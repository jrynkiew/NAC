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
			void Draw(int width, int height);
            void SetMousePosition(double x, double y);
		private:
            GLint modelLoc, viewLoc, projectionLoc;
            GLuint vertexShader, fragmentShader, shaderProgram;
            mat4x4 model, view, projection;
            unsigned int VAO, VBO, EBO;
            static const char* fragmentShaderSource;       
            static const char* vertexShaderSource;
            GLFWwindow* m_pWindow;
            double m_MouseX, m_MouseY, lastMouseX, lastMouseY = 0.0f;
            float aspectRatio;
            float rotationSpeed;
            static float cubeVertices[];
            static unsigned int cubeIndices[];
    };
}
