#pragma once
#include "Object.h"

 class DamageEntity : public Object {
  public:
   DamageEntity(int x, int y, int d = DAMAGE_FIREBALL_PLAYER)
       : Object() {
     this->x = x;
     this->y = y;
     this->hp = 0;
     this->damage = 0;
     this->sym = CHAR_EXPLOSION_DAMAGE;
     this->dir = {1, 0};
     this->tag = "DamageEntity";
     this->isIrrelevant = false;
   };

   void move() override {
     this->isIrrelevant = true;
   }

   void setHealth(int hp) override { 
     this->isIrrelevant = true; 
   }

  private:
   int lifetime = 1;
 };