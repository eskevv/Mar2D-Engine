#pragma once

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include <string>

#include "Texture.h"

class AssetStore
{
public:
   AssetStore() = default;

   void CreateTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string& filepath);
   void CreateMusic(const std::string& assetId, const std::string& filepath);
   void CreateSoundEffect(const std::string& assetId, const std::string& filepath);

   void Clear();
   
   Texture LoadFont(SDL_Renderer* renderer, TTF_Font* font, const std::string& textureText, SDL_Color textColor);
   
   Texture* GetTexture(const std::string& assedId);
   Mix_Music* GetMusic(const std::string& assedId);
   Mix_Chunk* GetChunk(const std::string& assedId);

private:
   std::map<std::string, Texture*> textures_;
   std::map<std::string, Mix_Music*> music_;
   std::map<std::string, Mix_Chunk*> audioChunks_;
};