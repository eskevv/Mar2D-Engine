#include "AssetStore.h"

void AssetStore::CreateTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string& filepath)
{
   Texture* texture = new Texture(renderer, filepath);
   if (texture) {
      textures_.emplace(assetId, texture);
   }
}

void AssetStore::CreateMusic(const std::string& assetId, const std::string& filepath)
{
   Mix_Music* music = Mix_LoadMUS(filepath.c_str());
   if (!music) {
      printf("Unable to load music %s in the AssetStore. Error: %s\n", filepath.c_str(), Mix_GetError());
   } else {
      music_.emplace(assetId, music);
   }
}

void AssetStore::CreateSoundEffect(const std::string& assetId, const std::string& filepath)
{
   Mix_Chunk* chunk = Mix_LoadWAV(filepath.c_str());
   if (!chunk) {
      printf("Unable to load audio chunk %s in the AssetStore. Error: %s\n", filepath.c_str(), Mix_GetError());
   } else {
      audioChunks_.emplace(assetId, chunk);
   }
}

Texture AssetStore::LoadFont(SDL_Renderer* renderer, TTF_Font* font, const std::string& textureText, SDL_Color textColor)
{
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
   return Texture(width, height, texture);
}

void AssetStore::Clear()
{
   for (auto texture : textures_) {
      SDL_DestroyTexture(texture.second->GetTexture());
   }
   for (auto music : music_) {
      Mix_FreeMusic(music.second);
   }
   for (auto chunk : audioChunks_) {
      Mix_FreeChunk(chunk.second);
   }
   textures_.clear();
   music_.clear();
   audioChunks_.clear();
}

Texture* AssetStore::GetTexture(const std::string& assetId)
{
   if (!textures_[assetId]) {
      printf("Error: That texture does not exist.");
      return nullptr;
   }
   return textures_[assetId];
}

Mix_Music* AssetStore::GetMusic(const std::string& assedId)
{
   if (!music_[assedId]) {
      printf("Error: That music file does not exist.");
      return nullptr;
   }
   return music_[assedId];
}

Mix_Chunk* AssetStore::GetChunk(const std::string& assedId)
{
   if (!audioChunks_[assedId]) {
      printf("Error: That audio chunk does not exist.");
      return nullptr;
   }
   return audioChunks_[assedId];
}
