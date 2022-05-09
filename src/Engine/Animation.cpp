#include "Animation.h"

void Animation::Update(double dt)
{
   if (!isLoop_ && IsLastFrame()) {
      frameTimer_.Start();
   }
   currentFrame_ = (frameTimer_.GetTicks()  * frameSpeed_ / 1000)  % numFrames_;
   clip_.x = clip_.w * currentFrame_;
}

void Animation::Reset()
{
   frameTimer_.Start();
   currentFrame_ = 0;
}

bool Animation::IsLastFrame() const
{
   return currentFrame_ == numFrames_ - 1;
}

Animation::Animation(int frames, int speed, bool isLoop, int width, int height) : numFrames_(frames), frameSpeed_(speed), isLoop_(isLoop)
{
   clip_ = {0, 0, width, height};
   frameTimer_.Start();
}
