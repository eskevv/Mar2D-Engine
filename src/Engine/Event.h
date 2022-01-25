#pragma once

#include <string>

class Event {
public:
  Event() = default;
};

class TestEvent : public Event {
public:
  std::string target_;

  TestEvent(const std::string& target) : target_(target) {}
};