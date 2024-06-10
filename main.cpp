//
// Created by bianca on 09/06/24.
//
#include <iostream>
#include "AVL.h"
using namespace std;

int main() {
    auto* tree = new AVL<int>();
    tree->insert(10);
    tree->insert(20);
    tree->insert(30);
    tree->insert(40);
    tree->insert(50);
    tree->insert(25);
    tree->preorder();
    tree->erase(40);
    tree->preorder();
    cout << boolalpha << tree->isBalanced() << endl;
    return 0;
}