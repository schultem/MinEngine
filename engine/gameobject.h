#pragma once
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "windows.h"

namespace go
{  
  class Game;
  class gameobject
  {
    public:
      static Game* game;
  };

  class coord2 : public gameobject
  {
    public:
      coord2(int x, int y) : x(x),y(y) {};
      int x,y;
  };

  class coord3 : public gameobject
  {
    public:
      coord3(int x, int y, int z) : x(x),y(y),z(z) {};
      int x,y,z;
  };

  class input : public gameobject
  {
    public:
      input(){suppressed=FALSE;};
  
      virtual int get(){return 0;};
      void suppress(){suppressed=TRUE;};

    protected:
      bool suppressed;
  };

  class keyinput : public input
  {
    public:
      keyinput(int p) : param(p) {};
  
      virtual int get(){return (suppressed ? 0 : param);};

    protected:
      int param;
  };

  class actor;

  class component : public gameobject
  {
    public:
      component(){};
      ~component(){};
      actor* parent;

      virtual void OnUpdate(int dt){};
      virtual void OnInput(input*){};
      virtual void OnRender(HDC*){};
      virtual void OnInteract(actor*){};
  };

  class actor : public gameobject
  {
    public:
      actor();
      ~actor();
  
      void AddComponent(component*);
      void RemoveComponent(component*);

      void update(int dt);
      void user(input*);
      void render(HDC*);
      void interact(component*);

    protected:
      virtual void OnUpdate(int dt){};
      virtual void OnInput(input*){};
      virtual void OnRender(HDC*){};
      virtual void OnInteract(component*){};

      std::vector<component*> components;
  };

  class event : public gameobject
  {
    std::vector<actor*> actors;

    public:
      event(){};
      void attach(actor*);
      void detach(actor*);
  
      void notify(int dt);
      void notify(HDC*);
      void notify(input*);
      void notify(actor*, component*);

      int dt;
  };

  class Game : public gameobject
  {
    public:
      Game(std::string name, coord2 res, unsigned int rate) :
        name(name),resolution(res),framerate(rate){event_handler = new event();};
      ~Game(){delete event_handler;};
  
      virtual void OnStart(){};
      virtual void OnStop(){};
      virtual void OnUpdate(){};
      virtual void OnUpdate(int dt){};
      virtual void OnInput(input*){};
      virtual void OnRender(HDC*){};
      virtual void OnInteract(go::actor*, go::component*){};

      std::string GetName(){ return name; };
      coord2 GetResolution(){ return resolution; };
      unsigned int GetFramerate(){ return framerate; };
  
      event* event_handler;
  
    protected:
      std::string name;
      coord2 resolution;
      unsigned int framerate;
  };
}
