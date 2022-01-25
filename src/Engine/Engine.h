#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <sstream>
#include <vector>

#include "Input.h"
#include "Skeleton.h"
#include "TextureLab.h"
#include "Timer.h"
#include "Game.h"

class Engine
{
public:
   bool Initialize();
   void Run();
   void Quit();

private:
   static const int WINDOW_WIDTH{1920};
   static const int WINDOW_HEIGHT{1080};
   static const int FPS{120};
   static const int MS_PER_FRAME{1000 / FPS};
   static constexpr float GAME_SCALE{1.6f};

   SDL_Window* window_{nullptr};
   SDL_Renderer* renderer_{nullptr};

   bool isRunning_{false};
   int frameCount_{0};
   int frameTime_{0};

   Input input_;
   TextureLab textureLab_;
   Timer systemTimer_;
   Game game_;

   TTF_Font* fpsFont_{nullptr};
   std::stringstream fpsText_;
   Texture fpsTexture_;
   SDL_Color fpsColor_;

   void Setup();
   void Events();
   void Update();
   void Render();
};