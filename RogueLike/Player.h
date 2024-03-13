#pragma once
#include "Object.h"
#include "config.h"

#include <vector>
#include <memory>

 class Player : public Object {
  public:
   static int swingsOfSword;
   static int fireballs;
   static int score;
   pair<int, int> dir = {0, 0};
   bool isShot = false;

   Player(int x = 0, int y = 0, int hp = HP_PLAYER, int d = DAMAGE_PLAYER)
       : Object() {
     this->x = x;
     this->y = y;
     this->hp = hp;
     this->damage = d;
     sym = CHAR_PLAYER;
     this->tag = "Player";
   };

   void move() override {
   };

   void setHealth(int hp) {
     PlayerLog log;
     if (hp > this->hp) {
       log.Logs.push_back("Player get " + to_string(hp - this->hp) + " hp");
     } else {
       if (hp == this->hp) {
         log.Logs.push_back("Player get bonus");
       } else {
         log.Logs.push_back("Player lost " + to_string(this->hp - hp) + " hp"); 
       }
     }
     this->hp = max(min(hp, HP_PLAYER), 0);
   }

   ~Player() { }

  private:
   std::vector<std::unique_ptr<Object>> arrows;
 };

 int Player::swingsOfSword;
 int Player::fireballs;
 int Player::score;