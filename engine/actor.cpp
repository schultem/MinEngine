#include <algorithm>
#include <iostream>
#include "gameobject.h"

go::actor::actor()
{
  go::gameobject::game->event_handler->attach(this);
};

go::actor::~actor()
{
  for (auto component : this->components)
  {
    this->RemoveComponent(component);
    delete component;
  }
  go::gameobject::game->event_handler->detach(this);
}

void go::actor::update(int dt)
{
  this->OnUpdate(dt);
  for (auto component : this->components)
  {
    component->OnUpdate(dt);
  }
}

void go::actor::user(go::input* input)
{
  this->OnInput(input);
  for (auto component : this->components)
  {
    component->OnInput(input);
  }
}

void go::actor::render(HDC* dc)
{
  this->OnRender(dc);
  for (auto component : this->components)
  {
    component->OnRender(dc);
  }
}

void go::actor::interact(go::component* other)
{
  this->OnInteract(other);
  for (auto component : this->components)
  {
    component->OnInteract(this);
  }
}

void go::actor::AddComponent(go::component* component)
{
  this->components.push_back(component);
}

void go::actor::RemoveComponent(go::component* component)
{    
  this->components.erase(std::remove(this->components.begin(), this->components.end(), component), this->components.end());    
}
