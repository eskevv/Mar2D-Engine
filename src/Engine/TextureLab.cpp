#include "TextureLab.h"

void TextureLab::CreateTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string filepath)
{
   Texture* texture = new Texture(renderer, filepath);
   textures_.emplace(assetId, texture);
}

Texture TextureLab::CreateTextureFont(SDL_Renderer* renderer, TTF_Font* font, const std::string& textureText, SDL_Color textColor)
{
   // Render text surface
   SDL_Surface* surface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
   SDL_Texture* texture;
   int width;
   int height;
   if (!surface) {
      printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
   } else {
      width = surface->w;
      height = surface->h;
      texture = SDL_CreateTextureFromSurface(renderer, surface);

      if (!texture) {
         printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
      }
   }
   return Texture(texture, width, height);
}

void TextureLab::Clear()
{
   for (auto texture : textures_) {
      SDL_DestroyTexture(texture.second->GetTexture());
   }
   textures_.clear();
}

Texture* TextureLab::GetTexture(const std::string& assetId)
{
   if (!textures_[assetId]) {
      printf("Error: That texture does not exist.");
      return nullptr;
   }
   return textures_[assetId];
}
