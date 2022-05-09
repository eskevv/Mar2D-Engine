#include <windows.h>
#include <iostream>

#include "Engine.h"

int CHUNK_SIZE = 8;
std::map<std::string, std::map<Vec2, int>> map_chunks;

Engine::Engine() : isRunning_(false) {}

bool Engine::Initialize()
{
   SetCurrentDirectory("../");

   if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
      printf("Failed to initialize SDL. Error: %s\n", SDL_GetError());
      return false;
   }

   int img_flags{IMG_INIT_JPG | IMG_INIT_PNG};
   if (!(IMG_Init(img_flags) & img_flags)) {
      printf("Failed to initialize SDL_IMG. Error: %s\n", IMG_GetError());
      return false;
   }

   if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
      printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
      return false;
   }

   if (TTF_Init() != 0) {
      printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
      return false;
   }

   window_ = SDL_CreateWindow("Breakout", 2560 - (WINDOW_WIDTH + 20), 300, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);
   if (!window_) {
      printf("Failed to create the window. Error: %s\n", SDL_GetError());
      return false;
   }

   renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
   if (!renderer_) {
      printf("Failed to create the renderer. Error: %s\n", SDL_GetError());
      return false;
   }

   return isRunning_ = true;
}

void Engine::Run()
{
   Setup();
   while (isRunning_) {
      Events();
      Update();
      Render();
   }
}

void Engine::Quit()
{
   assetStore_.Clear();
   SDL_DestroyRenderer(renderer_);
   SDL_DestroyWindow(window_);
   renderer_ = nullptr;
   window_ = nullptr;
   Mix_Quit();
   IMG_Quit();
   SDL_Quit();
}

void Engine::Setup()
{
   graphics_ = {renderer_, WINDOW_WIDTH, WINDOW_HEIGHT};

   fps_.Init(assetStore_, renderer_);

   InitGame();

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
}

void Engine::Update()
{
   // cap frame rate
   int wait_time = MS_PER_FRAME - (systemTimer_.GetTicks() - fps_.GetFrameTime());
   if (wait_time > 0 && wait_time <= MS_PER_FRAME) {
      SDL_Delay(wait_time);
   }

   // calculate delta time
   double delta_time = (systemTimer_.GetTicks() - fps_.GetFrameTime()) / 1000.0;

   // calcualte FPS
   fps_.Update(systemTimer_, assetStore_, renderer_);

   // update camera
   graphics_.GetCamera()->Update(delta_time, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void Engine::Render()
{
   SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
   SDL_RenderClear(renderer_);

   fps_.Render(renderer_);
   RenderGame();

   SDL_RenderPresent(renderer_);
}

// *  GAME DEMO * //

std::map<Vec2, int> Engine::GenerateChunks(int x, int y)
{
   printf("%i, %i\n", x, y);
   std::map<Vec2, int> chunk_data;
   for (int y_pos = 0; y_pos < CHUNK_SIZE; y_pos++) {
      for (int x_pos = 0; x_pos < CHUNK_SIZE; x_pos++) {
         int target_x = x * CHUNK_SIZE + x_pos;
         int target_y = y * CHUNK_SIZE + y_pos;

         int tile_type = 0;
         if (target_y > 10)
            tile_type = 2;
         else if (target_y == 10)
            tile_type = 1;
         else if (target_y == 9)
            if (rand() % 4 == 1)
               tile_type = 3;
         if (tile_type != 0) {
            std::string id = std::to_string(target_x) + ',' + std::to_string(target_y);
            chunk_data[Vec2(target_x, target_y)] = tile_type;
            printf("%s\n", id.c_str());
         }
      }
   }
   return chunk_data;
}

void Engine::InitGame()
{
   assetStore_.CreateTexture(renderer_, "dirt", "assets/dirt.png");
   assetStore_.CreateTexture(renderer_, "grass", "assets/grass.png");
   assetStore_.CreateTexture(renderer_, "plant", "assets/plant.png");

   tiles_[1] = *assetStore_.GetTexture("grass");
   tiles_[2] = *assetStore_.GetTexture("dirt");
   tiles_[3] = *assetStore_.GetTexture("plant");
}

void Engine::GameInput() {}

void Engine::UpdateGame() {}

void Engine::RenderGame()
{
   for (int y = 0; y < 70; y++) {
      for (int x = 0; x < 80; x++) {
         int target_x = x - 1 + (int)(graphics_.GetCamera()->position_.x / (CHUNK_SIZE * 16));
         int target_y = y - 1 + (int)(graphics_.GetCamera()->position_.y / (CHUNK_SIZE * 16));
         std::string id = std::to_string(target_x) + ',' + std::to_string(target_y);

         if (map_chunks.find(id) == map_chunks.end()) {
            map_chunks[id] = GenerateChunks(target_x, target_y);
            printf("added chunk\n");
         }

         for (auto& tile : map_chunks[id]) {
            SDL_Rect dstRec = {(int)tile.first.x, (int)tile.first.y, 16, 16};
            int tile_type = tile.second;
            graphics_.Render(&tiles_[tile_type], nullptr, &dstRec, 0.0, nullptr, SDL_FLIP_NONE);
         }
      }
   }
}
