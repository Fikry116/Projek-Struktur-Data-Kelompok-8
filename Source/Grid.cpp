#include "Grid.h"

/**
 * @brief Setup member grid (Grid Constructor).
 *
 * Di sini inisialisasi papan grid berdasarkan ukuran layar.
 * 
 * Logic-nya:
 * - Hitung berapa banyak kotak yang muat di layar (berdasarkan width/height).
 * 
 * - Siapin memori (resize vector) buat nampung status tiap kotak.
 * 
 * - Tandain posisi Start (Awal) dan End (Target) biar algoritma tau tujuannya.
 * 
 * - Panggil InitGrid() buat nyambungin jalan antar kotak (daftar tetangga).
 *
 * @param start Index posisi awal (titik mulai).
 * @param end Index posisi target (tujuan akhir).
 * @param width Lebar layar window (pixel).
 * @param height Tinggi layar window (pixel).
 * 
 */
Grid::Grid(int start,int end, unsigned int width, unsigned int height) 
  : start_cell(start), end_cell(end), window_width(width), window_height(height) {
  //inisialisasi ukuran grid (kotak)
  size_grid= 40.f;

  //hitung kolom berdasarkan lebar window/ukuran grid
  collumn = width / size_grid;
  
  //inisialisasi banyak baris berdasarkan tinggi window/ukuran grid
  row = height / size_grid;
  
  //total grid adalah kolom * baris
  total_grid = collumn * row;

  //inisialisasi seluruh grid dengan status grid sebagai idle (nganggur), dan ubah ukuran sebanyak total sel
  cell_state.resize(total_grid, CellState::Idle);

  //menyesuaikan ukuran menjadi total grid
  neighbors.resize(total_grid);

  //inisialisasi status pada indeks start cell adalah Start
  cell_state[start_cell] = CellState::Start;

  //inisialisasi status pada indeks end cell adalah End
  cell_state[end_cell] = CellState::End;

  //memanggil prosedur InitGrid() untuk menginisialisasi neighbors beserta tetangganya
  InitGrid();
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
  return size_grid;
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
  return total_grid;
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

//Inisialisasi grid ke-i beserta memetakan tetangga yang ada di sampingnya (atas/kiri/bawah/kanan) bila ada.
void Grid::InitGrid() {
  for(int i = 0; i < total_grid; i++) {
    if (i - collumn >= 0) neighbors[i].push_back(i - collumn);      // atas
    if (i % collumn != 0) neighbors[i].push_back(i - 1);         // kiri
    if (i + collumn < total_grid) neighbors[i].push_back(i + collumn); // bawah
    if ((i + 1) % collumn != 0) neighbors[i].push_back(i + 1);  //kanan
  }
}

void Grid::ResetState() {
  for(int i = 0 ; i < total_grid; i++) {
    cell_state[i] = CellState::Idle;
  }
  cell_state[start_cell] = CellState::Start;
  cell_state[end_cell] = CellState::End;
  parent.Clear();
}