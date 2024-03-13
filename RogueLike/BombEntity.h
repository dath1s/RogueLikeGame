#pragma once
#include "Object.h"

 class BombEntity : public Object {
  public:
   BombEntity(int x, int y, pair<int, int> direct = {0, 0},
              int objectSym = CHAR_BOMB, int dr = RADIUS_FIREBALL, int lt = -1,
              int d = DAMAGE_FIREBALL_PLAYER)
       : Object() {
     this->x = x;
     this->y = y;
     this->hp = 1;
     this->damage = d;
     this->dir = direct;
     lifetime = lt;
     this->sym = objectSym;
     this->tag = "BombEntity";
     this->isIrrelevant = false;
   };

   void move() override {
     setPosition(x - dir.first, y - dir.second);
     if (!--lifetime) {
       this->isIrrelevant = true;
     }
   }

   void setHealth(int hp) override { 
     this->isIrrelevant = true;
   }

  private:
   int lifetime;
   int radius;
 };