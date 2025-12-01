#include "Grid.h"

Grid::Grid(int start,int end, unsigned int width, unsigned int height) 
  : start_cell(start), end_cell(end), window_width(width), window_height(height) {
    SIZE_GRID = 40.f;
    collumn = width / SIZE_GRID;
    row = height / SIZE_GRID;
    TOTAL_GRID = collumn * row;
    cell_state.resize(TOTAL_GRID, CellState::Idle);
    adjacent.resize(TOTAL_GRID);
    cell_state[start_cell] = CellState::Start;
    cell_state[end_cell] = CellState::End;
}
/**
 * Getter kolom
 * @return Jumlah kolom
 */
int Grid::GetCollumn() {
    return collumn;
}

/**
 * Getter baris
 * @return jumlah baris
 */
int Grid::GetRow() {
    return row;
}

/**
 * Getter ukuran sel
 * @return ukuran sel (float)
 */
float Grid::GetGridSize() {
    return SIZE_GRID;
}

/**
 * Getter indeks sel awal
 * @return indeks sel awal
 */
int Grid::GetStartCell() {
    return start_cell;
}

/**
 * Getter indeks sel akhir
 * @return indeks sel akhir
 */
int Grid::GetEndCell() {
    return end_cell;
}

/**
 * Getter total sel
 * @return banyaknya sel dalam grid
 */
int Grid::GetTotalGrid() {
    return TOTAL_GRID;
}

/**
 * Setter indeks untuk sel akhir
 * @param index indeks untuk sel akhir 
 */
void Grid::SetEndCell(int index) {
    end_cell = index;
}

/**
 * Setter indeks untuk sel awal
 * @param index indeks untuk sel awal
 */
void Grid::SetStartCell(int index) {
    start_cell = index;
}

// void Grid::