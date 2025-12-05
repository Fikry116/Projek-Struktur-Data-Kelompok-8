#include "PathFinder.h"

PathFinder::PathFinder() {target_found = false;}

void PathFinder::UpdateBFS(Grid &grid) {
    if(myQueue.IsEmpty()) {
        grid.parent.Insert(grid.GetStartCell(), -1);
        myQueue.Enqueue(grid.GetStartCell());
    }
    
    if(target_found){
        return;
    }
    int current_node = myQueue.Front();

    
    if(current_node != grid.GetStartCell() && current_node != grid.GetEndCell()) {
        grid.cell_state[current_node] = CellState::Visited;
    }

    std::cout << current_node << " " << grid.GetEndCell() << " " << grid.GetStartCell() << "\n";

    if(current_node == grid.GetEndCell()) {
        target_found = true;
        backtrack_at = grid.GetEndCell();
        std::cout << "Found\n";
        return;
    }
    myQueue.Dequeue();
    
    for(int neighbor : grid.adjacent[current_node]) {
        if(grid.cell_state[neighbor] == CellState::Idle || neighbor == grid.GetEndCell()) {
            if(grid.cell_state[neighbor] != CellState::End) {
                grid.cell_state[neighbor] = CellState::InQueue;
            }
            grid.parent.Insert(neighbor, current_node);
            myQueue.Enqueue(neighbor);
        }
    }
}

void PathFinder::UpdateDFS(Grid &grid) {
    if(myStack.IsEmpty()) {
        //init
    }

    int current_node = myQueue.Front();

    if(current_node != grid.GetStartCell() && current_node != grid.GetEndCell())
      grid.cell_state[current_node] = CellState::Visited;

    if(current_node = grid.GetEndCell()) {
        backtrack_at = grid.GetEndCell();
        target_found = true;
        return;
    }
    myQueue.Dequeue();

    for(int neighbor : grid.adjacent[current_node]) {
        if(grid.cell_state[neighbor] == CellState::Idle) {
            grid.cell_state[neighbor] = CellState::InQueue;
            grid.parent.Insert(neighbor, current_node);
            myQueue.Enqueue(neighbor);
        }
    }
}

void PathFinder::FindShortestPath(Grid &grid) {
    std::cout << backtrack_at << "\n";
    if(backtrack_at != -1) {
        std::cout << backtrack_at << "\n";
        grid.path.push_back(backtrack_at);
        backtrack_at = grid.parent.Search(backtrack_at);
        if(backtrack_at != -1 && backtrack_at != grid.GetStartCell())
            grid.cell_state[backtrack_at] = CellState::Path;
    }
}