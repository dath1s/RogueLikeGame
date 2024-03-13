#pragma once
#include "Collider.h"
#include "config.h"
#include "PlayerLog.h"
#include <utility>

class Object {
 public:
  explicit Object();
  void setPosition(int x, int y);
  virtual void setHealth(int hp) = 0;
  virtual void move() = 0;
  float getDamage();
  ~Object();

  int x;
  int y;
  int hp;
  int sym;
  int damage;
  int isIrrelevant;
  pair<int, int> dir;
  string tag;
};

Object::Object() : tag(""){};

void Object::setPosition(int x, int y) {
  this->x = x;
  this->y = y;
}

float Object::getDamage() { return damage; }

Object::~Object() { }

