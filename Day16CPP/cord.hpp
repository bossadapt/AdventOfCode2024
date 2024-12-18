#ifndef CORD
#define CORD
#include <functional>
#include <stdlib.h>
class Cord {
public:
  int x;
  int y;
  Cord() {}
  Cord(int x, int y) {
    this->x = x;
    this->y = y;
  }

  bool operator==(const Cord &otherCord) const {
    if (this->x == otherCord.x && this->y == otherCord.y)
      return true;
    else
      return false;
  }

  struct HashFunction {
    size_t operator()(const Cord &cord) const {
      size_t xHash = std::hash<int>()(cord.x);
      size_t yHash = std::hash<int>()(cord.y) << 1;
      return xHash ^ yHash;
    }
  };
};
#endif
