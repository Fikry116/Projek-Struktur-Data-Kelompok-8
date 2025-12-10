#include "Grid.h"
class PathFinder {
private:
  Queue BFS_Queue;
  Stack DFS_Stack;
  int backtrack_at;
  bool target_found;
  
public:
  PathFinder(Grid &grid);
  bool IsTargetFound();
  void Reset();
  void UpdateBFS(Grid &grid);
  void UpdateDFS(Grid &grid);
  void FindPath(Grid &grid);
};