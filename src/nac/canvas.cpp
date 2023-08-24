#include "canvas.h"

namespace _NAC
{
    Canvas* Canvas::m_pInstance = nullptr;
    const char* Canvas::vertex_shader =
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
    const char* Canvas::fragment_shader =
        "precision mediump float;\n"
        "varying vec3 color;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = vec4(color, 1.0);\n"
        "}\n";
    #else
    const char* Canvas::fragment_shader =
        "varying vec3 color;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = vec4(color, 1.0);\n"
        "}\n";
    #endif

    const Vertex Canvas::vertices[3] = {
        {-0.6f, -0.6f, 1.f, 0.f, 0.f},
        {0.6f, -0.6f, 0.f, 1.f, 0.f},
        {0.f, 0.6f, 0.f, 0.f, 1.f}
    };

    Canvas::Canvas() {
    }

    Canvas::~Canvas() {
    }

    bool Canvas::Initialize(GLFWwindow* window) {
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

    const char* Canvas::GetVertexShader() {
        return vertex_shader;
    }

    const char* Canvas::GetFragmentShader() {
        return fragment_shader;
    }
}