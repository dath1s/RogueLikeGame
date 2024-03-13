#pragma once
#include "Noise.h"
#include "Block.h"
#include "config.h"

#include <vector>

using namespace std;
class Terrain {
 public:
  explicit Terrain(long long seed = 1, int x = 0, int y = 0) : noise(seed) { 
    for (auto& i : weights) {
      wholeWeight += i;
    }

    distribution[0] = weights[1] / wholeWeight;
    for (int i = 1; i < sizeof(weights) / sizeof(int); ++i) {
      distribution[i] = distribution[i - 1] + weights[i] / wholeWeight;
    }
  }

  vector<vector<Block>> getTerrain(int x, int y) { 
    remX = x;
    remY = y;
    terrainMemory.clear();
    terrainMemory.reserve(FIELD_LENGTH);
    for (int iy = 0; iy < FIELD_LENGTH; ++iy) {
      terrainMemory.push_back(vector<Block>());
      terrainMemory.back().reserve(FIELD_LENGTH);
      for (int ix = 0; ix < FIELD_LENGTH; ++ix) {
        terrainMemory.back().push_back(
            getCell(ix - x - FIELD_LENGTH / 2, iy - y - FIELD_LENGTH / 2));
      }
    }

    return terrainMemory;
  }

  Block getCell(int x, int y) {
    float value = noise.Noise(x * 0.05f, y * 0.05f);
    value = value < 1 ? -value : value;
    int partOfValue = static_cast<int>(value);
    value -= partOfValue;

    for (int i = 0; i < sizeof(distribution) / sizeof(float); ++i) {
      if (value <= distribution[i]) {
        return blocks[i];
      }
    }
    return blocks[9];
  }

  ~Terrain();

 private:
  vector<vector<Block>> terrainMemory;
  int remX;
  int remY;
  PerlinNoise noise;

  // for calculations
  int weights[10] = {WEIGHT_GRASS,      WEIGHT_DOOR,      WEIGHT_WEAP_SWORD,
                     WEIGHT_HEAL,      WEIGHT_SPAWN_MEL, WEIGHT_SPAWN_RAN,
                     WEIGHT_SPAWN_TAN, WEIGHT_WALL,      WEIGHT_WEAP_FIER,
                     WEIGHT_BOMB};
  float distribution[10] = {};
  float wholeWeight = 0;
  Block blocks[10] = {Grass(),       Door(),       Weapon(),     Heal(),
                      SpawnerMel(), SpawnerRan(), SpawnerTan(), Wall(),
                      Fireball(),   Bomb()};
};

Terrain::~Terrain() {}
