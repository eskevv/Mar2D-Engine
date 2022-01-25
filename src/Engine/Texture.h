#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Texture
{
public:
   Texture() = default;
   Texture(SDL_Renderer*, const std::string& path);
   Texture(SDL_Texture* texture, int width, int height);

   int GetWidth();
   int GetHeight();
   SDL_Texture* GetTexture();

private:
   SDL_Texture* texture_{nullptr};
   
   int width_{0};
   int height_{0};
};

