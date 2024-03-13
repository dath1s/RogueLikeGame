#pragma once
#include "Object.h"

class Scroll : public Object {
 public:
  int spells = 4;

  Scroll(int x, int y, int s = 10, int hp = -1) : Object() {
    this->x = x;
    this->y = y;
    this->hp = hp;
    this->sym = CHAR_FIREBALL_POTION;
    this->tag = "Scroll";
    this->damage = 0;
    this->dir = {0, 0};
    this->isIrrelevant = false;
  };

  void move() override {}
  void setHealth(int hp) override { 
    Player().fireballs += spells;
    this->isIrrelevant = true; 
  }
};