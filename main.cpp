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
        float A = 0, B = 0;
        float i, j;
        int k;
        float z[1760];
        char b[1760];
        printf("\x1b[2J");
        for(;;) {
            memset(b,32,1760);
            memset(z,0,7040);
            for(j=0; j < 6.28; j += 0.07) {
                for(i=0; i < 6.28; i += 0.02) {
                    float c = sin(i);
                    float d = cos(j);
                    float e = sin(A);
                    float f = sin(j);
                    float g = cos(A);
                    float h = d + 2;
                    float D = 1 / (c * h * e + f * g + 5);
                    float l = cos(i);
                    float m = cos(B);
                    float n = sin(B);
                    float t = c * h * g - f * e;
                    int x = 40 + 30 * D * (l * h * m - t * n);
                    int y= 12 + 15 * D * (l * h * n + t * m);
                    int o = x + 80 * y;
                    int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
                    if(22 > y && y > 0 && x > 0 && 80 > x && D > z[o]) {
                        z[o] = D;
                        b[o] = "...,,,ooo000"[N > 0 ? N : 0]; //works much better with ".,-~:;=!*#$@" or "JackEatDonut"
                    }
                }
            }
            printf("\x1b[H");
            for(k = 0; k < 1761; k++) {
                putchar(k % 80 ? b[k] : 10);
                A += 0.00004;
                B += 0.00002;
            }
            usleep(1000);
        }
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

    Vertex* vertices = new Vertex[3];
    vertices[0] = {-1.f, -1.f, 1.f, 0.f, 0.f};
    vertices[1] = {1.f, -1.f, 0.f, 1.f, 0.f};
    vertices[2] = {0.f, 1.f, 0.f, 0.f, 1.f};

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
    int i=0;
    //render loop
    loop = [&] {
        i++;
        renderer->Render(nac->GetWindow()->GetGLFWwindow());
        if(i>10000) {
            renderer->GetCanvas()->SetVertices(vertices);
            renderer->GetCanvas()->Initialize(nac->GetWindow()->GetGLFWwindow());
            printf("reinitialized\n");
        }
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