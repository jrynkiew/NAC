// emcc main.cpp -o index.html -s USE_WEBGL2=1 -s USE_GLFW=3 -s WASM=1 -std=c++1z

//https://gist.github.com/ousttrue/0f3a11d5d28e365b129fe08f18f4e141

// base:  https://www.glfw.org/docs/latest/quick.html#quick_example
// ref: https://gist.github.com/SuperV1234/5c5ad838fe5fe1bf54f9

#include <nac.h>
#include <thread>

using namespace _NAC;

NAC* nac;
Renderer* renderer;

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
    //create NAC instance
    nac = new NAC();

    //initialize NAC
    if(!nac->Initialize())
    {
        printf("Error during NAC renderer initialization!\n");
        nac->Shutdown();
        exit(EXIT_FAILURE);
    }

    renderer = nac->GetRenderer();
    printf("Use Modern OpenGL (with shaders)\n");

    //render loop
    loop = [&] {
        renderer->GetCanvas()->run_program();
        
        renderer->GetInterface()->Draw();

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