#pragma once

#include <SDL2/SDL.h>

class Input
{
public:
   Input() = default;

   void KeyDownEvent(SDL_Scancode code);
   void KeyUpEvent(SDL_Scancode code);
   void NewFrame();

   bool IsPressed(SDL_Scancode code) const;
   bool IsHeld(SDL_Scancode code) const;

private:
   static const short MAX_KEYS{360};

   bool keysPressed_[MAX_KEYS];
   bool keysHeld_[MAX_KEYS];
};
