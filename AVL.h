#include <iostream>
using namespace std;
int const maxi=100;

// NODOS AVL
struct NodeBT {
    int data;
    int h=0;
    int f=0;
    NodeBT *left= nullptr;
    NodeBT *right= nullptr;
};
// NODOS BST
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// PILAS
template <typename T2=NodeBT>
class stack{
public:
    T2* list[maxi];
    int top=-1; //index of the top element
    int isfull (){
        if (top>=maxi-1) return 1;
        else return 0;
    }
    int isempty(){
        if(top==-1) return 1;
        else return 0;
    }
    T2* pop(){
        NodeBT* xd=list[top];
        (top)--;
        return xd;
    }
    void push(T2* x){
        (top)++;
        list[top]=x;
    }
};

// COLAS
template <typename T2=NodeBT>
class queue{
public:
    T2* list[maxi];
    int front=0, rear=0;
    int isfull(){
        if ((front==rear+1)%maxi) return 1;
        return 0;
    }
    int isempty() {
        if (front==rear) return 1;
        return 0;
    }
    void enqueue(NodeBT* node) {
        rear = (rear+1)%maxi;
        list[rear]=node;
    };
    T2* dequeue(){
        front=(front+1)%maxi;
        return list[front];
    };
};
NodeBT* front(queue<> q) {return q.list[q.front+1];}

// ARBOL AVL
class AVL{
private:
    bool recuri(NodeBT* &node, int value){
        //SI NO LO ENCUENTRA
        if(node==nullptr) {
            auto* nuevo = new NodeBT;
            nuevo->data=value;
            node = nuevo;
            return true;
        }
            // proceso recursivo
        else if(value < node->data)
            return recuri(node->left, value);
        else if(value > node->data)
            return recuri(node->right, value);
            //SI LO ENCUENTRA
        else return false;
    }
    bool recurf(NodeBT* &node, int value){
        //SI NO LO ENCUENTRA
        if(node==nullptr) return false;
            // proceso recursivo
        else if(value < node->data)
            return recurf(node->left, value);
        else if(value > node->data)
            return recurf(node->right, value);
        //SI LO ENCUENTRA
        return true;
    }
    bool recurr(NodeBT* &node, NodeBT* viejo, int value){
        //SI NO LO ENCUENTRA
        if(node==nullptr) return false;
            // proceso recursivo
        else if(value < node->data)
            return recurr(node->left,node,value);
        else if(value > node->data)
            return recurr(node->right, node, value);
        //SI LO ENCUENTRA
        del(node,viejo);
        return true;
    }
    int del(NodeBT* &node, NodeBT* viejo){
        // Se supone que lo encontramos
        int save=node->data;
        //Eliminar un nodo con 2 hijos
        if(node->left!=nullptr && node->right!=nullptr) {
            NodeBT *temp = node->right;
            viejo=temp;
            while (temp->left != nullptr) temp = temp->left;
            node->data = del(temp,viejo); //chapo al sucesor
        }//Eliminar una HOJA
        else if(node->left==nullptr && node->right==nullptr) {
            if (viejo->left==node) viejo->left=nullptr;
            if (viejo->right==node) viejo->right=nullptr;
            delete node;
        }
            //Eliminar un nodo con 1 hijo
        else {
            if(node->left!=nullptr) node->data=del(node->left,node);
            else if(node->right!=nullptr) node->data=del(node->right,node);
        }
        return save;
    }
    static void RRote(NodeBT* &Y){
        NodeBT* Z = Y->left;
        Y->left = Z->right;
        Z->right = Y;
        Y = Z;
    };
    static void LRote(NodeBT* &X){
        NodeBT* Z = X->right;
        X->right = Z->left;
        Z->left = X;
        X = Z;
    };
    void ordenes(NodeBT* n,int tipo){
        switch (tipo) {
            case 1: //preorder
                if (n==nullptr) return;
                cout<<n->data<<' ';
                ordenes(n->left,tipo);
                ordenes(n->right,tipo);
                break;
            case 2: //inorder
                if (n==nullptr) return;
                ordenes(n->left,tipo);
                cout<<n->data<<' ';
                ordenes(n->right,tipo);
                break;
            case 3: //postorder
                if (n==nullptr) return;
                ordenes(n->left,tipo);
                ordenes(n->right,tipo);
                cout<<n->data<<' ';
                break;
            case 4: {//breadth
                if (n==nullptr) return;
                queue<> q;
                q.enqueue(n);
                while (!q.isempty()){
                    NodeBT* node = q.dequeue();
                    cout<<node->data; cout<<' ';
                    if(node->left != nullptr)
                        q.enqueue(node->left);
                    if(node->right != nullptr)
                        q.enqueue(node->right);

                    //solo para imprimir como "arbol"
                    auto actual = front(q);
                    if (!q.isempty() && (actual->data<node->data || node->right==actual)) cout<<endl;
                } break;}
            case 5: {//depth
                if (n==nullptr) return;
                stack<> stack;
                stack.push(n);
                while(!stack.isempty()) {
                    NodeBT *node = stack.pop();
                    cout<<node->data<<' ';
                    if(node->right != nullptr)
                        stack.push(node->right);
                    if(node->left != nullptr)
                        stack.push(node->left);
                } break;}
            default: return;
        }
    }
public:
    NodeBT* root= nullptr;
    void insert(int value) {recuri(root, value); h(root); f(root); balanced(root);}
    void find(int value) {recurf(root, value);}
    void remove(int value) {recurr(root, nullptr, value); h(root); f(root); balanced(root);}

    int h(NodeBT* n){
        int hi=-1;
        int hd=-1;
        if (n->left!=nullptr) hi=h(n->left);
        if (n->right!= nullptr) hd=h(n->right);
        n->h=max(hi,hd)+1;
        return n->h;
    };
    int f(NodeBT* n){
        int hi=-1;
        int hd=-1;
        if (n->left!=nullptr) {
            hi=n->left->h;
            f(n->left);
        }
        if (n->right!= nullptr) {
            hd=n->right->h;
            f(n->right);
        }
        return n->f=hi-hd;
    };

    void balanced(NodeBT* &n){
        if (n->left!= nullptr) balanced(n->left);
        if (n->right!= nullptr) balanced(n->right);
        if (n->f>=2){
            if (n->left->f<=-1) {LRote(n->left); RRote(n);}
            else RRote(n);
            h(root); f(root);
            balanced(n);
        } if (n->f<=-2){
            if (n->right->f>=1) {RRote(n->right); LRote(n);}
            else LRote(n);
            h(root); f(root);
            balanced(n);
        }
    }

    TreeNode* avl2bst(NodeBT* feo){
        if (feo==nullptr) return nullptr;
        TreeNode* yap= new TreeNode;
        yap->val=feo->data;
        yap->left=avl2bst(feo->left);
        yap->right=avl2bst(feo->right);
        return yap;
    }

    void preorder(){ordenes(root,1); cout<<endl;}
    void inorder(){ordenes(root,2); cout<<endl;}
    void postorder(){ordenes(root,3); cout<<endl;}
    void breadth(){ordenes(root,4); cout<<endl;}
    void depth(){ordenes(root,5); cout<<endl;}
};