#include "Timer.h"
#include <SDL2/SDL.h>

void Timer::Start()
{
   started_ = true;
   paused_ = false;
   startTicks_ = SDL_GetTicks();
   pausedTicks_ = 0;
}

void Timer::Stop()
{
   started_ = false;
   paused_ = false;
   startTicks_ = 0;
   pausedTicks_ = 0;
}

void Timer::Pause()
{
   if (started_ && !paused_) {
      paused_ = true;

      pausedTicks_ = SDL_GetTicks() - startTicks_;
      startTicks_ = 0;
   }
}

void Timer::Unpause()
{
   if (started_ && paused_) {
      paused_ = false;
      startTicks_ = SDL_GetTicks() - pausedTicks_;
      pausedTicks_ = 0;
   }
}

uint32_t Timer::GetTicks()
{
   uint32_t time = 0;

   if (started_) {
      if (paused_) {
         time = pausedTicks_;
      }
      else {
         time = SDL_GetTicks() - startTicks_;
      }
   }

   return time;
}

bool Timer::IsStarted()
{
   return started_;
}

bool Timer::IsPaused()
{
   return paused_ && started_;
}
