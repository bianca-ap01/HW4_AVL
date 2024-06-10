//
// Created by bianca on 09/06/24.
//

#ifndef HW4_AVL_AVL_H
#define HW4_AVL_AVL_H

#include <iostream>
using namespace std;

template<typename T>
class AVL{
private:
    struct Node{
        Node* left;
        Node* right;
        T key;
        int height;
        Node():left(nullptr), right(nullptr), height(1){};
        explicit Node(T _key):left(nullptr), right(nullptr), key(_key), height(1){};
    };

    Node* root;
    int sz{};

    T max(T a, T b){
        return (a < b) ? b : a;
    }

    Node* leftRotate(Node* a){
        Node* b = a->right;
        Node* temp = b->left;
        b->left = a;
        a->right = temp;
        a->height = max(height(a->left), height(a->left))+1;
        b->height = max(height(b->left), height(b->left))+1;
        return b;
    }

    Node* rightRotate(Node* a){
        Node* b = a->left;
        Node* temp = b->right;
        b->right = a;
        a->left = temp;
        a->height = max(height(a->left), height(a->right))+1;
        b->height = max(height(b->left), height(b->right))+1;
        return b;
    }

    int balanceFactor(Node* node){
        if(!node) return 0;
        else return height(node->left) - height(node->right);
    }

    Node* balance(Node* node){
        if(balanceFactor(node) > 1){
            if(balanceFactor(node->left) < 0) node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if(balanceFactor(node) < -1){
            if(balanceFactor(node->right) > 0) node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* inorderSuccessor(Node* node){
        Node* temp = node;
        while(temp and temp->left) temp = temp->left;
        return temp;
    }

    Node* maxValueNode(Node* node){
        Node* temp = node;
        while(temp and temp->right) temp = temp->right;
        return temp;
    }

    bool isBalanced(Node* node){
        if(!node) return true;
        if(balanceFactor(node) < -1 or balanceFactor(node) > 1) return false;
        return isBalanced(node->left) and isBalanced(node->right);
    }

    Node* find(Node* node, T key){
        if(!node) return nullptr;
        if(key < node->key) return find(node->left, key);
        else if(key > node->key) return find(node->right, key);
        else return node;
    }

    Node* insert(Node* node, T key){
        if(!node) return new Node(key);
        if(key < node->key) node->left = insert(node->left, key);
        else if(key > node->key) node->right = insert(node->right, key);
        else return node;
        node->height = 1 + max(height(node->left), height(node->right));
        return balance(node);
    }

    Node* erase(Node* node, T key){
        if(!node) return node;
        if(key < node->key) node->left = erase(node->left, key);
        else if(key > node->key) node->right = erase(node->right, key);
        else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            } else {
                Node* temp = inorderSuccessor(node->right);
                node->key = temp->key;
                node->right = erase(node->right, temp->key);
            }
        }
        node->height = 1 + max(height(node->left), height(node->right));
        return balance(node);
    }

    void preorder(Node* node){
        if(!node) return;
        cout << node->key << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void clear(Node* node){
        if(!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    AVL() : root(nullptr), sz(0) {}

    int height(Node* node){
        if(!node) return 0;
        else return node->height;
    }

    void insert(T key){
        root = insert(root, key);
        sz++;
    }

    void erase(T key){
        root = erase(root, key);
        sz--;
    }

    int size(){
        return sz;
    }

    Node* find(T key){
        return find(root, key);
    }

    void preorder() {
        preorder(root);
        cout << endl;
    }

    Node* minValue(){
        return inorderSuccessor(root);
    }

    Node* maxValue(){
        return maxValueNode(root);
    }

    bool isBalanced(){
        return isBalanced(root);
    }

    ~AVL(){
        clear(root);
    }
};

#endif //HW4_AVL_AVL_H
