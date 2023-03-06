#pragma once
#define NAC_CANVAS_H

#include <renderer.h>
#include <window.h>

namespace _NAC {
    //definition of class that creates a canvas
    class Canvas
    {
        public:
            // constructor
            Canvas(SDL_Window* window, SDL_Renderer* renderer);
            // destructor
            ~Canvas();
            // initialize the canvas
            bool Initialize();
            // draw the canvas
            void Draw_Canvas();
            // shutdown the canvas
            void Shutdown();
        private:
            // renderer
            SDL_Renderer* m_Renderer;
            // window
            SDL_Window* m_Window;
            // viewport
            SDL_Renderer* m_Viewport;
            // render target
            SDL_Texture* m_RenderTarget;
    };
}
