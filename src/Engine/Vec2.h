#pragma once
#include <iostream>

class Vec2 {
public:
  float x{0};
  float y{0};

  Vec2() {}
  Vec2(float x, float y);

  bool operator==(const Vec2 &v) const;
  bool operator!=(const Vec2 &v) const;

  Vec2 operator+(const Vec2 &v) const;
  Vec2 operator-(const Vec2 &v) const;
  Vec2 operator/(float val) const;
  Vec2 operator*(float val) const;

  bool operator<(const Vec2& vec2) const;

  void operator+=(const Vec2 &val);
  void operator-=(const Vec2 &val);
  void operator*=(float val);
  void operator/=(float val);

  float dist(const Vec2 &v) const;

  friend std::ostream &operator<<(std::ostream &stream, const Vec2 &vector);
};
