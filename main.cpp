// #include <nac.h>

// using namespace _NAC;

// int main(void)
// {
//     // create NAC instance
//     NAC* nac = new NAC();

//     // initialize NAC. If it fails, shutdown and exit
//     if(!nac->Initialize())
//     {
//         printf("Error during NAC gui initialization!\n");
//         nac->Shutdown();
//         exit(EXIT_FAILURE);
//     }

//     // get pointers to the window and render object created during NAC initialization
//     auto window = nac->GetWindow()->GetGLFWwindow();
//     auto renderer = nac->GetRenderer();
    
//     if (!window)
//     {
//         printf("Error during NAC window creation!\n");
//         nac->Shutdown();
//         exit(EXIT_FAILURE);
//     }

//     nac->Run();

//     loop = [&] {
//         renderer->DrawGUI();

//         glfwPollEvents();

//         renderer->Render(window);
//     };

// #ifdef __EMSCRIPTEN__
//     emscripten_set_main_loop(main_loop, 0, true);
// #else
//     while (!glfwWindowShouldClose(window))
//         main_loop();
// #endif

//     ImGui_ImplOpenGL3_Shutdown();
//     ImGui_ImplGlfw_Shutdown();
//     ImGui::DestroyContext();

//     glfwDestroyWindow(window);
//     glfwTerminate();
//     exit(EXIT_SUCCESS);
// }

// Dear ImGui: standalone example application for SDL2 + SDL_Renderer
// (SDL is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

// Important to understand: SDL_Renderer is an _optional_ component of SDL. We do not recommend you use SDL_Renderer
// because it provides a rather limited API to the end-user. We provide this backend for the sake of completeness.
// For a multi-platform app consider using e.g. SDL+DirectX on Windows and SDL+OpenGL on Linux/OSX.
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