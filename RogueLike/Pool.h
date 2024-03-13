#pragma once
#include <vector>
#include <memory>

#include "Object.h"

class Pool {
 public:
  static std::vector<std::shared_ptr<Object>> objects;
};

std::vector<std::shared_ptr<Object>> Pool::objects;
