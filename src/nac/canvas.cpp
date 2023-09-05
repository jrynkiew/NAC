#include "canvas.h"

namespace _NAC
{
    const char* Canvas::vertex_shader_text =
        "attribute vec3 Position;\n"
        "attribute vec3 inColor;\n"

        "uniform mat4 transform;\n"

        "varying vec3 Color;\n"

        "void main()\n"
        "{\n"
        "    gl_Position = transform * vec4(Position, 1.0);\n"
        "    Color = inColor;\n"
        "}\n";
    #ifdef __EMSCRIPTEN__
    const char* Canvas::fragment_shader_text =
        "precision mediump float;\n"
        "attribute vec4 Color;\n"

        "void main()\n"
        "{\n"
        "    gl_FragColor = Color;\n"
        "}\n";
    #else
    const char* Canvas::fragment_shader_text =
        "attribute vec4 Color;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = Color;\n"
        "}\n";
    #endif

    Canvas::Canvas() {
    }

    Canvas::~Canvas() {
    }

    bool Canvas::Initialize(GLFWwindow* window) {
        context.window = window;
        
        glEnable(GL_DEPTH_TEST);

        float vertices[] = {
            // Front face
            0.5,  0.5,  0.5,
            -0.5,  0.5,  0.5,
            -0.5, -0.5,  0.5,
            0.5, -0.5,  0.5,

            // Back face
            0.5,  0.5, -0.5,
            -0.5,  0.5, -0.5,
            -0.5, -0.5, -0.5,
            0.5, -0.5, -0.5,
        };

        float vertex_colors[] = {
            1.0, 0.4, 0.6,
            1.0, 0.9, 0.2,
            0.7, 0.3, 0.8,
            0.5, 0.3, 1.0,

            0.2, 0.6, 1.0,
            0.6, 1.0, 0.4,
            0.6, 0.8, 0.8,
            0.4, 0.8, 0.8,
        };

        unsigned short triangle_indices[] = {
            // Front
            0, 1, 2,
            2, 3, 0,

            // Right
            0, 3, 7,
            7, 4, 0,

            // Bottom
            2, 6, 7,
            7, 3, 2,

            // Left
            1, 5, 6,
            6, 2, 1,

            // Back
            4, 7, 6,
            6, 5, 4,

            // Top
            5, 1, 0,
            0, 4, 5,
        };

        glGenVertexArrays(1, &context.vao);
        glBindVertexArray(context.vao);

        unsigned int triangles_ibo;
        glGenBuffers(1, &triangles_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangles_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof triangle_indices, triangle_indices, GL_STATIC_DRAW);

        unsigned int verticies_vbo;
        glGenBuffers(1, &verticies_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, verticies_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(verticies_index, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(verticies_index);

        unsigned int colors_vbo;
        glGenBuffers(1, &colors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof vertex_colors, vertex_colors, GL_STATIC_DRAW);

        glVertexAttribPointer(colors_index, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(colors_index);

        // Unbind to prevent accidental modification
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &(GetVertexShaderText()), NULL);
        glCompileShader(vertex_shader);
        check_shader_error(vertex_shader);

        GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &(GetFragmentShaderText()), NULL);
        glCompileShader(fragment_shader);
        check_shader_error(fragment_shader);

        context.shader_program = glCreateProgram();
        glAttachShader(context.shader_program, vertex_shader);
        glAttachShader(context.shader_program, fragment_shader);
        glLinkProgram(context.shader_program);

        context.uniform_transform = glGetUniformLocation(context.shader_program, "transform");
        return true;
    }

    void Canvas::Shutdown() {
    }

    void Canvas::Draw() {
        run_program();
    }

    const char*& Canvas::GetVertexShaderText() const {
        return vertex_shader_text;
    }

    const char*& Canvas::GetFragmentShaderText() const {
        return fragment_shader_text;
    }

    void Canvas::run_program() {
        glfwGetFramebufferSize(context.window, &width, &height);
        ratio = width / (float)height;
        glViewport(0, 0, width, height);

        mat4x4_identity(m);
        mat4x4_rotate_Z(m, m, (float)glfwGetTime());
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_mul(mvp, p, m);

        glUseProgram(context.shader_program);
        glUniformMatrix4fv(context.uniform_transform, 1, GL_FALSE, (const GLfloat *)mvp);
        
        glBindVertexArray(context.vao);
        glDrawElements(GL_TRIANGLES, triangles * 3, GL_UNSIGNED_SHORT, NULL);
    }

    void Canvas::check_shader_error(GLuint shader) {
        GLint result;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            GLint log_length;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
            std::vector<GLchar> log(log_length);

            GLsizei length;
            glGetShaderInfoLog(shader, log.size(), &length, log.data());

            shader_error_callback(0, log.data());
        }
    }

    void Canvas::check_program_error(GLuint program) {
        GLint result;
        glGetProgramiv(program, GL_LINK_STATUS, &result);
        if (result == GL_FALSE)
        {
            GLint log_length;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
            std::vector<GLchar> log(log_length);

            GLsizei length;
            glGetProgramInfoLog(program, log.size(), &length, log.data());

            program_error_callback(0, log.data());
        }
    }

    void Canvas::shader_error_callback(int error, const char *description) {
        fprintf(stderr, "Error in shader: %s\n", description);
    }

    void Canvas::program_error_callback(int error, const char *description) {
        fprintf(stderr, "Error in program: %s\n", description);
    }
}