#pragma once

#include "Skeleton.h"
#include "TextureLab.h"

class Game
{
public:
   void Setup(TextureLab& textureLab, SDL_Renderer* renderer);
   void HandleInput(Input& input);
   void Update(double dt);
   void Render(SDL_Renderer* renderer, float scale);
   void Destroy();

   Skeleton skeleton_;
   static Skeleton* skeletons_[9];
};