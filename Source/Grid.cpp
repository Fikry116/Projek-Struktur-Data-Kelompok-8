#include "Grid.h"

Grid::Grid(int start,int end, unsigned int width, unsigned int height) 
  : start_cell(start), end_cell(end), window_width(width), window_height(height) {
    SIZE_GRID = 20.f;
    collumn = width / SIZE_GRID;
    row = height / SIZE_GRID;
    TOTAL_GRID = collumn * row;
    cell_state.resize(TOTAL_GRID, CellState::Idle);
    adjacent.resize(TOTAL_GRID);
    cell_state[start_cell] = CellState::Start;
    cell_state[end_cell] = CellState::End;
}

int Grid::GetCollumn() {
    return collumn;
}

int Grid::GetRow() {
    return row;
}

int Grid::GetGridSize() {
    return SIZE_GRID;
}

int Grid::GetStartCell() {
    return start_cell;
}

int Grid::GetEndCell() {
    return end_cell;
}

int Grid::GetTotalGrid() {
    return TOTAL_GRID;
}

void Grid::SetEndCell(int index) {
    end_cell = index;
}

void Grid::SetStartCell(int index) {
    start_cell = index;
}