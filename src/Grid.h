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

        sf::RectangleShape(sf::Vector2f({SIZE_GRID-1.f, SIZE_GRID-1.f}));
        myGrid.resize(TOTAL_GRID);

    }

    void DrawGrid(sf::RenderWindow &window) {
        for(unsigned int i = 0; i < TOTAL_GRID; i++) {
            float posX = (i % collumn) * SIZE_GRID;
            float posY = (i / collumn) * SIZE_GRID;
            std::cout << posX << " " << posY << "\n";
            drawable_grid.setPosition({posX, posY});
            drawable_grid.setFillColor({sf::Color::White});
            drawable_grid.setOutlineColor(sf::Color::Black);
            drawable_grid.setOutlineThickness(-1.f);

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