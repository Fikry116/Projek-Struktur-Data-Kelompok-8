#pragma once
//struct grid buat BFS sama DFS
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector> 
#include "Tree.h"
#include "Stack.h"
#include "Queue.h"

// Status untuk sel-sel pada setiap indeks
enum class CellState {
    Idle,     ///< Status sel nganggur
    InQueue,  ///< Status sel berada di dalam antrian  
    InStack,  ///< Status sel berada di dalam tumpukkan
    Visited,  ///< Status sel sudah dikunjungi
    Path,     ///< Status sel untuk jalur
    Wall,     ///< Status sel untuk tembok
    Start,    ///< Status sel untuk titik awal
    End       ///< Status sel untuk titik akhir
 };

/**
 * @brief Mode kuas untuk mengatur tembok, set awal, set akhir, dan hapus tembok
 */
enum class CellModifier {
    WallBrush,  ///< Mode untuk mengecat tembok
    SetStart,   ///< Mode untuk mengatur titik awal
    SetEnd,     ///< Mode untuk mengatur titik akhir
    Erase       ///< Mode untuk menghapus tembok
};

class Grid {
private:
  int collumn;
  int row;
  int total_grid;
  float size_grid;
  int start_cell;
  int end_cell;
  unsigned int window_width;
  unsigned int window_height;
    
  
public:
  std::vector<std::vector<int>> neighbors;
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
};