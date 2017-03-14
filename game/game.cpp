#include "game.h"
#include <iostream>

Game new_game = Game();
go::Game* go::gameobject::game = &new_game;

Game::Game() : go::Game("seeder", go::coord2(150,150), 25)
{
  this->player = new Player();
  this->score = new Score();
}

void Game::OnInput(go::input* input)
{
  if (this->score->won)
  {
    input->suppress();
  }
}

void Game::OnUpdate(int dt)
{
  this->score->value += this->player->WithdrawPoints();

  this->score->won = this->player->size > (this->GetResolution().x - 2*this->player->speed);
}

Game::~Game()
{
  delete this->player;
  delete this->score;
}

void Game::OnStart()
{
}

void Game::OnStop()
{
}
