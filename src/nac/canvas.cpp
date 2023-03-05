namespace _NAC {
    // constructor
    Canvas::Canvas(SDL_Window* window, SDL_Renderer* renderer) 
    {
        m_Renderer = renderer;
        m_Window = window;
    }

    Canvas::~Canvas() 
    {
        Shutdown();
    }

    bool Canvas::Initialize()
    {
        // create a viewport
        m_Viewport = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_TARGETTEXTURE);
        if(m_Viewport == NULL)
        {
            printf("Error creating viewport: %s\n", SDL_GetError());
            return false;
        }

        // create a render target
        m_RenderTarget = SDL_CreateTexture(m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 800, 600);
        if(m_RenderTarget == NULL)
        {
            printf("Error creating render target: %s\n", SDL_GetError());
            return false;
        }

        return true;
    }

    void Canvas::Draw_Canvas()
    {
        // set the viewport
        SDL_RenderSetViewport(m_Renderer, NULL);
        // set the render target
        SDL_SetRenderTarget(m_Renderer, m_RenderTarget);
        // set the viewport
        SDL_RenderSetViewport(m_Viewport, NULL);
        // set the render target
        SDL_SetRenderTarget(m_Viewport, m_RenderTarget);
        // clear the render target
        SDL_SetRenderDrawColor(m_Viewport, 0, 0, 0, 255);
        SDL_RenderClear(m_Viewport);

        // draw the canvas
        SDL_Rect rect;
        rect.x = 0;
        rect.y = 0;
        rect.w = 800;
        rect.h = 600;
        SDL_SetRenderDrawColor(m_Viewport, 255, 255, 255, 255);
        SDL_RenderFillRect(m_Viewport, &rect);

        // set the viewport
        SDL_RenderSetViewport(m_Renderer, NULL);
        // set the render target
        SDL_SetRenderTarget(m_Renderer, NULL);

        // render the render target to the viewport
        SDL_RenderCopy(m_Renderer, m_RenderTarget, NULL, NULL);
    }

    void Canvas::Shutdown()
    {
        SDL_DestroyTexture(m_RenderTarget);
        SDL_DestroyRenderer(m_Viewport);
    }
}