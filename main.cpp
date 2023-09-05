// emcc main.cpp -o index.html -s USE_WEBGL2=1 -s USE_GLFW=3 -s WASM=1 -std=c++1z

//https://gist.github.com/ousttrue/0f3a11d5d28e365b129fe08f18f4e141

// base:  https://www.glfw.org/docs/latest/quick.html#quick_example
// ref: https://gist.github.com/SuperV1234/5c5ad838fe5fe1bf54f9

#include <nac.h>
#include <thread>
#include <iostream>
#include <string.h>
#include <math.h>
#include <unistd.h>

using namespace _NAC;
using namespace std;

NAC* nac;
Renderer* renderer;
Window* window;

std::function<void()> loop;
void main_loop() { 
    #ifdef __EMSCRIPTEN__
        // emscripten_log(EM_LOG_CONSOLE, "main_loop");
    #else
        // printf("main_loop\n");
    #endif
    loop();
 }

 void thread_loop() { 
    #ifdef __EMSCRIPTEN__
        // emscripten_log(EM_LOG_CONSOLE, "thread_loop");
    #else
        // printf("thread_loop\n");
    #endif
 }

void threadLoopIteration(void*)
{
    #ifdef __EMSCRIPTEN__
        //emscripten_log(EM_LOG_CONSOLE, "threadLoopIteration");
    #else
        //printf("threadLoopIteration\n");
    #endif
    thread_loop();
}

void tw()
{
    #ifdef __EMSCRIPTEN__
        emscripten_set_main_loop_arg(threadLoopIteration, nullptr, 0, 1);
    #else
        threadLoopIteration(nullptr);
    #endif
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

    //get renderer and window pointers
    renderer = nac->GetRenderer();
    window = nac->GetWindow();

    //render loop
    loop = [&] {

        nac->Run();
    };

    //run NAC
#ifdef __EMSCRIPTEN__
    std::thread thread(tw);
    emscripten_set_main_loop(main_loop, 0, true);
#else
    std::thread nativeThread(tw);
    while (!glfwWindowShouldClose(nac->GetWindow()->GetGLFWwindow()))
        main_loop();
#endif

    #ifndef __EMSCRIPTEN__
        nativeThread.join();
    #endif
    renderer->Shutdown();
    window->Shutdown();
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