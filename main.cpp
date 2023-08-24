// emcc main.cpp -o index.html -s USE_WEBGL2=1 -s USE_GLFW=3 -s WASM=1 -std=c++1z

//https://gist.github.com/ousttrue/0f3a11d5d28e365b129fe08f18f4e141

// base:  https://www.glfw.org/docs/latest/quick.html#quick_example
// ref: https://gist.github.com/SuperV1234/5c5ad838fe5fe1bf54f9


#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#else
#include "glad/glad.h"
#endif
#include <nac.h>
#include <thread>

using namespace _NAC;

static const char *vertex_shader_text =
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
static const char *fragment_shader_text =
	"precision mediump float;\n"
    "varying vec3 color;\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = vec4(color, 1.0);\n"
    "}\n";
#else
static const char *fragment_shader_text =
    "varying vec3 color;\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = vec4(color, 1.0);\n"
    "}\n";
#endif

NAC* nac;

std::function<void()> loop;
void main_loop() { 
    #ifdef __EMSCRIPTEN__
        emscripten_log(EM_LOG_CONSOLE, "main_loop");
    #else
        printf("main_loop\n");
    #endif
    loop();
 }

void threadLoopIteration(void*)
{
    #ifdef __EMSCRIPTEN__
        emscripten_log(EM_LOG_CONSOLE, "threadLoopIteration");
    #else
        printf("threadLoopIteration\n");
    #endif
        // loop();
}

void tw()
{
    #ifdef __EMSCRIPTEN__
        emscripten_set_main_loop_arg(threadLoopIteration, nullptr, 0, 1);
    #else
        while(true)
        {
            threadLoopIteration(nullptr);
        }
    #endif
}

void check_error(GLuint shader)
{
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

int main(void)
{
    GLint mvp_location, vpos_location, vcol_location;

    //create NAC instance
    nac = new NAC();

    //initialize NAC
    if(!nac->Initialize())
    {
        printf("Error during NAC gui initialization!\n");
        nac->Shutdown();
        exit(EXIT_FAILURE);
    }

    if (!nac->GetWindow()->GetGLFWwindow())
    {
        printf("Error during NAC window creation!\n");
        nac->Shutdown();
        exit(EXIT_FAILURE);
    }    

    glEnable(GL_CULL_FACE);

    printf("Use Modern OpenGL (with shaders)\n");
    // NOTE: OpenGL error checks have been omitted for brevity
    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, nac->GetRenderer()->GetCanvas()->GetVerticesSize(), nac->GetRenderer()->GetCanvas()->GetVertices(), GL_STATIC_DRAW);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    auto vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &(nac->GetRenderer()->GetCanvas()->GetVertexShaderText()), NULL);
    glCompileShader(vertex_shader);
    check_error(vertex_shader);

    auto fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &(nac->GetRenderer()->GetCanvas()->GetFragmentShaderText()), NULL);
    glCompileShader(fragment_shader);
    check_error(fragment_shader);

    auto program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");
    glEnableVertexAttribArray(vpos_location);
    //you need to pass the appropriate arguments to this function. Specifically, you need to provide the attribute location (vpos_location), the number of components (2 for x and y), the data type (GL_FLOAT), whether the data should be normalized (GL_FALSE in this case), the stride (sizeof(vertices[0])), and the pointer to the data (0 for the initial position in the array). struct Vertex is defined in another class. Here's how you can do it:
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(sizeof(float) * 2));

    loop = [&] {
        float ratio;
        int width, height;
        mat4x4 m, p, mvp;
        glfwGetFramebufferSize(nac->GetWindow()->GetGLFWwindow(), &width, &height);
        ratio = width / (float)height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        mat4x4_identity(m);
        mat4x4_rotate_Z(m, m, (float)glfwGetTime());
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_mul(mvp, p, m);
        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat *)mvp);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        nac->GetRenderer()->BeginScene();

        glfwPollEvents();

        nac->GetRenderer()->Render(nac->GetWindow()->GetGLFWwindow());

    };

#ifdef __EMSCRIPTEN__
    std::thread thread(tw);
    emscripten_set_main_loop(main_loop, 0, true);
#else
    while (!glfwWindowShouldClose(nac->GetWindow()->GetGLFWwindow()))
        main_loop();
#endif

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(nac->GetWindow()->GetGLFWwindow());
    glfwTerminate();
    exit(EXIT_SUCCESS);
}


#ifdef __EMSCRIPTEN__
extern "C" {
    EMSCRIPTEN_KEEPALIVE
    void updateCanvasSize(int width, int height) {
        // canvasWidth = width;
        // canvasHeight = height;
        glfwSetWindowSize(nac->GetWindow()->GetGLFWwindow(), width, height);
    }
}
#endif