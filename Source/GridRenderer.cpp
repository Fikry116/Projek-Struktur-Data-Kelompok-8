#include "GridRenderer.h"

GridRenderer::GridRenderer(float size) :cell_size(size) {
  cell_shape.setSize(sf::Vector2f({cell_size-1.f, cell_size-1.f}));
}

void GridRenderer::DrawGrid(sf::RenderWindow &window, Grid &grid) { //sementara percobaan grid awal (belum BFS/DFS)
    for(unsigned int i = 0; i < grid.GetTotalGrid(); i++) {
      
      CellState state = grid.cell_state[i];
      sf::Color color;
      if(state == CellState::Idle) {
        color = sf::Color(20, 20, 20);
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
      
      float posX = (i % grid.GetCollumn()) * grid.GetGridSize();
      float posY = (i / grid.GetCollumn()) * grid.GetGridSize();
      cell_shape.setPosition({posX, posY});
        
      cell_shape.setFillColor({color});
      cell_shape.setOutlineThickness(-1.f);
      cell_shape.setOutlineColor(sf::Color::Black);
        
      window.draw(cell_shape);
    }
}

int GridRenderer::GetIndex(int x, int y, Grid &grid) {
    if (x < 0 || x >= grid.GetCollumn() || y < 0 || y >= grid.GetRow()) return -1;
    return y * grid.GetCollumn() + x;
}

void GridRenderer::BrushTool(sf::RenderWindow &window, CellModifier brush, sf::Vector2i mouse_pos, Grid &grid) {
  int index = GetIndex(mouse_pos.x/grid.GetGridSize(), mouse_pos.y/grid.GetGridSize(), grid);

  if(index == -1) return;

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