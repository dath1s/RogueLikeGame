#pragma once
#include "Object.h"

class EnemyRan : public Object {
 public:
  Object* pl;
  explicit EnemyRan(int x, int y, shared_ptr<Player> pl, int hp = HP_ENEMY_RAN,
                    int d = DAMAGE_ENEMY_RAN)
      : Object() {

    this->x = x;
    this->y = y;
    this->hp = hp;
    this->damage = 0;
    player = pl;
    this->sym = CHAR_ENEMY_RAN;
    this->tag = "EnemyMel";
    this->isIrrelevant = false;
    this->dir = {1, 0};  
  };

  void move() override {
    auto r = RADIUS_ENEMY;
    if (player->x <= x + r && player->x >= x - r && player->y <= y + r &&
        player->y >= y - r) {
      if (!kd) {
        if (x == player->x) {
          Pool().objects.push_back(std::make_unique<Arrow>(Arrow(
              x, -(y > player->y ? 1 : -1) + y, {0, (y > player->y ? 1 : -1)})));
          kd = KD_ENEMY_RAN;
        } else if (x == player->x) {
          Pool().objects.push_back(std::make_unique<Arrow>(Arrow(
              -(x > player->x ? 1 : -1) + x, y, {(x > player->x ? 1 : -1), 0})));
          kd = KD_ENEMY_RAN;
        } else {
          this->x -= dir.first;
          this->y -= dir.second;
          if (player->x > x) {
            dir.first = -1;
          } else if (player->x < x) {
            dir.first = 1;
          } else if (player->y < y) {
            dir.second = 1;
          } else if (player->y > y) {
            dir.second = -1;
          } else {
            do {
              dir = {rand() % 3 - 1, rand() % 3 - 1};
            } while (!(dir.first || dir.second));
          }
        }
      } else {
        --kd;
      }
    }
  }

  void setHealth(int hp) override {
    if (hp == this->hp) {
      do {
        dir = {rand() % 3 - 1, rand() % 3 - 1};
      } while (!(dir.first || dir.second));
    } else {
      this->hp = max(hp, 0);
      if (!this->hp) {
        if (rand() & 1) {
          Pool().objects.push_back(
              make_shared<HealingEntity>(this->x, this->y));
        } else {
          Pool().objects.push_back(make_shared<Scroll>(this->x, this->y));
        }
        this->isIrrelevant = true;
      }
    }
  }

 private:
  int kd = 0;
  shared_ptr<Object> player;
};