#include "score.h"

Score::Score()
  : position( go::coord2(25,75))
  , value(time(0))
  , won(FALSE){}

Score::~Score(){}

void Score::OnRender(HDC* dc)
{
  if (this->won)
  {
    std::ostringstream stm;
    stm << this->value;
    const std::string& tmp = stm.str();   
    const char* cstr = tmp.c_str();
    TextOut(*dc, this->position.x, this->position.y, cstr, tmp.length());
  }
}

void Score::OnUpdate(int dt)
{
  if (!this->won)
    this->value+=dt;
}