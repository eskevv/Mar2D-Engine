#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>

#include "AssetStore.h"
#include "Texture.h"
#include "Timer.h"

class FPS_System
{
public:
   FPS_System() : frameCount_(0), frameTime_(0), avgFPS_(0), fpsColor_{185, 50, 0, 255}, fpsFont_(nullptr) {}

   void Init(AssetStore& assetStore, SDL_Renderer* renderer) { fpsFont_ = TTF_OpenFont("assets/fonts/squarea.ttf", 14); }

   void Update(Timer& system, AssetStore& assetStore, SDL_Renderer* renderer)
   {
      frameCount_++;
      frameTime_ = system.GetTicks();
      avgFPS_ = frameCount_ / (frameTime_ / 1000.0f);
      fpsText_.str("");
      fpsText_ << "FPS " << avgFPS_;
      fpsTexture_ = assetStore.LoadFont(renderer, fpsFont_, fpsText_.str().c_str(), fpsColor_);
      destRec = {5, 5, fpsTexture_.GetWidth(), fpsTexture_.GetHeight()};
   }

   void Render(SDL_Renderer* renderer) { SDL_RenderCopy(renderer, fpsTexture_.GetTexture(), nullptr, &destRec); }

   int GetFrameTime() const { return frameTime_; }

private:
   int frameCount_;
   int frameTime_;
   int avgFPS_;

   SDL_Color fpsColor_;
   TTF_Font* fpsFont_;

   SDL_Rect destRec;
   std::stringstream fpsText_;
   Texture fpsTexture_;
};