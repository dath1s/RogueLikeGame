#pragma once
#include "Object.h"
#include "Player.h"

class Sword : public Object {
 public:
  int spells = 4;

  Sword(int x, int y, int hp = -1) : Object() {
    this->x = x;
    this->y = y;
    this->hp = hp;
    this->sym = CHAR_STRONG_POTION;
    this->damage = 0;
    this->tag = "Sword";
    this->dir = {0, 0};
    this->isIrrelevant = false;
  };

  void move() override {
  }

  void setHealth(int hp) override { 
    Player().swingsOfSword += spells;
    this->isIrrelevant = true; 
  }
};