#pragma once
#include "Object.h"

class NullEntity : public Object {
 public:
  NullEntity() { 
	this->tag = "";
    this->isIrrelevant = true;
  }

  void move() override { }

  void setHealth(int hp) override { }
};