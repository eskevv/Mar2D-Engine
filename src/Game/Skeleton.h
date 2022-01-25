#pragma once

#include <SDL2/SDL_image.h>

#include "Input.h"
#include "TextureLab.h"
#include "Animation.h"

class Skeleton
{
public:
   Skeleton() = default;
   Skeleton(TextureLab& textureLab, int posX = 100, int posY = 800);

   void HandleInput(Input& input);
   void Update(double dt);
   void Draw(SDL_Renderer* renderer, float scale);

   SDL_Rect GetCollider();

private:
   static constexpr float MAX_SPEED{5.5};

   Texture* currentTexture_;

   SDL_Rect collider_;
   std::map<std::string, Animation*> animations_;
   std::map<std::string, Texture*> textures_;
   std::string currentAnimation_;

   float posX_{0};
   float posY_{0};
   float velocityX_{0};
   float velocityY_{0};

   bool moveRight_{false};
   bool moveLeft_{false};
   bool moveUp_{false};
   bool moveDown_{false};
   bool attacking_{false};
   int facing{0};

   void Attack();
   void Hurt();
   void AddAnimations(TextureLab& textureLab);
   void SetAnimation(const std::string& id);
};