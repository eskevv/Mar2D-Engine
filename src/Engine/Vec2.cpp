#include "Vec2.h"

Vec2::Vec2(float x, float y) : x(x), y(y) {}

bool Vec2::operator==(const Vec2 &vec) const { return x == vec.x && y == vec.y; }
bool Vec2::operator!=(const Vec2 &vec) const { return x != vec.x || y != vec.y; }
Vec2 Vec2::operator+(const Vec2 &vec) const { return Vec2(x + vec.x, y + vec.y); }
Vec2 Vec2::operator-(const Vec2 &vec) const { return Vec2(x - vec.x, y - vec.y); }
Vec2 Vec2::operator/(float val) const { return Vec2(x / val, y / val); }

bool Vec2::operator<(const Vec2& vec2) const
{
    if(x < vec2.x) return true;
    if(x > vec2.x) return false;
    //x == coord.x
    if(y < vec2.y) return true;
    if(y > vec2.y) return false;
    //x == coord.x && y == coord.y
    //*this == coord
    return false;
}

Vec2 Vec2::operator*(float val) const { return Vec2(x * val, y * val); }

void Vec2::operator+=(const Vec2 &vec)
{
  x += vec.x;
  y += vec.y;
}

void Vec2::operator-=(const Vec2 &vec)
{
  x -= vec.x;
  y -= vec.y;
}

void Vec2::operator/=(float scale)
{
  x /= scale;
  y /= scale;
}

void Vec2::operator*=(float scale)
{
  x *= scale;
  y *= scale;
}

float Vec2::dist(const Vec2 &v) const { return 0.0f; }

std::ostream &operator<<(std::ostream &stream, const Vec2 &vector)
{
  return stream << vector.x << " " << vector.y << "\n";
}