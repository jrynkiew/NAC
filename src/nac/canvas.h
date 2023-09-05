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

struct Context {
  unsigned int shader_program;
  unsigned int vao;
  GLFWwindow* window;
 
  unsigned int uniform_transform;
};

namespace _NAC
{
	class Canvas
	{
		public:
			Canvas();
			~Canvas();
			bool Initialize(GLFWwindow* window);   
            void Draw();
            void Shutdown();
            
            const char*& GetVertexShaderText() const;
            const char*& GetFragmentShaderText() const;  

            void SetVertexShaderText(const char* text);
            void SetFragmentShaderText(const char* text);

		private:
            int width, height
            GLuint vertex_buffer, index_buffer, vertex_shader, fragment_shader;
            mat4x4 m, p, mvp;
            Context context;
            static const char* vertex_shader_text;       
            static const char* fragment_shader_text;
            
            const unsigned int triangles = 6 * 2;   // Number of triangles rendered
            const unsigned int verticies_index = 0;
            const unsigned int colors_index = 1;

            void run_program();
            
            void shader_error_callback(int error, const char *description);
            void program_error_callback(int error, const char *description);
            void check_shader_error(GLuint shader);
            void check_program_error(GLuint program);
    };
}