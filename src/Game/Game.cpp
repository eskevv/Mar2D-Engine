#include "Game.h"

Skeleton* Game::skeletons_[9];


void Game::Setup(TextureLab& textureLab, SDL_Renderer* renderer)
{
   textureLab.CreateTexture(renderer, "skely-react", "assets/images/skeleton_react.png");
   textureLab.CreateTexture(renderer, "skely-walk", "assets/images/skeleton_walk.png");
   textureLab.CreateTexture(renderer, "skely-attack", "assets/images/skeleton_attack.png");
   textureLab.CreateTexture(renderer, "skely-idle", "assets/images/skeleton_idle.png");
   textureLab.CreateTexture(renderer, "skely-dead", "assets/images/skeleton_dead.png");
   textureLab.CreateTexture(renderer, "skely-hurt", "assets/images/skeleton_hit.png");

   skeleton_ = {textureLab};

   for (int i = 0; i < 9; i++) {
      skeletons_[i] = new Skeleton(textureLab, 0);
   }
}

void Game::HandleInput(Input& input)
{
   skeleton_.HandleInput(input);
}

void Game::Update(double dt)
{
   for (int i = 0; i < 9; i++) {
      skeletons_[i]->Update(dt);
   }

   skeleton_.Update(dt);
}

void Game::Render(SDL_Renderer* renderer, float scale)
{
   for (int i = 0; i < 9; i++) {
      skeletons_[i]->Draw(renderer, scale);
   }

   skeleton_.Draw(renderer, scale);
}

void Game::Destroy()
{
   for (int i = 0; i < 9; i++) {
      delete skeletons_[i];
   }
}
