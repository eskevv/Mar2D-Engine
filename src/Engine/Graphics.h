#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Camera.h"
#include "Texture.h"

class Graphics
{
public:
   Graphics() = default;
   Graphics(SDL_Renderer* renderer, int screenWidth, int screenHeight);

   void SetCamera(Vec2* target);
   
   void Render(Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, double angle, SDL_Point* center, SDL_RendererFlip flip);
   void RenderRect(SDL_Rect* dstRect);

   Camera* GetCamera();

private:
   Camera camera_;
   SDL_Renderer* renderer_ {nullptr};
};
