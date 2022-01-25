#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "Circle.h"

bool IsColliding(SDL_Rect a, SDL_Rect b);

bool IsCollidingPixel(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b);

bool IsColliding(Circle& a, Circle& b);

bool IsColliding(Circle& a, SDL_Rect& b);

double DistanceSquared(int x1, int y1, int x2, int y2);
