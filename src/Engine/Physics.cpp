#include "Physics.h"

bool IsColliding(SDL_Rect a, SDL_Rect b)
{
   int aTop = a.y, bTop = b.y;
   int aBottom = a.y + a.h, bBottom = b.y + b.h;
   int aLeft = a.x, bLeft = b.x;
   int aRight = a.x + a.w, bRight = b.x + b.w;

   return (aLeft <= bRight && aRight >= bLeft && aTop <= bBottom && aBottom >= bTop);
}

bool IsCollidingPixel(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b)
{
   for (size_t boxA = 0; boxA < a.size(); boxA++) {
      for (size_t boxB = 0; boxB < b.size(); boxB++) {
         if (IsColliding(a[boxA], b[boxB])) {
            return true;
         }
      }
   }
   return false;
}

bool IsColliding(Circle& a, Circle& b)
{
   int totalRadius = a.r + b.r;
   int totalRadiusSquared = totalRadius * totalRadius;

   return (DistanceSquared(a.x, a.y, b.x, b.y) < totalRadiusSquared);
}

bool IsColliding(Circle& a, SDL_Rect& b)
{
   int cX, cY;

   if (a.x < b.x) {
      cX = b.x;
   } else if (a.x > b.x + b.w) {
      cX = b.x + b.w;
   } else {
      cX = a.x;
   }

   if (a.y < b.y) {
      cY = b.y;
   } else if (a.y > b.y + b.h) {
      cY = b.y + b.h;
   } else {
      cY = a.y;
   }

   return (DistanceSquared(a.x, a.y, cX, cY) < a.r * a.r);
}

double DistanceSquared(int x1, int y1, int x2, int y2)
{
   int deltaX = x2 - x1;
   int deltaY = y2 - y1;

   return deltaX * deltaX + deltaY * deltaY;
}
