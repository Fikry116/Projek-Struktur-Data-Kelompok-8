#include "MazeGenerator.h"
#include <algorithm>

MazeGenerator::MazeGenerator(Grid *target_grid) : grid(target_grid) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}


bool MazeGenerator::Generate() {
    if(frontier.empty()) return false;

    int randIndex = rand() % frontier.size();
    int currentIndex = frontier[randIndex];
    frontier.erase(frontier.begin() + randIndex);

    int x = currentIndex % grid->GetCollumn();
    int y = currentIndex / grid->GetCollumn();
    
    if (grid->cell_state[currentIndex] == CellState::Wall) {
        ConnectCell(x, y); 
        
        PushFrontier(x, y);
    }
    
    return true;
}

void MazeGenerator::Reset() {
    int index_x = rand() % grid->GetCollumn();
    int index_y = rand() % grid->GetRow();
    frontier.clear();
    int index_1d = GetIndex(index_x, index_y);
    grid->cell_state[index_1d] = CellState::Idle;

    PushFrontier(index_x, index_y);
}

void MazeGenerator::PushFrontier(int current_x, int current_y) {
    int direction[4][2] = {{0, -2}, //top
                           {0, 2}, // bot
                           {-2, 0}, //left
                           {2, 0}};  //right

    for (int i = 0; i < 4; i++) {
        int new_x = current_x + direction[i][0];
        int new_y = current_y + direction[i][1];

        if(isValid(new_x, new_y)) {
            int idx = GetIndex(new_x, new_y);

            if(grid->cell_state[idx] == CellState::Wall) {
                bool exists = false;
                for(int f : frontier) if (f == idx) exists = true;

                if(!exists) frontier.push_back(idx);
            }
        }
    }
}

void MazeGenerator::ConnectCell(int current_x, int current_y) {
    int dirs[4][2] = {{0, -2}, {0, 2}, {-2, 0}, {2, 0}};
    
    std::vector<int> potential_connectors;

    for(int i=0; i<4; i++) {
        int new_x = current_x + dirs[i][0];
        int new_y = current_y + dirs[i][1];

        if(isValid(new_x, new_y)) {
            int nIdx = GetIndex(new_x, new_y);
            
            if(grid->cell_state[nIdx] == CellState::Idle) {
                potential_connectors.push_back(i); 
            }
        }
    }

    if(!potential_connectors.empty()) {
        int random_dir_index = potential_connectors[rand() % potential_connectors.size()];
        
        int dx = dirs[random_dir_index][0];
        int dy = dirs[random_dir_index][1];

        int wall_x = current_x + (dx / 2);
        int wall_y = current_y + (dy / 2);
        int wall_idx = GetIndex(wall_x, wall_y);
        
        grid->cell_state[wall_idx] = CellState::Idle;
        
        int current_idx = GetIndex(current_x, current_y);
        grid->cell_state[current_idx] = CellState::Idle; 
    }
}

bool MazeGenerator::isValid(int x, int y) {
    return x >= 0 && x < grid->GetCollumn() && y >= 0 && y < grid->GetRow();
}

int MazeGenerator::GetIndex(int x, int y) {
    if(isValid(x, y)) {
        return y * grid->GetCollumn() + x;
    }
    return -1;
}

void MazeGenerator::ResetMaze() {
    for(int i = 0; i < grid->GetTotalGrid(); i++) {
        if (grid->cell_state[i] == CellState::Path ||
            grid->cell_state[i] == CellState::InQueue ||
            grid->cell_state[i] == CellState::InStack ||
            grid->cell_state[i] == CellState::Visited) {
                grid->cell_state[i] = CellState::Idle;
            }
    }
    
}