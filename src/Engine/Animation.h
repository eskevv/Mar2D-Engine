#pragma once

#include <SDL2/SDL.h>
#include "Timer.h"

class Animation
{
public:
   Animation() = default;
   Animation(int frames, int speed, bool isLoop, int width, int height);

   Timer frameTimer_;
   SDL_Rect clip_;

   int currentFrame_{0};
   int numFrames_{0};
   int frameSpeed_{0};
   bool isLoop_{false};

   void Reset();
   void Update(double dt);
   bool IsLastFrame() const;
};