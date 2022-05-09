#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Texture
{
public:
   Texture() = default;
   Texture(SDL_Renderer*, const std::string& path);
   Texture(int width, int height, SDL_Texture* texture);

   int GetWidth() const;
   int GetHeight() const;
   SDL_Texture* GetTexture() const;

private:
   int width_;
   int height_;
   SDL_Texture* texture_;
};
