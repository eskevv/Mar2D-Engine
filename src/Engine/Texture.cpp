#include <iostream>

#include "Texture.h"

// * CONSTRUCTORS *

Texture::Texture(int width, int height, SDL_Texture* texture) : width_(width), height_(height), texture_(texture) {}

Texture::Texture(SDL_Renderer* renderer, const std::string& path)
{
   SDL_Surface* surface = IMG_Load(path.c_str());
   if (!surface) {
      printf("Unable to load image %s! IMG Error: %s\n", path.c_str(), IMG_GetError());
   } else {
      width_ = surface->w;
      height_ = surface->h;
      texture_ = SDL_CreateTextureFromSurface(renderer, surface);
      if (!texture_) {
         printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
      }
   }
   SDL_FreeSurface(surface);
}

// * ACESSORS *

int Texture::GetWidth() const
{
   return width_;
}

int Texture::GetHeight() const
{
   return height_;
}

SDL_Texture* Texture::GetTexture() const
{
   return texture_;
}