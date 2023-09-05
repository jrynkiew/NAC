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
            GLuint vertex_buffer, index_buffer, vertex_shader, fragment_shader, program;
            mat4x4 m, p, mvp;
            Context context;
            static const char* vertex_shader_text;       
            static const char* fragment_shader_text;
            
            void run_program();
            void prepare_shader();
            void prepare_fragment_shader();
            void prepare_vertex_shader();
            void prepare_vertex_buffer();
            void prepare_index_buffer();
            void prepare_program();
            
            void shader_error_callback(int error, const char *description);
            void program_error_callback(int error, const char *description);
    };
}