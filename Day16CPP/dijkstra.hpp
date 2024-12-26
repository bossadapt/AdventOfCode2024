#ifndef DIJKSTRA
#define DIJKSTRA
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <queue>
#include <stdexcept>
#include <vector>
// i was suprised by how many  path finding problems, going to  make this and
// just spread it to my solutions
using namespace std;

class Dijkstra {
private:
  char wall;
  vector<string> grid;
  class CordNode {
  public:
    unsigned long x;
    unsigned long y;
    unsigned long path;
    unsigned long priority;
    // does not compute priority
    CordNode(unsigned long x, unsigned long y, unsigned long path) {
      this->x = x;
      this->y = y;
    }
    CordNode(unsigned long x, unsigned long y, unsigned long path,
             CordNode &endCord) {
      this->x = x;
      this->y = y;
      computePriority(endCord);
    }
    // making this work with priority queue
    bool operator==(const CordNode &otherCord) const {
      if (this->priority == otherCord.priority)
        return true;
      else
        return false;
    }
    bool operator>(const CordNode &otherCord) const {
      if (this->priority > otherCord.priority)
        return true;
      else
        return false;
    }
    bool operator>=(const CordNode &otherCord) const {
      if (this->priority >= otherCord.priority)
        return true;
      else
        return false;
    }
    bool operator<=(const CordNode &otherCord) const {
      if (this->priority <= otherCord.priority)
        return true;
      else
        return false;
    }
    bool operator<(const CordNode &otherCord) const {
      if (this->priority < otherCord.priority)
        return true;
      else
        return false;
    }
    void computePriority(const CordNode &endNode) {
      long long xDif = endNode.y - this->y;
      long long yDif = endNode.x - this->x;
      this->priority = abs(xDif) + abs(yDif) + path;
    }
    bool isSameCord(const CordNode &otherCord) {
      if (this->x == otherCord.x && this->y == otherCord.y) {
        return true;
      }
      return false;
    }
    // cord Nodes are not based on path length as well
    struct HashFunction {
      size_t operator()(const CordNode &cord) const {
        size_t xHash = std::hash<int>()(cord.x);
        size_t yHash = std::hash<int>()(cord.y) << 1;
        return xHash ^ yHash;
      }
    };
  };
  CordNode start = CordNode(0, 0, 0);
  CordNode end = CordNode(0, 0, 0);
  std::priority_queue<CordNode, std::vector<CordNode>, std::greater<CordNode>>
      pathPriorityQueue;

public:
  Dijkstra(char startChar, char endChar, char wallChar,
           vector<string> charGrid) {
    // turn start and end char to
    grid = charGrid;
    wall = wallChar;
    bool startFound = false;
    bool endFound = false;
    for (unsigned long y = 0; y < grid.size(); y++) {
      for (unsigned long x = 0; x < grid[y].size(); x++) {
        if (grid[y][x] == startChar) {
          if (startFound) {
            // you could remove this if you dont care, , mostly a block to stop
            // me from shooting me in the foot
            throw std::invalid_argument("multiple start chars found");
          } else {
            startFound = true;
            this->start.x = x;
            this->start.y = y;
          }
        }
        if (!endFound && grid[y][x] == endChar) {
          if (endFound) {
            // you could remove this if you dont care, mostly a block to stop me
            // from shooting me in the foot
            throw std::invalid_argument("multiple end chars found");
          } else {
            endFound = true;
            this->end.x = x;
            this->end.y = y;
          }
        }
      }
    }
    if (!startFound) {
      throw std::invalid_argument("start not found in grid");
    } else if (!endFound) {
      throw std::invalid_argument("start not found in grid");
    } else {
      start.computePriority(end);
    }
  }
  Dijkstra(unsigned long startX, unsigned long startY, unsigned long endX,
           unsigned long endY, char wallChar, vector<vector<char>> grid) {}
  ///-1 if cant fined path
  long long findPathLength() {
    bool notReached = true;
    pathPriorityQueue.push(start);
    while (notReached && !pathPriorityQueue.empty()) {
      CordNode current = pathPriorityQueue.top();
      // printf("checking:%lu, %lu", current.x, current.y);
      pathPriorityQueue.pop();
      if (current.isSameCord(end)) {
        return current.path;
      }
      // left
      if (current.x != 0 && grid[current.y][current.x - 1] != wall) {
        CordNode newCord =
            CordNode(current.x - 1, current.y, current.path + 1, end);
        pathPriorityQueue.push(newCord);
      }
      // top
      if (current.y != 0 && grid[current.y - 1][current.x] != wall) {
        CordNode newCord =
            CordNode(current.x, current.y - 1, current.path + 1, end);
        pathPriorityQueue.push(newCord);
      }
      // bottom
      if (current.y != grid.size() - 1 &&
          grid[current.y + 1][current.x] != wall) {
        CordNode newCord =
            CordNode(current.x, current.y + 1, current.path + 1, end);
        pathPriorityQueue.push(newCord);
      }
      // right
      if (current.x != grid[current.y].size() - 1 &&
          grid[current.y][current.x + 1] != wall) {
        CordNode newCord =
            CordNode(current.x + 1, current.y, current.path + 1, end);
        pathPriorityQueue.push(newCord);
      }
    }
    if (pathPriorityQueue.empty()) {
      return -1;
    }
  }
};

#endif