#include "gameobject.h"
#include <string>
#include <sstream>
#include <iostream>
#include <time.h>

class Score : public go::actor
{
  public:
    virtual void OnUpdate(int dt);
    virtual void OnRender(HDC*);
    bool SetPosition(int x, int y);

    Score();
    ~Score();

    go::coord2 position;
    long unsigned int value;
    bool won;
};
