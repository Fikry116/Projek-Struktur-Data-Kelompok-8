#include "PathFinder.h"

PathFinder::PathFinder(Grid &grid) : backtrack_at(grid.GetEndCell()) {
    target_found = false;
}

/**
 * @brief Jalanin satu langkah algoritma BFS (Breadth First Search).
 * BFS konsepnya mencari tempat dengan mencatat setiap persimpangan jalan, lalu pergi ke persimpangan jalan yang ada di catatan (queue),
 * baru dia pergi ke persimpangan jalan yang ada di catatan (queue).
 * 
 * Alur algoritma-nya:
 * 
 * 1. Cek queue (antrian). Kalau kosong, mulai dari Start Node.
 * 
 * 2. Ambil node paling awal dari antrian (Current Node).
 * 
 * 3. Tandain node itu sebagai "Visited" kalau tempat itu (sel) sudah dikunjungi.
 * 
 * 4. Kalau ketemu Target (End Cell), update selesai.
 * 
 * 5. Kalau belum, cari tetangga yang masih "Idle" (belum dikunjungi), masukin ke queue.
 * 
 * * @param grid Referensi ke object Grid 
 * 
 * @details Misal node awal 25 memiliki tetangga {15, 24, 35, 26} maka Enqueue ke queue menjadi {15, 24, 35, 26}
 * @details Langkah 1: Ambil queue pertama yaitu 15
 * @details Langkah 2: lalu Dequeu(), queue menjadi {24, 35, 26}.
 * @details Langkah 3: Masukkan tetangganya 15 yang belum dikunjungi {5, 14, 16}, maka queue menjadi {24, 35, 26, 5, 14, 16}
 * @details Langkah 4: node 15 berubah status menjadi visited (telah dikunjungi)
 * @details dan loop terus menerus sampai mengunjungi node akhir.
 * 
 */
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

/**
 * @brief Jalanin satu langkah algoritma DFS (Depth First Search).
 * DFS konsepnya seperti mencari tempat dari dari ujung jalan ke ujung jalan sampai ketemu tempat yang dicari,
 * baru dia mau balik arah (backtracking).
 * 
 * Alur algoritma nya:
 * 
 * 1. Cek stack (tumpukan). Kalau kosong, mulai dari Start Node.
 * 
 * 2. Ambil node paling atas dari tumpukan (Current Node).
 * 
 * 3. Tandain node itu sebagai "Visited" kalau tempat itu (sel) sudah dikunjungi.
 * 
 * 4. Kalau ketemu Target (End Cell), update selesai.
 * 
 * 5. Kalau belum, cari tetangga yang masih "Idle" (belum dikunjungi), masukin ke tumpukan buat diproses next step.
 * * @param grid Referensi ke object Grid (Peta/Map permainan kita).
 * Kita butuh ini buat tau tetangganya siapa aja dan update warnanya.
 * 
 * @details Misal node awal 25 memiliki tetangga {15, 24, 35, 26} maka Push ke stack menjadi {26, 35, 24, 15}
 * @details Langkah 1: Ambil stack (tumpukkan) pertama yaitu 26
 * @details Langkah 2: lalu Pop() menjadi {35, 24, 15}.
 * @details Langkah 3: Masukkan tetangganya 15 yang belum dikunjungi yaitu {5, 14, 16}, maka stack menjadi {16, 14, 5, 35, 24, 15}
 * @details Langkah 4: node 15 berubah status menjadi visited (telah dikunjungi)
 * @details dan loop terus menerus sampai mengunjungi node akhir.
 * 
 */
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

/**
 * @brief Jalanain satu kali langkah untuk mencari jalur (DFS/BFS)
 * 
 * Recall: pada struktur tree ini menggunakan konsep mapping dengan key dan value,
 * dimana key adalah yang node dari sebuah value, sedangkan value adalah parent dari key, dengan value harus bersifat unik.
 * 
 * Dengan konsep backtracking alias seperti jalan mundur, dengan base case ketika backtrack_at = -1
 * 
 * Alur Logic:
 * 
 * 1. Periksa apakah backtrack_at != -1, jika ya lanjut langkah 2, 3, 4, jika tidak maka jalur sudah ditemukan
 * 
 * 2. Masukkan data backtrack_at ke vector path.
 * 
 * 3. Pencarian value (parent) dari backtrack_at yang dimasukkan ke backtrack_at
 * 
 * 4. Periksa apakah nilai backtrack_at yang baru != -1 dan sel awal, jika ya maka ubah status sel pada indeks
 *    backtrack_at sebagai Path (jalur)
 * 
 * @param grid referensi ke data grid
 */
void PathFinder::FindShortestPath(Grid &grid) {
    if(backtrack_at != -1) {
        grid.path.push_back(backtrack_at); //search value dengan key 
        backtrack_at = grid.parent.Search(backtrack_at);
        if(backtrack_at != -1 && backtrack_at != grid.GetStartCell()) {
            grid.cell_state[backtrack_at] = CellState::Path;
        }
    }
}