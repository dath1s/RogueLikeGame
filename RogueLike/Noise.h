#pragma once
#include <cstdlib>

class PerlinNoise {
 public:
  PerlinNoise(long long seed = 1) {
    srand(seed);
    for (auto& i : permutationTable) {
      i = rand() & 3;
    }
  }

  float Noise(float fx, float fy) {
    int left = static_cast<int>(fx);
    int top = static_cast<int>(fy);
    float pointInQuadX = fx - left;
    float pointInQuadY = fy - top;

    float topLeftGradient[2];
    GetPseudoRandomGradientVector(topLeftGradient, left, top);
    float topRightGradient[2];
    GetPseudoRandomGradientVector(topRightGradient, left + 1, top);
    float bottomLeftGradient[2];
    GetPseudoRandomGradientVector(bottomLeftGradient, left, top + 1);
    float bottomRightGradient[2];
    GetPseudoRandomGradientVector(bottomRightGradient, left + 1, top + 1);

    float distanceToTopLeft[2] = {pointInQuadX, pointInQuadY};
    float distanceToTopRight[2] = {pointInQuadX - 1, pointInQuadY};
    float distanceToBottomLeft[2] = {pointInQuadX, pointInQuadY - 1};
    float distanceToBottomRight[2] = {pointInQuadX - 1, pointInQuadY - 1};

    float tx1 = Dot(distanceToTopLeft, topLeftGradient);
    float tx2 = Dot(distanceToTopRight, topRightGradient);
    float bx1 = Dot(distanceToBottomLeft, bottomLeftGradient);
    float bx2 = Dot(distanceToBottomRight, bottomRightGradient);

    pointInQuadX = QunticCurve(pointInQuadX);
    pointInQuadY = QunticCurve(pointInQuadY);

    float tx = Lerp(tx1, tx2, pointInQuadX);
    float bx = Lerp(bx1, bx2, pointInQuadX);
    float tb = Lerp(tx, bx, pointInQuadY);

    return tb;
  }

  float Noise(float fx, float fy, int octaves, float persistence = 0.5f) {
    float amplitude = 1;
    float max = 0;
    float result = 0;

    while (octaves-- > 0) {
      max += amplitude;
      result += Noise(fx, fy) * amplitude;
      amplitude *= persistence;
      fx *= 2;
      fy *= 2;
    }

    return result / max;
  }

 private:
  char permutationTable[1024];

  void GetPseudoRandomGradientVector(float* source, int x, int y) {
    float options[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    float* choosen = options[permutationTable[((x * 1836311903) ^
                                               (y * 2971215073) + 4807526976) &
                                              1023]];
    source[0] = choosen[0];
    source[1] = choosen[1];
  }

  static float QunticCurve(float t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
  }

  static float Lerp(float a, float b, float t) { return a + (b - a) * t; }

  static float Dot(float* a, float* b) { return a[0] * b[0] + a[1] * b[1]; }
};