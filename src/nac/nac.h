#include <interface.h>
#include <texture.h>
#include <functional>

namespace _NAC {
    class NAC { 
        public:
            NAC();
            ~NAC();

            SDL_Renderer* GetRenderer();
            SDL_Window* GetWindow();
            ImGuiIO* GetInterface();
            NAC* GetInstance();

            bool Initialize();
            void Run();
            void Shutdown();

            void GetEvents();
            void Run();
            static void Draw();
            
        private:
            static Renderer* m_Renderer;
            static Window* m_Window;
    };
    
    static std::function<void()> loop;
    // static NAC* g_pNAC = nullptr;
}
