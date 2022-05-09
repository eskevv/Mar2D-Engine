#include "Tile.h"

#include "Physics.h"

Tile::Tile(int x, int y, int size, int type) : type_(type)
{
   box_ = {x, y, size, size};
}

void Tile::Render(Graphics* graphics, Texture* texture, SDL_Rect* tiles[])
{
   // SDL_Rect cameraBox = graphics->GetCamera()->ReturnRect();

   // if (IsColliding(cameraBox, box_)) {
   graphics->Render(texture, nullptr, &box_, 0.0, nullptr, SDL_FLIP_NONE);
   // }
}

int Tile::GetType()
{
   return type_;
}

SDL_Rect Tile::GetBox()
{
   return box_;
}
