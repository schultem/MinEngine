#include "gameobject.h"

class Player : public go::actor
{
  public:
    virtual void OnRender(HDC*);
    virtual void OnInput(go::input*);
    bool SetPosition(int x, int y);
    int WithdrawPoints();

    Player();
    ~Player();

    go::coord2 position;
    int speed;
    unsigned int size;
  
  private:
    int points_earned;

};
