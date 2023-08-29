#include "canvas.h"

namespace _NAC
{
    Canvas* Canvas::m_pInstance = nullptr;
    const char* Canvas::vertex_shader_text =
        "uniform mat4 MVP;\n"
        "attribute vec3 vCol;\n"
        "attribute vec2 vPos;\n"
        "varying vec3 color;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
        "    color = vCol;\n"
        "}\n";
    #ifdef __EMSCRIPTEN__
    const char* Canvas::fragment_shader_text =
        "precision mediump float;\n"
        "varying vec3 color;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = vec4(color, 1.0);\n"
        "}\n";
    #else
    const char* Canvas::fragment_shader_text =
        "varying vec3 color;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = vec4(color, 1.0);\n"
        "}\n";
    #endif

    const Vertex Canvas::vertices[3] = {
        {-0.6f, -0.3f, 1.f, 0.f, 0.f},
        {0.6f, -0.3f, 0.f, 1.f, 0.f},
        {0.f, 0.6f, 0.f, 0.f, 1.f}
    };

    Canvas::Canvas() {
    }

    Canvas::~Canvas() {
    }

    bool Canvas::Initialize(GLFWwindow* window) {
        return true;
    }

    void Canvas::Shutdown() {
    }

    void Canvas::Draw() {
    }

    Canvas* Canvas::GetInstance() {
        if (!m_pInstance)
            m_pInstance = new Canvas();

        return m_pInstance;
    }

    void Canvas::SetVertexShaderText(const char* text) {
        vertex_shader_text = text;
    }

    const char*& Canvas::GetVertexShaderText() const {
        return vertex_shader_text;
    }

    void Canvas::SetFragmentShaderText(const char* text) {
        fragment_shader_text = text;
    }

    const char*& Canvas::GetFragmentShaderText() const {
        return fragment_shader_text;
    }

    const Vertex* Canvas::GetVertices() const {
        return vertices;
    }

    GLsizei Canvas::GetVerticesSize() const {
        return sizeof(vertices);
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

            error_callback(0, log.data());
        }
    }
}