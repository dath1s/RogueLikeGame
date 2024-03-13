#pragma once
#include <map>
#include <string>
#include <cstdio>

#include <cstdio>

using namespace std;

//class Collider {
// public:
//  static map<Object*, pair<int, int>> colliders;
//
//  Object& collide(Object& parent) {
//    for (auto& kv : colliders) {
//      if (kv.first != &parent) {
//        if (kv.second.first == parent.x && kv.second.second == parent.y ) {
//          return *kv.first;
//        }
//      }
//    }
//    printf("returned-%s", ne.tag.c_str());
//    printf("rebilded-%s", dynamic_cast<Object&>(ne).tag.c_str());
//    return dynamic_cast<Object&>(ne);
//  }
//
//  class NullEntity : public Object {
//   public:
//    NullEntity() { tag = ""; }
//
//    void move() override {}
//    void setHealth(int hp) override {}
//  };
//  NullEntity ne;
//};
//
//map<Object*, pair<int, int>> Collider::colliders;
//
//Collider collider;




