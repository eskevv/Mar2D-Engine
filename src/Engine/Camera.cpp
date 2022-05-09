#include "Camera.h"

Camera::Camera(int x, int y, int w, int h) : width_(w), height_(h)
{
   position_.x = x;
   position_.y = y;
}

void Camera::Update(double dt, int width, int height)
{
   if (target_) {
      if (styleX == FIXED) {
         position_.x = (target_->x - width_ / 2);
      } else if (styleX == FLOAT) {
         CameraFloat("X");
      }
      if (styleY == FIXED) {
         position_.y = (target_->y - height_ / 2);
      } else if (styleY == FLOAT) {
         CameraFloat("Y");
      }
   }
}

void Camera::CameraFloat(const std::string& axis)
{
   float distanceX = abs((target_->x - width_ / 2) - position_.x);
   float distanceY = abs((target_->y - height_ / 2) - position_.y);

   if (axis == "X") {
      if (position_.x + speedX_ <= target_->x - width_ / 2) {
         position_.x += distanceX / speedX_;
      } else if (position_.x - speedX_ >= target_->x - width_ / 2) {
         position_.x -= distanceX / speedX_;
      }
   } else if (axis == "Y") {
      if (position_.y + speedY_ <= target_->y - height_ / 2) {
         position_.y += distanceY / speedY_;
      } else if (position_.y - speedY_ >= target_->y - height_ / 2) {
         position_.y -= distanceY / speedY_;
      }
   }
}

void Camera::SetCameraStyle(const std::string& axis, Style style, float speed)
{
   if (axis == "X" || axis == "Y") {
      if (style == FIXED || style == FLOAT) {
         styleX = axis == "X" ? style : styleX;
         speedX_ = axis == "X" ? speed : speedX_;

         styleY = axis == "Y" ? style : styleY;
         speedY_ = axis == "Y" ? speed : speedY_;
      }
   } else {
      std::cout << "Invalid axis for camera style chosen." << std::endl;
   }
}

SDL_Rect Camera::ReturnRect()
{
   return SDL_Rect{static_cast<int>(position_.x), static_cast<int>(position_.y), width_, height_};
}
