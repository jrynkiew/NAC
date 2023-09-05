#include "canvas.h"

namespace _NAC
{
    Canvas* Canvas::m_pInstance = nullptr;
    
    const char* Canvas::vertex_shader_text =
        "attribute vec3 vPos;\n"
        "attribute vec3 vCol;\n"

        "uniform mat4 MVP;\n"

        "varying vec3 Color;\n"

        "void main()\n"
        "{\n"
        "    gl_Position = MVP * vec4(vPos, 1.0);\n"
        "    Color = vCol;\n"
        "}\n";
    #ifdef __EMSCRIPTEN__
    const char* Canvas::fragment_shader_text =
        "precision mediump float;\n"
        "in vec4 Color;\n"

        "void main()\n"
        "{\n"
        "    gl_FragColor = Color;\n"
        "}\n";
    #else
    const char* Canvas::fragment_shader_text =
        "in vec4 Color;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = Color;\n"
        "}\n";
    #endif


    const Vertex Canvas::vertices[3] = {
        {-0.6f, -0.3f, 1.f, 0.f, 0.f},
        {0.6f, -0.3f, 0.f, 1.f, 0.f},
        {0.f, 0.6f, 0.f, 0.f, 1.f}
    };

    Canvas::Canvas() {
        m_pInstance = this;
    }

    Canvas::~Canvas() {
    }

    bool Canvas::Initialize(GLFWwindow* window) {
        m_pWindow = window;
        prepare_vertex_buffer();
        prepare_vertex_shader();
        prepare_fragment_shader();
        prepare_program();
        return true;
    }

    void Canvas::Shutdown() {
    }

    void Canvas::Draw() {
        run_program();
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

    void Canvas::run_program() {
        glfwGetFramebufferSize(m_pWindow, &width, &height);
        ratio = width / (float)height;
        glViewport(0, 0, width, height);
        mat4x4_identity(m);
        mat4x4_rotate_Z(m, m, (float)glfwGetTime());
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_mul(mvp, p, m);
        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat *)mvp);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void Canvas::prepare_vertex_buffer() {
        glGenBuffers(1, &vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, Canvas::GetInstance()->GetVerticesSize(), Canvas::GetInstance()->GetVertices(), GL_STATIC_DRAW);    
    }

    void Canvas::prepare_vertex_shader() {
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &(Canvas::GetInstance()->GetVertexShaderText()), NULL);
        glCompileShader(vertex_shader);
        check_shader_error(vertex_shader);
    }

    void Canvas::prepare_fragment_shader() {
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &(Canvas::GetInstance()->GetFragmentShaderText()), NULL);
        glCompileShader(fragment_shader);
        check_shader_error(fragment_shader);
    }

    void Canvas::prepare_program() {
        program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);
        check_program_error(program);

        mvp_location = glGetUniformLocation(program, "MVP");
        vpos_location = glGetAttribLocation(program, "vPos");
        vcol_location = glGetAttribLocation(program, "vCol");

        glEnableVertexAttribArray(vpos_location);
        glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
                            sizeof(Vertex), (void*) 0);
        glEnableVertexAttribArray(vcol_location);
        glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                            sizeof(Vertex), (void*) (sizeof(float) * 2));
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
