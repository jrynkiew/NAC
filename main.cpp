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