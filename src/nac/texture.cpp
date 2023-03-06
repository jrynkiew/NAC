#include "texture.h"

namespace _NAC {
    // constructor
    Texture::Texture(int width, int height, int xPos, int yPos, const char* filePath, SDL_Renderer* renderer)
    {
        m_Width = width;
        m_Height = height;
        m_xPos = xPos;
        m_yPos = yPos;
        m_filePath = filePath;
        Load_Texture(renderer);
    }

    // destructor
    Texture::~Texture()
    {
    }

    // gets the width of the texture
    int Texture::Get_Width()
    {
        return m_Width;
    }

    // gets the height of the texture
    int Texture::Get_Height()
    {
        return m_Height;
    }

    // gets the Y position of the texture
    int Texture::Get_Y_Pos()
    {
        return m_yPos;
    }

    // gets the X position of the texture
    int Texture::Get_X_Pos()
    {
        return m_xPos;
    }

    // gets the texture file path
    const char* Texture::Get_File_Path()
    {
        return m_filePath;
    }

    // gets the texture
    SDL_Texture* Texture::Get_Texture()
    {
        return m_Texture;
    }

    // gets the surface
    SDL_Surface* Texture::Get_Surface()
    {
        return m_Surface;
    }

    // gets the rectangle
    const SDL_Rect* Texture::Get_Rect()
    {
        return &m_Rect;
    }

    // sets the texture
    void Texture::Set_Texture(SDL_Texture* texture)
    {
        m_Texture = texture;
    }

    // sets the surface
    void Texture::Set_Surface(SDL_Surface* surface)
    {
        m_Surface = surface;
    }

    // sets the rectangle
    void Texture::Set_Rect(SDL_Rect rect)
    {
        m_Rect = rect;
    }

    // loads the texture from a file
    bool Texture::Load_Texture(SDL_Renderer* renderer)
    {
        // load the image
        m_Surface = IMG_Load(m_filePath);
        if (m_Surface == NULL)
        {
            printf("IMG_Load: %s\n", IMG_GetError());
            return false;
        }

        // create the texture from the surface
        m_Texture = SDL_CreateTextureFromSurface(renderer, m_Surface);
        if (m_Texture == NULL)
        {
            printf("SDL_CreateTextureFromSurface: %s\n", SDL_GetError());
            return false;
        }

        // set the rectangle
        m_Rect.x = m_xPos;
        m_Rect.y = m_yPos;
        m_Rect.w = m_Width;
        m_Rect.h = m_Height;

        // free the surface
        SDL_FreeSurface(m_Surface);

        return true;
    }
        
}