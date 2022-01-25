#include "Input.h"

void Input::KeyDownEvent(SDL_Scancode code)
{
   if (!keysHeld_[code]) {
      keysPressed_[code] = 1;
   }
   keysHeld_[code] = 1;
}

void Input::KeyUpEvent(SDL_Scancode code)
{
   keysHeld_[code] = 0;
}

void Input::NewFrame()
{
   for (int i = 0; i < MAX_KEYS; i++) {
      keysPressed_[i] = 0;
   }
}

bool Input::IsPressed(SDL_Scancode code) const
{
   return keysPressed_[code] == true;
}


bool Input::IsHeld(SDL_Scancode code) const
{
   return keysHeld_[code] == true;
}