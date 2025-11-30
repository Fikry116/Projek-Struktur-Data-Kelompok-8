#pragma once
#include "Grid.h"

class GridRenderer {
private:
  sf::RectangleShape cell_shape;
  float cell_size;
public:

  GridRenderer(float size);

  void DrawGrid(sf::RenderWindow &window, Grid &grid);

  void BrushTool(sf::RenderWindow &window, CellModifier brush, sf::Vector2i mouse_pos, Grid &grid);

  int GetIndex(int x, int y, Grid &grid);
};