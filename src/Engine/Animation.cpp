#include "Animation.h"

void Animation::Update(double dt)
{
   startTime_ += dt;
   printf("%f", startTime_);
   if (startTime_ >= frameSpeed_) {
      startTime_ = 0.0;
      currentFrame_++;
   }

   if (currentFrame_ >= numFrames_) {
      if (isLoop_) {
         currentFrame_ = 0;
      } else {
         currentFrame_ = numFrames_ - 1;
      }
   }

   clip_.x = clip_.w * currentFrame_;
}

void Animation::Reset() 
{
   currentFrame_ = 0;
}

bool Animation::IsLastFrame() 
{
   return currentFrame_ == numFrames_ - 1; 
}


Animation::Animation(int frames, double speed, bool isLoop, int width, int height, int row, int column)
    : numFrames_(frames), frameSpeed_(speed), isLoop_(isLoop)
{
   clip_ = {column, row, width, height};
}
