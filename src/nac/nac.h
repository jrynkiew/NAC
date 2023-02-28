#include <interface.h>
#include <functional>

namespace _NAC {
    class NAC { 
        public:
            NAC();
            ~NAC();
            bool Initialize();
            void Shutdown();

            SDL_Renderer* GetRenderer();
            SDL_Window* GetWindow();
            ImGuiIO* GetInterface();

        private:
            static Renderer* m_pRenderer;
            static Window* m_pWindow;
            static Interface* m_pInterface;

            std::function<void()> loop;
            void main_loop();
    };
}