#pragma once
//struct grid buat BFS sama DFS
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector> 
#include "Tree.h"
#include "Stack.h"
#include "Queue.h"

enum class CellState {
    Idle,
    InQueue,
    InStack,
    Visited,
    Path,
    Wall,
    Start,
    End
 };

enum class CellModifier {
    WallBrush,
    SetStart,
    SetEnd,
    Erase
};

class Grid {
private:
  int collumn;
  int row;
  int TOTAL_GRID;
  float SIZE_GRID;
  int start_cell;
  int end_cell;
  unsigned int window_width;
  unsigned int window_height;
    
  
public:
  std::vector<std::vector<int>> adjacent;
  std::vector<CellState> cell_state;
  std::vector<int> path;
  Tree parent;

  Grid(int start,int end, unsigned int width, unsigned int height);

  int GetCollumn();
  int GetRow();
  int GetTotalGrid();
  float GetGridSize();
  int GetStartCell();
  int GetEndCell();
  void SetEndCell(int index);
  void SetStartCell(int index);
  void ResetState();
  void InitGrid();
  // void SetCollumn(int width, int height);
    //Stack myStack
    //Queue myQueue
};