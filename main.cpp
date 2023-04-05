#include <nac.h>

using namespace _NAC;

// Main code
int main(int, char**)
{
    // create NAC object
    NAC* nac = new NAC();

    // initialize NAC object
    if(!nac->Initialize())
    {
        printf("Error during NAC initialization!\n");
        nac->Shutdown();
        exit(EXIT_FAILURE);
    }

    // to get pointers to the window, render and imgui objects created during NAC initialization
    // auto window = nac->GetWindow();
    // auto renderer = nac->GetRenderer();
    // auto imgui = nac->GetInterface();

    nac->Run();

    return 0;
}
// GLFWwindow* w;

// void threadLoopIteration(void*)
// {
//         glClear(GL_COLOR_BUFFER_BIT);
//         glfwSwapBuffers(w);
// }

// void tw()
// {
//         glfwMakeContextCurrent(w);
//         emscripten_set_main_loop_arg(threadLoopIteration, nullptr, 0, 1);
// }

// void mainLoopIteration(void*) {}

// int main()
// {
//         std::cout << "TSS: " << emscripten_has_threading_support() << std::endl;

//         if (glewInit() != GLEW_OK) {
//                 std::cout << "No glew" << std::endl;
//                 return 1;
//         }
//         if (glfwInit() != GLFW_TRUE) {
//                 std::cout << "No glf" << std::endl;
//                 return 2;
//         }
//         w = glfwCreateWindow(100, 100, "Foo", 0, 0);

//         glfwMakeContextCurrent(w);
//         glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
//         glfwMakeContextCurrent(nullptr);

//         std::thread thread(tw);
//         emscripten_set_main_loop_arg(mainLoopIteration, nullptr, 0, 1);

//         return 0;
// }