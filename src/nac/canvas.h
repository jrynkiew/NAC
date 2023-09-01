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

            //Getters and Setters
            Canvas* GetInstance();
            Vertex* GetVertices() const;
            GLsizei GetVerticesSize() const;
            const char*& GetVertexShaderText() const;
            const char*& GetFragmentShaderText() const;
            
            void SetVertexShaderText(const char* text);
            void SetFragmentShaderText(const char* text);
            void SetVertices(Vertex* vertices);

			bool Initialize(GLFWwindow* window);
			void Shutdown();
			void Draw();
           
            void check_shader_error(GLuint shader);
            void check_program_error(GLuint program);    
                    

		private:
            GLuint vertex_buffer, vertex_shader, fragment_shader, program;
            GLint mvp_location, vpos_location, vcol_location;
            GLFWwindow* m_pWindow;
            int width, height;
            mat4x4 m, p, mvp;
            float ratio;
            static Canvas* m_pInstance;
            static Vertex vertices[3];
            static const char* vertex_shader_text;       
            static const char* fragment_shader_text;
            
            void run_program();
            void prepare_shader();
            void prepare_vertex_buffer();
            void prepare_vertex_shader();
            void prepare_fragment_shader();
            void prepare_program();
            
            void shader_error_callback(int error, const char *description);
            void program_error_callback(int error, const char *description);
    };
}