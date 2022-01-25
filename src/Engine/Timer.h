#pragma once

#include <cstdint>

class Timer {
public:
   Timer() = default;

   void Start();
   void Stop();
   void Pause();
   void Unpause();

   uint32_t GetTicks();

   bool IsStarted();
   bool IsPaused();

private:
   uint32_t startTicks_{0};
   uint32_t pausedTicks_{0};

   bool paused_{false};
   bool started_{false};
};