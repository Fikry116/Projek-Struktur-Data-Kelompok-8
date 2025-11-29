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
    Wall
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
            color = sf::Color(0, 255, 156);
          }
          
          float posX = (i % collumn) * SIZE_GRID;
          float posY = (i / collumn) * SIZE_GRID;
          std::cout << posX << " " << posY << "\n";
          drawable_grid.setPosition({posX, posY});
            
          drawable_grid.setFillColor({color});
          drawable_grid.setOutlineThickness(-1.f);
          drawable_grid.setOutlineColor(sf::Color::Black);
            
          window.draw(drawable_grid);
        }
    }

    void BrushTool(sf::RenderWindow &window, CellModifier brush, sf::Vector2i mouse_pos) {
        sf::Vector2f mouse_pos_f(static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y));
        switch (brush) {
          case CellModifier::WallBrush:
            
            break;
          case CellModifier::SetStart:
            break;
          case CellModifier::SetEnd:
            break;  
        default:
            break;
        }
    }


    //Stack myStack
    //Queue myQueue
};