#include <renderer.h>
#include <window.h>

namespace _NAC {
    class NAC { 
        public:
            NAC();
            ~NAC();
            bool Initialize();
            void Run();
            void Shutdown();

            Renderer* GetRenderer();
            Window* GetWindow();

        private:
            static Renderer* m_Renderer;
            static Window* m_Window;
            int m_Width, m_Height;
    };
}