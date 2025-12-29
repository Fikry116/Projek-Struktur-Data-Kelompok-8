#pragma once
#include "Grid.h"
#include <vector>
#include <cstdlib> // Buat rand()
#include <ctime>   // Buat seed random

class MazeGenerator {
private:
    Grid* grid;
    std::vector<int> frontier;

    bool isValid(int x, int y);
    int GetIndex(int x, int y);
    void PushFrontier(int x, int y);
    void ConnectCell(int x, int y);
    
public:
    
    MazeGenerator(Grid *target_grid);

    bool Generate();
    void Reset();
    void ResetMaze();


};