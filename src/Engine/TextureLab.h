#pragma once

#include <map>
#include <string>
#include "Texture.h"
#include <SDL2/SDL_ttf.h>

class TextureLab
{
public:
   TextureLab() = default;

   void CreateTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string filepath);
   Texture CreateTextureFont(SDL_Renderer* renderer, TTF_Font* font, const std::string& textureText, SDL_Color textColor);
   void Clear();
   Texture* GetTexture(const std::string& assedId);

private:
   std::map<std::string, Texture*> textures_;
};