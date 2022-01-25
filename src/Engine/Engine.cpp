#include <windows.h>
#include <iostream>

#include "Engine.h"

bool Engine::Initialize()
{
   SetCurrentDirectory("../");

   if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      std::cout << "Failed to initialize SDL. Error: " << SDL_GetError() << std::endl;
      return false;
   }

   int img_flags{IMG_INIT_JPG | IMG_INIT_PNG};
   if (!(IMG_Init(img_flags) & img_flags)) {
      std::cout << "Failed to initialize SDL_IMG. Error: " << IMG_GetError() << std::endl;
      return false;
   }

   if (TTF_Init() != 0) {
      printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
      return false;
   }

   window_ = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);
   if (!window_) {
      std::cout << "Failed to create the window. Error: " << SDL_GetError() << std::endl;
      return false;
   }

   renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
   if (!renderer_) {
      std::cout << "Failed to create the renderer. Error: " << SDL_GetError() << std::endl;
      return false;
   }

   return isRunning_ = true;
}

void Engine::Run()
{
   if (isRunning_) {
      Setup();
      while (isRunning_) {
         Events();
         Update();
         Render();
      }
   }
}

void Engine::Quit()
{
   game_.Destroy();
   textureLab_.Clear();
   SDL_DestroyRenderer(renderer_);
   SDL_DestroyWindow(window_);
   renderer_ = nullptr;
   window_ = nullptr;
   IMG_Quit();
   SDL_Quit();
}

void Engine::Setup()
{
   fpsFont_ = TTF_OpenFont("assets/fonts/frostbite.ttf", 16);
   fpsColor_ = {255, 110, 0, 255};

   game_.Setup(textureLab_, renderer_);

   systemTimer_.Start();
}

void Engine::Events()
{
   SDL_Event event;
   input_.NewFrame();
   while (SDL_PollEvent(&event)) {
      switch (event.type) {
         case SDL_KEYDOWN:
            if (!event.key.repeat) {
               input_.KeyDownEvent(event.key.keysym.scancode);
            }
            break;
         case SDL_KEYUP:
            input_.KeyUpEvent(event.key.keysym.scancode);
            break;
         case SDL_QUIT:
            isRunning_ = false;
            break;
      }
   }

   if (input_.IsPressed(SDL_SCANCODE_ESCAPE)) {
      isRunning_ = false;
   }
   game_.HandleInput(input_);
}

// TODO:
// - load maps
// - animations
// - create particles
// - attack collisions with every entity
// - player controller
// - slow motion camera

void Engine::Update()
{
   int time = systemTimer_.GetTicks();
   // calculate fps
   frameCount_++;
   int avg_fps = frameCount_ / (time / 1000.f);
   // cap frame rate
   int wait_time = MS_PER_FRAME - (time - frameTime_);
   if (wait_time > 0 && wait_time <= MS_PER_FRAME) {
      SDL_Delay(wait_time);
   }
   // calculate delta time
   double delta_time = (time - frameTime_) / 1000.0;
   frameTime_ = systemTimer_.GetTicks();
   // create fps texture
   fpsText_.str("");
   fpsText_ << "FPS " << avg_fps;
   fpsTexture_ = textureLab_.CreateTextureFont(renderer_, fpsFont_, fpsText_.str().c_str(), fpsColor_);

   game_.Update(delta_time);
}

void Engine::Render()
{
   SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
   SDL_RenderClear(renderer_);

   game_.Render(renderer_, GAME_SCALE);

   SDL_Rect fpsQuad = {20, WINDOW_HEIGHT - fpsTexture_.GetHeight(), fpsTexture_.GetWidth(), fpsTexture_.GetHeight()};
   SDL_RenderCopy(renderer_, fpsTexture_.GetTexture(), nullptr, &fpsQuad);
   SDL_RenderPresent(renderer_);
}
