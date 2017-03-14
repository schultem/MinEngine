#include "mingw-std-threads-master/mingw.mutex.h"
#include "gameobject.h"
#include <string>

class Engine
{
  public:
    Engine(go::Game* game);
    ~Engine();

    int Update(int dt);
    std::string GetName(){ return game->GetName(); }
    int GetFramerate(){ return game->GetFramerate(); };
    go::coord2 GetResolution(){ return game->GetResolution(); };

    void Event(HDC);
    void Event(go::input*);
    void Event(go::actor*, go::component*);

    go::Game* game;

  private:
    std::mutex event_mtx;
};
