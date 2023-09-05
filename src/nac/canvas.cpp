#include "canvas.h"

namespace _NAC
{
    Canvas* Canvas::m_pInstance = nullptr;

    const char* Canvas::vertex_shader_text =
        "attribute vec3 Position;\n"
        "attribute vec3 inColor;\n"

        "uniform mat4 gWorld;\n"

        "varying vec4 Color;\n"

        "void main()\n"
        "{\n"
        "    gl_Position = gWorld * vec4(Position, 1.0);\n"
        "    Color = vec4(inColor, 1.0f);\n"
        "}\n";
    #ifdef __EMSCRIPTEN__
    const char* Canvas::fragment_shader_text =
        "precision mediump float;\n"
        "varying vec4 Color;\n"

        "void main()\n"
        "{\n"
        "    gl_FragColor = Color;\n"
        "}\n"
    #else
    const char* Canvas::fragment_shader_text =
        "varying vec4 Color;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = Color;\n"
        "}\n";
    #endif

    Canvas::Canvas() {
        m_pInstance = this;
    }

    Canvas::~Canvas() {
    }

    bool Canvas::Initialize(GLFWwindow* window) {
        m_pWindow = window;
        scale = 0.0f;

        World[0][0] = cosf(scale); World[0][1] = -sinf(scale); World[0][2] = 0.0f; World[0][3] = 0.0f;
        World[1][0] = sinf(scale); World[1][1] = cosf(scale) ; World[1][2] = 0.0f; World[1][3] = 0.0f;
        World[2][0] = 0.0;         World[2][1] = 0.0f;         World[2][2] = 1.0f; World[2][3] = 0.0f;
        World[3][0] = 0.0f;        World[3][1] = 0.0f;         World[3][2] = 0.0f; World[3][3] = 1.0f;

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
        glUniformMatrix4fv(gWorldLocation, 1, GL_FALSE, &World[0][0]);
        glDrawElements(GL_TRIANGLES, 54, GL_UNSIGNED_INT, 0);
    }

    void Canvas::prepare_vertex_buffer() {
        // Center
        Vertices[0] = Vertex(0.0f, 0.0);

        // Top row
        Vertices[1] = Vertex(-1.0f,  1.0f);
        Vertices[2] = Vertex(-0.75f, 1.0f);
        Vertices[3] = Vertex(-0.50f, 1.0f);
        Vertices[4] = Vertex(-0.25f, 1.0f);
        Vertices[5] = Vertex(-0.0f,  1.0f);
        Vertices[6] = Vertex(0.25f,  1.0f);
        Vertices[7] = Vertex(0.50f,  1.0f);
        Vertices[8] = Vertex(0.75f,  1.0f);
        Vertices[9] = Vertex(1.0f,   1.0f);

        // Bottom row
        Vertices[10] = Vertex(-1.0f,  -1.0f);
        Vertices[11] = Vertex(-0.75f, -1.0f);
        Vertices[12] = Vertex(-0.50f, -1.0f);
        Vertices[13] = Vertex(-0.25f, -1.0f);
        Vertices[14] = Vertex(-0.0f,  -1.0f);
        Vertices[15] = Vertex(0.25f,  -1.0f);
        Vertices[16] = Vertex(0.50f,  -1.0f);
        Vertices[17] = Vertex(0.75f,  -1.0f);
        Vertices[18] = Vertex(1.0f,   -1.0f);

        glGenBuffers(1, &vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);    
    }

    void Canvas::prepare_index_buffer() {
         unsigned int Indices[] = { // Top triangles
            0, 2, 1,
            0, 3, 2,
            0, 4, 3,
            0, 5, 4,
            0, 6, 5,
            0, 7, 6,
            0, 8, 7,
            0, 9, 8,

            // Bottom triangles
            0, 10, 11,
            0, 11, 12,
            0, 12, 13,
            0, 13, 14,
            0, 14, 15,
            0, 15, 16,
            0, 16, 17,
            0, 17, 18,

            // Left triangle
            0, 1, 10,

            // Right triangle
            0, 18, 9 
        };

        glGenBuffers(1, &index_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
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

        gWorldLocation = glGetUniformLocation(program, "gWorld");

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                            6 * sizeof(float), (void*) 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                            6 * sizeof(float), (void*)(3 * sizeof(float)));
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