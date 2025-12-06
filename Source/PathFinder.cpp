#include "PathFinder.h"

PathFinder::PathFinder(Grid &grid) : backtrack_at(grid.GetEndCell()) {
    target_found = false;
}

void PathFinder::UpdateBFS(Grid &grid) {
    if(myQueue.IsEmpty()) {
        grid.parent.Insert(grid.GetStartCell(), -1);
        myQueue.Enqueue(grid.GetStartCell());
    }
    
    if(target_found){
        return;
    }
    int current_node = myQueue.Front();

    //sel berubah status menjadi Visited setelah dilakukan Queue
    if(current_node != grid.GetStartCell() && current_node != grid.GetEndCell()) {
        grid.cell_state[current_node] = CellState::Visited;
    }

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
        grid.parent.Insert(grid.GetStartCell(), -1);
        myStack.Push(grid.GetStartCell());
    }

    int current_node = myStack.Top();

    if(current_node != grid.GetStartCell() && current_node != grid.GetEndCell())
      grid.cell_state[current_node] = CellState::Visited;

    if(current_node == grid.GetEndCell()) {
        target_found = true;
        return;
    }

    myStack.Pop();

    for(int neighbor : grid.adjacent[current_node]) {
        if(grid.cell_state[neighbor] == CellState::Idle || neighbor == grid.GetEndCell()) {
            if(grid.cell_state[neighbor] != CellState::End) {
                grid.cell_state[neighbor] = CellState::InStack;
            }
            grid.parent.Insert(neighbor, current_node);
            myStack.Push(neighbor);
        }
    }
}

void PathFinder::FindShortestPath(Grid &grid) {
    if(backtrack_at != -1) {
        grid.path.push_back(backtrack_at); //search value dengan key 
        backtrack_at = grid.parent.Search(backtrack_at);
        if(backtrack_at != -1 && backtrack_at != grid.GetStartCell()) {
            grid.cell_state[backtrack_at] = CellState::Path;
        }
    }
}