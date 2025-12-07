#include "Tree.h"

TreeNode::TreeNode(int key, int value, TreeNode *prnt, TreeNode *l, TreeNode *r) 
  : Key(key), Value(value), parent(prnt), left(l), right(r) {}

//Konstruktor Tree dengan metode Binary Search Tree yang menggunakan konsep
//mapping key dan value, dengan inisialisasi akarnya null
  Tree::Tree() : root(nullptr) {}

//Destruktor Tree, untuk menghapus nodes yang ada di Tree
Tree::~Tree() {Clear();}

/**
 * @brief Fungi pembungkus untuk memasukkan data ke dalam tree
 * 
 * @param key sebagai angka kunci untuk sebuah nilai pada node
 * @param value adalah nilai yang yang ada pada key 
 */
void Tree::Insert(int key, int val) {
    root = InsertRecursive(root, key, val);
}

/**
 * @brief Fungsi insert dengan cara rekursif. Rekursif ini akan bergerak ke kiri dan ke kanan
 * dengan cara membandingkan key yang akan di masukkan dengan key yang ada di dalam node. 
 * Sehingga node ini akan tersortir secara otomatis berdasarkan key 
 */
TreeNode *Tree::InsertRecursive(TreeNode *node, int key, int value) {
    if(node == nullptr) { //basis
        node = new TreeNode(key, value, nullptr, nullptr, nullptr);
        return node;
    } 
    if(key < node->Key) {
        node->left = InsertRecursive(node->left, key, value);
    } else {
        node->right = InsertRecursive(node->right, key, value);
    }
    return node;
}

/**
 * @brief Fungsi search adalah fungsi yang mencari value beradasrkan input key nya.
 * Fungsi ini berguna untuk mencari jalur setelah dilakukan BFS/DFS. Karena dengan konsep
 * Binary Search Tree yang sudah tersortir, fungsi ini akan bergerak ke kiri atau kanan dengan
 * membandingkan key parameter dengan key node
 * 
 * @param key adalah angka yang akan dicari.
 * @return value dari key di dalam node Tree
 */
int Tree::Search(int key) {
    TreeNode *current = root;
    while (current) {
        if (key == current->Key) {
            return current->Value;
        } else if (key < current->Key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return -1;
}

/**
 * @brief Fungsi ini untuk menghapus keseluruhan node dengan rekursif.
 * @param node node yang akan dihapus, dimulai dari root 
 */
void Tree::DestroyRecursive(TreeNode *node) {
    if(node) {
        DestroyRecursive(node->left);
        DestroyRecursive(node->right);
        delete node;
    }
}

//Fungsi ini untuk menghapus seluruh node dengan memanggil fungsi DestroyRecursive()
//dan membuat root menjadi nullptr, karena node sudah dihapus semua. 
void Tree::Clear() {
    DestroyRecursive(root);
    root = nullptr;
}