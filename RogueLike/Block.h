#pragma once
#include "config.h"
#include <string>

using namespace std;

class Block {
 public:
  Block() {}
  Block(bool walk, bool iso, int sym, string tag)
      : isWalkable(walk), isSpawnObject(iso), sym(sym), tag(tag) {}

  virtual ~Block() = default;
  bool isWalkable;
  bool isSpawnObject;
  int sym;
  string tag;
  //pair<int, int> place;
};

class Wall: public Block {
 public:
  Wall() : Block(false, true, CHAR_WALL, "Wall"){};
};

class Grass : public Block {
 public:
  Grass() : Block(true, false, CHAR_GRASS, "Grass"){};
};

class Bomb : public Block {
 public:
  Bomb() : Block(true, true, CHAR_GRASS, "Bomb"){};
};

class SpawnerMel : public Block {
 public:
  SpawnerMel() : Block(false, true, CHAR_SPAWN_MEL, "Spawner-Mel"){};
};

class SpawnerRan : public Block {
 public:
  SpawnerRan() : Block(false, true, CHAR_SPAWN_RAN, "Spawner-Ran"){};
};

class SpawnerTan : public Block {
 public:
  SpawnerTan() : Block(false, true, CHAR_SPAWN_TAN, "Spawner-Tan"){};
};

class Heal : public Block {
 public:
  Heal() : Block(true, true, CHAR_GRASS, "Heal"){};
};

class Weapon : public Block {
 public:
  Weapon() : Block(true, true, CHAR_GRASS, "Sword"){};
};

class Fireball : public Block {
 public:
  Fireball() : Block(true, true, CHAR_GRASS, "Fireball"){};
};

class Door : public Block {
 public:
  Door() : Block(true, false, CHAR_DOOR, "Door"){};
};