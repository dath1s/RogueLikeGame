#pragma once
#include "Object.h"
#include "HealingEntity.h"
#include "Sword.h"
#include "Scroll.h"
#include <memory>

class EnemyMel : public Object {
 public:
  EnemyMel(int x, int y, shared_ptr<Object> pl, int hp = HP_ENEMY_MEL,
           int d = DAMAGE_ENEMY_MEL)
      : Object() {
    this->x = x;
    this->y = y;
    this->hp = hp;
    this->damage = d;
    player = pl;
    this->sym = CHAR_ENEMY_MEL;
    this->tag = "EnemyMel";
    this->isIrrelevant = false;
    this->dir = {1, 0};   
  };

  void move() override {
    auto r = RADIUS_ENEMY;
    this->x -= dir.first;
    this->y -= dir.second;
    dir = {0, 0};
    if (player->x <= x + r && player->x >= x - r && player->y <= y + r &&
        player->y >= y - r) {
      if (player->x > x) {
        dir.first = -1;
      } else if (player->x < x) {
        dir.first = 1;
      } else if (player->y < y) {
        dir.second = 1;
      } else {
        dir.second = -1;
      }
    } else {
      do {
        dir = {rand() % 3 - 1, rand() % 3 - 1};
      } while (!dir.first ^ !dir.second);
    }
  }

  void setHealth(int hp) override {
    if (hp == this->hp) {
      do {
        dir = {rand() % 3 - 1, rand() % 3 - 1};
      } while (!dir.first ^ !dir.second);
    } else {
      this->hp = max(hp, 0);
      if (!this->hp) {
        if (rand() & 1) {
          Pool().objects.push_back(
              make_shared<HealingEntity>(this->x, this->y));
        } else {
          Pool().objects.push_back(make_shared<Sword>(this->x, this->y));
        }
        this->isIrrelevant = true;
      }
    }
  }

 private:
  shared_ptr<Object> player;
};