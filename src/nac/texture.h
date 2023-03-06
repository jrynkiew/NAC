#pragma once
#define NAC_RENDERER_TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>

namespace _NAC {
    // definition of class that creates a texture and loads it from a file
    class Texture
    {
    public:
        // constructor
        Texture(int width, int height, int xPos, int yPos, const char* filePath, SDL_Renderer* renderer);
        // destructor
        ~Texture();
        // gets the width of the texture
        int Get_Width();
        // gets the height of the texture
        int Get_Height();
        // gets the position of the texture
        int Get_Y_Pos();
        // gets the position of the texture
        int Get_X_Pos();
        // gets the texture file path
        const char* Get_File_Path();
        // gets the texture
        SDL_Texture* Get_Texture();
        // sets the texture
        void Set_Texture(SDL_Texture* texture);
        // gets the surface
        SDL_Surface* Get_Surface();
        // sets the surface
        void Set_Surface(SDL_Surface* surface);
        // gets the rectangle
        const SDL_Rect* Get_Rect();
        // sets the rectangle
        void Set_Rect(SDL_Rect rect);
        // loads the texture from a file
        bool Load_Texture(SDL_Renderer* renderer);

    private:
        // the width of the texture
        int m_Width;
        // the height of the texture
        int m_Height;
        // the Y position of the texture
        int m_yPos;
        // the X position of the texture
        int m_xPos;
        // the texture file path
        const char* m_filePath;
        // the texture
        SDL_Texture* m_Texture;
        // the surface
        SDL_Surface* m_Surface;
        // the rectangle
        SDL_Rect m_Rect;
    };
}