// emcc main.cpp -o index.html -s USE_WEBGL2=1 -s USE_GLFW=3 -s WASM=1 -std=c++1z

//https://gist.github.com/ousttrue/0f3a11d5d28e365b129fe08f18f4e141

// base:  https://www.glfw.org/docs/latest/quick.html#quick_example
// ref: https://gist.github.com/SuperV1234/5c5ad838fe5fe1bf54f9



#include <renderer.h>

static const struct
{
    float x, y;
    float r, g, b;
} vertices[3] =
    {
        {-0.6f, -0.4f, 1.f, 0.f, 0.f},
        {0.6f, -0.4f, 0.f, 1.f, 0.f},
        {0.f, 0.6f, 0.f, 0.f, 0.5f}};

mat4x4 m, p, mvp;
float ratio;
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (key == GLFW_KEY_LEFT  && action == GLFW_REPEAT)
    {
        fprintf(stdout, "Left key pressed", NULL);
        mat4x4_identity(m);
        mat4x4_rotate_Z(m, m, (float)glfwGetTime());
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_mul(mvp, p, m);
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT)
    {
        fprintf(stdout, "Left key pressed", NULL);
        mat4x4_identity(m);
        mat4x4_rotate_Z(m, m, -(float)glfwGetTime());
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_mul(mvp, p, m);
    }
}

std::function<void()> loop;
void main_loop() { loop(); }

int main(void)
{
    glfwSetErrorCallback(g_sRenderer->error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    auto window = glfwCreateWindow(1280, 720, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
#ifdef __EMSCRIPTEN__
#else
    gladLoadGL();
#endif
    glfwSwapInterval(1);
    printf("%s\n", glGetString(GL_VERSION));

    //imgui
    g_sRenderer->Initialize(window);


    // NOTE: OpenGL error checks have been omitted for brevity
    GLint mvp_location, vpos_location, vcol_location;
    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    const char* vst = g_sRenderer->GetVertexShaderText();
    const char* fst = g_sRenderer->GetFragmentShaderText();
    auto vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vst, NULL);
    glCompileShader(vertex_shader);
    g_sRenderer->check_error(vertex_shader);

    auto fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fst, NULL);
    glCompileShader(fragment_shader);
    g_sRenderer->check_error(fragment_shader);

    auto program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
                          sizeof(vertices[0]), (void *)0);
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                          sizeof(vertices[0]), (void *)(sizeof(float) * 2));

    loop = [&] {
        
        int width, height;
        
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat *)mvp);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        g_sRenderer->BeginScene();

        glfwPollEvents();

        g_sRenderer->Render(window);

    };

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(main_loop, 0, true);
#else
    while (!glfwWindowShouldClose(window))
        main_loop();
#endif

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}