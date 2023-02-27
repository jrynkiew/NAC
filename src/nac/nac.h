#include <renderer.h>
#include <window.h>

namespace _NAC {
    class NAC { 
        public:
            NAC();
            ~NAC();
            bool Initialize();
            void Shutdown();

            Renderer* GetRenderer();
            Window* GetWindow();

        private:
            static Renderer* m_pRenderer;
            static Window* m_pWindow;

            std::function<void()> NAC::loop;
            void NAC::main_loop();
    };
}