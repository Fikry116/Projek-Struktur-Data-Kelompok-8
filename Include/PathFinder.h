#include "Grid.h"
class PathFinder {
private:
  Queue myQueue;
  Stack myStack;
  int backtrack_at;
  
public:
  bool target_found;
  PathFinder(Grid &grid);
  void UpdateBFS(Grid &grid);
  void UpdateDFS(Grid &grid);
  void FindShortestPath(Grid &grid);
};
