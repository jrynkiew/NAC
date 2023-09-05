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
    vec3 pos;
    vec3 color;

    Vertex() {}

    Vertex(float x, float y)
    {
        pos.Add(x, y, 0.0f);

        float red   = (float)rand() / (float)RAND_MAX;
        float green = (float)rand() / (float)RAND_MAX;
        float blue  = (float)rand() / (float)RAND_MAX;
        color.Add(red, green, blue);
    }
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
            const Vertex* GetVertices() const;
            GLsizei GetVerticesSize() const;
            const char*& GetVertexShaderText() const;
            const char*& GetFragmentShaderText() const;
            
            void SetVertexShaderText(const char* text);
            void SetFragmentShaderText(const char* text);

			bool Initialize(GLFWwindow* window);
			void Shutdown();
			void Draw();
           
            void check_shader_error(GLuint shader);
            void check_program_error(GLuint program);    
                    

		private:
            GLuint vertex_buffer, index_buffer, vertex_shader, fragment_shader, program;
            GLuint gWorldLocation;
            GLFWwindow* m_pWindow;
            int width, height;
            mat4x4 World;
            mat4x4 m, p, mvp;
            float ratio;
            float scale;
            static Canvas* m_pInstance;
            Vertex Vertices[19];
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