#include "Grid.h"
class PathFinder {
private:
  Queue myQueue;
  Stack myStack;
  int backtrack_at;
  
public:
  bool target_found;
  PathFinder();
  void UpdateBFS(Grid &grid);
  void UpdateDFS(Grid &grid);
  void FindShortestPath(Grid &grid);
};
