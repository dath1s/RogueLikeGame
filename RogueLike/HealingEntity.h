#pragma once
#include "Object.h"

class HealingEntity : public Object {
 public:
  HealingEntity(int x, int y, int add = HEALING, int hp = 1) : Object() {
    this->x = x;
    this->y = y;
    this->hp = hp;
    this->damage = -add;
    this->sym = CHAR_HEAL;
    this->tag = "HealingEntity";
    this->isIrrelevant = false;
    this->dir = {0, 0};
  };

  void move() override { 
  }

  void setHealth(int hp) override { 
    this->isIrrelevant = true;
  }
};
