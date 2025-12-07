#include "GridRenderer.h"
#include <algorithm>
#include <random>

//Konstruktor untuk GridRender yang menginisialisasi ukuran dari sell
GridRenderer::GridRenderer(float size) :cell_size(size) {
  cell_shape.setSize(sf::Vector2f({cell_size-1.f, cell_size-1.f}));
}

/**
 * @brief Merender seluruh grid dan status selnya ke layar (Render Loop).
 * 
 * Fungsi ini mengiterasi seluruh sel dalam grid, menentukan warna berdasarkan 
 * status sel (CellState), dan menggambarnya pada posisi yang sesuai.
 * 
 * @param window Referensi ke sf::RenderWindow sebagai target rendering.
 * @param grid   Referensi objek Grid yang menyimpan data status sel (State Data).
 * 
 */
void GridRenderer::DrawGrid(sf::RenderWindow &window, Grid &grid) {
  for(unsigned int i = 0; i < grid.GetTotalGrid(); i++) {
    
    CellState state = grid.cell_state[i];
    sf::Color color;
    if(state == CellState::Idle) {
      color = sf::Color(68, 71, 90);
    } else if (state == CellState::Wall) {
      color = sf::Color(100, 116, 139);
    } else if (state == CellState::InQueue || state == CellState::InStack) {
      color = sf::Color(171, 224, 240);
    } else if (state == CellState::Visited) {
      color = sf::Color(6, 182, 212);
    } else if (state == CellState::Path) {
      color = sf::Color(250, 204, 21);
    } else if (state == CellState::Start) {
      color = sf::Color(34, 197, 94);
    } else if (state == CellState::End) {
      color = sf::Color(239, 68, 68);
    }
    
    float posX = (i % grid.GetCollumn()) * grid.GetGridSize(); // bernilai {0, 40, 80, ..., width - ukuran sel}
    float posY = (i / grid.GetCollumn()) * grid.GetGridSize(); // bernilai {0, 40, 80, ..., height - ukuran sel}
    cell_shape.setPosition({posX, posY});
    
    cell_shape.setFillColor({color});
    cell_shape.setOutlineThickness(-1.f);
    cell_shape.setOutlineColor(sf::Color::Black);
      
    window.draw(cell_shape);
  }
}

/**
 * @brief Mengkonversi koordinat Grid 2D (kolom, baris) menjadi indeks array 1D (Linear).
 * * Fungsi ini melakukan pengecekan batas (bounds checking) terlebih dahulu.
 * * @param x Indeks kolom pada grid.
 * @param y Indeks baris pada grid.
 * @param grid Referensi objek Grid untuk mendapatkan dimensi (jumlah baris & kolom).
 * @return int Indeks array linear jika valid, atau -1 jika koordinat berada di luar batas grid.
 */
int GridRenderer::GetIndex(int x, int y, Grid &grid) {
  if (x < 0 || x >= grid.GetCollumn() || y < 0 || y >= grid.GetRow()) return -1; //mencegah saat klik di luar koordinat grid berdasarkan indeks
  std::cout << x << " " << y << "\n";
  return y * grid.GetCollumn() + x;
}

/**
 * @brief Memodifikasi status sel pada grid (menggambar tembok, set start/end) berdasarkan input mouse.
 * Fungsi ini mengkonversi posisi mouse menjadi indeks grid dan mengubah
 * status sel (CellState) sesuai dengan mode kuas 'brush' yang dipilih.
 * @param window Referensi ke sf::RenderWindow (konteks rendering saat ini).
 * @param brush  Enum CellModifier yang menentukan mode "lukis" (misal: Wall, Start, End, Erase).
 * @param mouse_pos Koordinat posisi kursor mouse relatif terhadap window (Screen Coordinates).
 * @param grid   Referensi ke objek Grid yang akan dimodifikasi status selnya.
 * 
 * @note Fungsi ini memiliki validasi untuk mencegah penimpaan titik Start/End secara tidak sengaja.
 */
void GridRenderer::BrushTool(sf::RenderWindow &window, CellModifier brush, sf::Vector2i mouse_pos, Grid &grid) {
  int index = GetIndex(mouse_pos.x/grid.GetGridSize(), mouse_pos.y/grid.GetGridSize(), grid);
  std::cout << index << "\n";

  if(index == -1) return; //mencegah saat klik di luar koordinat grid berdasarkan indeks

  switch (brush) {
    case CellModifier::WallBrush:
      if(grid.cell_state[index] == CellState::End || grid.cell_state[index] == CellState::Start) return;

      grid.cell_state[index] = CellState::Wall;
      break;
    case CellModifier::SetStart:
      if(index == grid.GetStartCell()) return;

      grid.cell_state[index] = CellState::Start;
      grid.cell_state[grid.GetStartCell()] = CellState::Idle;
      grid.SetStartCell(index);
      break;
    case CellModifier::SetEnd:
      if(index == grid.GetEndCell()) return;

      grid.cell_state[index] = CellState::End;
      grid.cell_state[grid.GetEndCell()] = CellState::Idle;
      grid.SetEndCell(index);
      break;
    case CellModifier::Erase:
      if(grid.cell_state[index] == CellState::End || grid.cell_state[index] == CellState::Start) return;
      grid.cell_state[index] = CellState::Idle;
    default:
      break;
      }      
}
