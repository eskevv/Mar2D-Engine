#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "AssetStore.h"
#include "Camera.h"
#include "FPS_System.h"
#include "Graphics.h"
#include "Input.h"
#include "Timer.h"

class Engine
{
public:
   Engine();

   bool Initialize();
   void Run();
   void Quit();

   static const int WINDOW_WIDTH{1920};
   static const int WINDOW_HEIGHT{1080};
   static const int FPS{120};
   static const int MS_PER_FRAME{1000 / FPS};

protected:
   void Setup();
   void Events();
   void Update();
   void Render();

   bool isRunning_;

   SDL_Window* window_{nullptr};
   SDL_Renderer* renderer_{nullptr};

   Graphics graphics_;
   Input input_;
   AssetStore assetStore_;
   Timer systemTimer_;
   FPS_System fps_;

   // DEMO //
   Texture dirt_;
   Texture grass_;
   Texture plant_;
   std::map<int, Texture> tiles_;

   std::map<Vec2, int> GenerateChunks(int x, int y);
   void InitGame();
   void GameInput();
   void UpdateGame();
   void RenderGame();
};