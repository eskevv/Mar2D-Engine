#include "Skeleton.h"
#include "Game.h"
#include "Physics.h"

Skeleton::Skeleton(TextureLab& textureLab, int posX, int posY) : posX_(posX), posY_(posY)
{
   if (posX_ == 0) {
      posX_ = 200 + rand() % 1300;
   }
   if (posY_ == 0) {
      posY_ = 200 + rand() % 1300;
   }

   int x = static_cast<int>(posX_);
   int y = static_cast<int>(posY_);
   int w = static_cast<int>(20);
   int h = static_cast<int>(20);

   collider_ = {x, y, w, h};

   AddAnimations(textureLab);

   SetAnimation("idle");
}

void Skeleton::HandleInput(Input& input)
{
   attacking_ = false;

   if (input.IsHeld(SDL_SCANCODE_RIGHT)) {
      moveRight_ = true;
   } else {
      moveRight_ = false;
   }
   if (input.IsHeld(SDL_SCANCODE_LEFT)) {
      moveLeft_ = true;
   } else {
      moveLeft_ = false;
   }
   if (input.IsPressed(SDL_SCANCODE_E)) {
      attacking_ = true;
   }
}

void Skeleton::Update(double dt)
{
   if (facing >= 0) {
      facing = 1;
   }
   if (facing < 0) {
      facing = -1;
   }

   if (moveLeft_) {
      posX_ -= MAX_SPEED;
      facing -= 2;
      SetAnimation("walk");
   }
   if (moveRight_) {
      posX_ += MAX_SPEED;
      facing += 2;
      SetAnimation("walk");
   }
   if (!moveRight_ && !moveLeft_) {
      SetAnimation("idle");
   }

   collider_.x = posX_;
   collider_.y = posY_;

   if (attacking_) {
      SetAnimation("attack");
   }

   if (currentAnimation_ == "attack") {
      if (animations_[currentAnimation_]->currentFrame_ == 7) {
         Attack();
      } else if (animations_[currentAnimation_]->IsLastFrame()) {
         SetAnimation("idle");
         attacking_ = false;
      }
   }

   animations_[currentAnimation_]->Update(dt);
}

void Skeleton::Draw(SDL_Renderer* renderer, float scale)
{
   int posX = static_cast<int>(posX_);
   int posY = static_cast<int>(posY_);
   int width = animations_[currentAnimation_]->clip_.w * scale;
   int height = animations_[currentAnimation_]->clip_.h * scale;

   if (currentAnimation_ == "attack") {
      posY -= 5;
   }

   SDL_Rect dstRect = {posX, posY, width, height};
   SDL_Rect srcRect = animations_[currentAnimation_]->clip_;

   SDL_RendererFlip flip = facing > 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

   SDL_RenderCopyEx(renderer, currentTexture_->GetTexture(), &srcRect, &dstRect, 0.0, nullptr, flip);
}

SDL_Rect Skeleton::GetCollider()
{
   return collider_;
}

void Skeleton::Attack()
{
   SDL_Rect hitBox = {static_cast<int>(posX_), static_cast<int>(posY_), 50, 40};

   for (auto enemy : Game::skeletons_) {
      if (IsColliding(hitBox, enemy->GetCollider())) {
         enemy->Hurt();
      }
   }
}

void Skeleton::Hurt()
{
   SetAnimation("hurt");
}

void Skeleton::AddAnimations(TextureLab& textureLab)
{
   animations_["react"] = new Animation(4, 0.03, true, 22, 32, 0, 0);
   textures_["react"] = textureLab.GetTexture("skely-react");

   animations_["walk"] = new Animation(13, 0.03, true, 22, 32, 0, 0);
   textures_["walk"] = textureLab.GetTexture("skely-walk");

   animations_["attack"] = new Animation(18, 0.03, false, 43, 37, 0, 0);
   textures_["attack"] = textureLab.GetTexture("skely-attack");

   animations_["hurt"] = new Animation(8, 0.03, false, 30, 32, 0, 0);
   textures_["hurt"] = textureLab.GetTexture("skely-hurt");

   animations_["idle"] = new Animation(11, 0.03, true, 24, 32, 0, 0);
   textures_["idle"] = textureLab.GetTexture("skely-idle");

}

void Skeleton::SetAnimation(const std::string& id)
{
   if (animations_[currentAnimation_]) {
      animations_[currentAnimation_]->Reset();
   }
   currentAnimation_ = id;
   currentTexture_ = textures_[id];
}
