#pragma once

#include <SDL2/SDL.h>
#include "Vec2.h"

class Camera
{
public:
   Camera() = default;
   Camera(int x, int y, int w, int h);

   enum Style {FIXED, FLOAT};

   Style styleX = FIXED;
   Style styleY = FIXED;
   Vec2 position_;
   Vec2* target_ = nullptr;

   float speedX_{10.0f};
   float speedY_{10.0f};
   int width_{0};
   int height_{0};
   float scale_{1.0f};

   void Update(double dt, int width, int height);
   void CameraFloat(const std::string& axis);
   void SetCameraStyle(const std::string& axis, Style style, float speed);

   SDL_Rect ReturnRect();
};