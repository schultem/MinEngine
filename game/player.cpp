#include "player.h"

Player::Player()
  : position(go::coord2(75,75))
  , speed(4)
  , size(10){}

Player::~Player(){}

void Player::OnRender(HDC* dc)
{
  Rectangle(*dc, this->position.x - this->size/2, 
                 this->position.y - this->size/2,
                 this->position.x + this->size/2, 
                 this->position.y + this->size/2);
}

void Player::OnInput(go::input* in)
{
  
  switch(in->get())
  {
    case VK_DOWN:
      this->SetPosition(this->position.x, this->position.y+this->speed);
      break;
    case VK_LEFT:
      this->SetPosition(this->position.x-this->speed, this->position.y);
      break;
    case VK_RIGHT:
      this->SetPosition(this->position.x+this->speed, this->position.y);
      break;
    case VK_UP:
      this->SetPosition(this->position.x, this->position.y-this->speed);
      break;
    default:
      break;
  }
}

bool Player::SetPosition(int x, int y)
{
  if ((this->game->GetResolution().x-this->size/2 > x)
  && (this->game->GetResolution().y-this->size/2 > y)
  && (x > this->size/2)
  && (y > this->size/2))
  {
    this->position = go::coord2(x,y);
    this->size+=1;
    this->points_earned += size*x + size*y;
    return TRUE;
  } else if (this->size-1)
  {
    this->size-=1;
  }
  return FALSE;
}

int Player::WithdrawPoints()
{
  int points = this->points_earned;
  this->points_earned=0;
  return points;
}