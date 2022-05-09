#pragma once

#include <SDL2/SDL.h>
#include "Texture.h"
#include "Camera.h"
#include "Graphics.h"

class Tile
{
public:
   Tile() = default;
   Tile(int x, int y, int size, int type);

   void Render(Graphics* graphics, Texture* texture, SDL_Rect* tiles[]);

   int GetType();
   SDL_Rect GetBox();

   bool priorityDraw_{false};
private:
   SDL_Rect box_;


   int type_;
};