//struct grid buat BFS sama DFS
#include <iostream>
#include <queue>
#include <stack>
#include <SFML/Graphics.hpp>
#include <vector> 

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
    SetEnd
};

struct Grid {
  int collumn;
  int row;
  int TOTAL_GRID;
  float SIZE_GRID;
  int start_grid;
  int end_grid;
  unsigned int window_width;
  unsigned int window_height;
    
  std::vector<std::vector<int>> myGrid;
  std::vector<CellState> grid_state;
  std::vector<int> path;
    
  sf::RectangleShape drawable_grid;
    
  Grid(int start,int end, unsigned int width, unsigned int height) 
    : start_grid(start), end_grid(end), window_width(width), window_height(height) {
      SIZE_GRID = 40.f;
      collumn = width / SIZE_GRID;
      row = height / SIZE_GRID;
      TOTAL_GRID = collumn * row;
      grid_state.resize(TOTAL_GRID, CellState::Idle);

      drawable_grid.setSize(sf::Vector2f({SIZE_GRID-1.f, SIZE_GRID-1.f}));
      myGrid.resize(TOTAL_GRID);

  }

  void DrawGrid(sf::RenderWindow &window) {
    for(unsigned int i = 0; i < TOTAL_GRID; i++) {
      
      CellState state = grid_state[i];
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
      
      float posX = (i % collumn) * SIZE_GRID;
      float posY = (i / collumn) * SIZE_GRID;
      drawable_grid.setPosition({posX, posY});
        
      drawable_grid.setFillColor({color});
      drawable_grid.setOutlineThickness(-1.f);
      drawable_grid.setOutlineColor(sf::Color::Black);
        
      window.draw(drawable_grid);
    }
  }

  int GetIndex(int x, int y) {
    if (x < 0 || x >= collumn || y < 0 || y >= row) return -1;
    return y * collumn + x;
  }

  void BrushTool(sf::RenderWindow &window, CellModifier brush, sf::Vector2i mouse_pos) {
      sf::Vector2f mouse_pos_f(static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y));
      int index = GetIndex(mouse_pos.x/SIZE_GRID, mouse_pos.y/SIZE_GRID);

      if(index == -1) return;

      switch (brush) {
        case CellModifier::WallBrush:
          if(grid_state[index] == CellState::End || grid_state[index] == CellState::Start) return;

          grid_state[index] = CellState::Wall;
          break;
        case CellModifier::SetStart:
          if(index == start_grid) return;

          grid_state[index] = CellState::Start;
          grid_state[start_grid] = CellState::Idle;
          start_grid = index;
          break;
        case CellModifier::SetEnd:
          if(index == end_grid) return;

          grid_state[index] = CellState::End;
          grid_state[end_grid] = CellState::Idle;
          end_grid = index;    
          break;  
      default:
          break;
      }
  }


    //Stack myStack
    //Queue myQueue
};