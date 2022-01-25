#pragma once

#include <functional>
#include <list>
#include <map>
#include <memory>
#include <typeindex>
#include "Event.h"

////////////////////////////////////////////////
// *Event Systems
////////////////////////////////////////////////

class IEventCallback {
public:
  virtual ~IEventCallback() = default;

  virtual void Execute(Event& e) = 0;
};

template <typename TOwner, typename TEvent>
class EventCallback : public IEventCallback {
private:
  typedef void (TOwner::*CallbackFunction)(TEvent&);

  TOwner* owner_;
  CallbackFunction function_;

public:
  EventCallback(TOwner* owner, CallbackFunction function) : owner_(owner), function_(function) {}
  virtual ~EventCallback() override = default;

  virtual void Execute(Event& e) override { std::invoke(function_, owner_, static_cast<TEvent&>(e)); }
};

class EventBus {
public:
  typedef std::list<std::unique_ptr<IEventCallback>> HandlerList;

  template <typename TEvent, typename TOwner>
  void SubscribeToEvent(TOwner* owner, void (TOwner::*function)(TEvent&))
  {
    if (!subscribers_[typeid(TEvent)].get()) {
      subscribers_[typeid(TEvent)] = std::make_unique<HandlerList>();
    }

    auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(owner, function);
    subscribers_[typeid(TEvent)]->push_back(std::move(subscriber));
  }

  template <typename TEvent, typename... TArgs>
  void EmitEvent(TArgs&&... args)
  {
    auto handlers = subscribers_[typeid(TEvent)].get();
    if (handlers) {
      for (auto it = handlers->begin(); it != handlers->end(); it++) {
        TEvent event(std::forward<TArgs>(args)...);
        it->get()->Execute(event);
      }
    }
  }

private:
  std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers_;
};