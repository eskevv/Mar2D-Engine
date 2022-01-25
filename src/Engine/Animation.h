#pragma once

#include <SDL2/SDL.h>

class Animation
{
public:
   Animation() = default;
   Animation(int frames, double speed, bool isLoop, int width, int height, int row, int column);

   SDL_Rect clip_;
   int currentFrame_{0};
   int numFrames_{0};
   double frameSpeed_{0};
   double startTime_{0.0};
   bool isLoop_{false};

   void Reset();
   void Update(double dt);
   bool IsLastFrame();
};