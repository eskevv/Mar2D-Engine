#include "Graphics.h"

Graphics::Graphics(SDL_Renderer* renderer, int screenWidth, int screenHeight) : renderer_(renderer)
{
   camera_ = {0, 0, screenWidth, screenHeight};
}

void Graphics::Render(Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
   int x = static_cast<int>(dstRect->x - camera_.position_.x);
   int y = static_cast<int>(dstRect->y - camera_.position_.y);
   int w = dstRect->w * camera_.scale_;
   int h = dstRect->h * camera_.scale_;
   SDL_Rect dst = {x, y, w, h};

   SDL_RenderCopyEx(renderer_, texture->GetTexture(), srcRect, &dst, angle, center, flip);
}

void Graphics::RenderRect(SDL_Rect* dstRect)
{
   int x = static_cast<int>(dstRect->x - camera_.position_.x);
   int y = static_cast<int>(dstRect->y - camera_.position_.y);
   int w = dstRect->w * camera_.scale_;
   int h = dstRect->h * camera_.scale_;
   SDL_Rect dst = {x, y, w, h};

   SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
   SDL_RenderDrawRect(renderer_, &dst);
}

Camera* Graphics::GetCamera()
{
   return &camera_;
}

void Graphics::SetCamera(Vec2* target)
{
   camera_.target_ = target;
}
