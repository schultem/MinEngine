#include "gameobject.h"
#include <algorithm>

void go::event::notify(int dt)
{
  this->dt=dt;
  this->game->OnUpdate(dt);
  for(auto actor: this->actors)
  {
    actor->update(dt);
  }
}

void go::event::notify(HDC* dc)
{
  this->game->OnRender(dc);
  for(auto actor: this->actors)
  {
    actor->render(dc);
  }
}

void go::event::notify(go::input* input)
{
  this->game->OnInput(input);
  for(auto actor: this->actors)
  {
    actor->user(input);
  }
}

void go::event::notify(go::actor* actor, go::component* other)
{
  this->game->OnInteract(actor, other);
  actor->interact(other);
}

void go::event::attach(go::actor* actor)
{
  this->actors.push_back(actor);
}

void go::event::detach(actor* actor)
{    
  this->actors.erase(std::remove(this->actors.begin(), this->actors.end(), actor), this->actors.end());    
}
