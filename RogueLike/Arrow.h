#pragma once
#include "Object.h"
#include "config.h"
#include "Pool.h"

class Arrow : public Object {
 public:
  int speed = 3;

  Arrow(int x, int y, std::pair<int, int> direct = {1, 0}, int speed = 1,
        int hp = 1, int d = DAMAGE_AROOW_PLAYER)
      : Object() {
    this->x = x;
    this->y = y;
    this->hp = hp;
    this->damage = d;
    this->speed = speed;
    this->tag = "Arrow";
    this->isIrrelevant = false;
    this->sym = CHAR_ARROW;
    this->dir = direct;
  };

  void move() override {
    for (int i = 0; i < speed; i++) {
      setPosition(x - dir.first, y - dir.second);
    }
    if (!--lifetime) {
      isIrrelevant = true;
    }
  }

  void setHealth(int hp) override { 
    isIrrelevant = true;
  }

  ~Arrow() { 
    isIrrelevant = true;
  }

 private:
  int lifetime = 10;
};