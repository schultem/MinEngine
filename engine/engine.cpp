#include <time.h>
#include <chrono>
#include "engine.h"

Engine::Engine(go::Game* game) 
  : game(game)
{
  this->game->OnStart();
}

Engine::~Engine(void)
{
  this->game->OnStop();
}

int Engine::Update(int dt)
{
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

  this->event_mtx.lock();
    this->game->event_handler->notify(dt);
  this->event_mtx.unlock();

  return (2000/(this->GetFramerate()+dt) - std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - begin).count()/1000);
}

void Engine::Event(HDC dc)
{
  this->event_mtx.lock();
    this->game->event_handler->notify(&dc);
  this->event_mtx.unlock();
}

void Engine::Event(go::input* in)
{
  this->event_mtx.lock();
    this->game->event_handler->notify(in);
  this->event_mtx.unlock();
}

void Engine::Event(go::actor* actor, go::component* other)
{
  this->event_mtx.lock();
    this->game->event_handler->notify(actor,other);
  this->event_mtx.unlock();
}
