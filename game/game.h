#include "gameobject.h"
#include "player.h"
#include "score.h"

class Game : public go::Game
{
  public:
    virtual void OnStart();
    virtual void OnStop();
    virtual void OnUpdate(int dt);
    virtual void OnInput(go::input*);

    void AddScore(int);

    Game();
    ~Game();

    Player* player;
    Score* score;
};