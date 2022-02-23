#include<bits/stdc++.h>
#define watch(x) cout<<(#x)<<" is "<<(x)<<endl;

using namespace std;

struct Node{
    int data;
    Node *left;
    Node *right;
    int height;
};

Node *createNode(int x){
    Node *node = new Node;
    node->data = x;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int getHeight(Node *node){
    if(node == NULL) return 0;
    else return node->height;
}

class BST{
    Node *root = NULL;
    Node* recursiveInsertItem(Node *node, int x){
        if(node == NULL) node = createNode(x);
        else if(x <= node->data){
            node->left = recursiveInsertItem(node->left,x);
        }
        else if(x > node->data){
            node->right = recursiveInsertItem(node->right,x);
        }

        //adjusting
        node->height = 1 + max(getHeight(node->left),getHeight(node->right));
        int bf = BalanceFactor(node);
        if(!(bf == 0 || bf == 1 || bf ==-1 ))cout<<"Height  invariant violated.\nAfter  rebalancing:";
        if(bf > 1 && x <node->left->data) node =  LL_rotation(node);
        if(bf < -1 && x > node->right->data) node =  RR_rotation(node);
        if(bf > 1 && x > node->left->data) node = LR_rotation(node);
        if(bf < -1 && x < node->right->data) node = RL_rotation(node);
        return node;

    }
    bool recursiveSearchItem(Node *node, int x){
        if(node == NULL)return false;
        else if(node->data == x)return true;
        else if(x > node->data) recursiveSearchItem(node->right,x);
        else if(x < node->data) recursiveSearchItem(node->left,x);
    }

    Node* recursiveDeleteItem(Node *node, int x){
        if(node == NULL)return node;
        //searching for deleting
        else if(x > node->data){node->right = recursiveDeleteItem(node->right,x);}
        else if(x < node->data){node->left = recursiveDeleteItem(node->left,x);}
        else if(x == node->data){
            //found the node to be deleted.
            if(node->left == NULL && node->right == NULL){
                delete node;
                node = NULL;
            }
            else if(node->left == NULL){
                Node *temp = node->right;
                delete node;
                node = temp;
            }
            else if(node->right == NULL){
                Node *temp = node->left;
                delete node;
                node = temp;
            }
            else{
                //has 2 children
                Node *temp = node->right;
                //finding smallest in R-sub tree.
                while(temp->left != NULL)temp = temp->left;
                node->data = temp->data;
                node->right = recursiveDeleteItem(node->right, temp->data);
            }
        }
        //adjusting
        if(node != NULL){
            node->height = 1 + max(getHeight(node->left),getHeight(node->right));
            int bf = BalanceFactor(node);
            watch(node->data)
            watch(bf)
            if(!(bf == 0 || bf == 1 || bf ==-1 ))cout<<"Height invariant violated.\nAfter  rebalancing:";
            if(bf > 1){
                if(BalanceFactor(node->left) > 1){
                    node = LL_rotation(node);
                }
                else node = LR_rotation(node);
            }
            else if(bf < 1 && abs(bf)>1){
                if(BalanceFactor(node->right) > 1){
                    node = LL_rotation(node);
                }
                else node = RL_rotation(node);
            }
        }
        return node;
    }

    int recursiveHeight(Node *node){
        if(node == NULL) return -1;
        return 1+ max(recursiveHeight(node->left), recursiveHeight(node->right));
    }

    void recursivePreOrder(Node *node){
        if(node == NULL) return;
        cout<<node->data;
        if(node->left != NULL || node->right != NULL){
            cout<<"(";recursivePreOrder(node->left);cout<<")";
            cout<<"(";recursivePreOrder(node->right);cout<<")";
        }
    }

    int BalanceFactor(Node *node){
        if(node == NULL) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    Node *LL_rotation(Node *A){
        Node *B = A->left;
        Node *Br = B->right;
        ///rotation
        B->right = A;
        A->left = Br;

        A->height = 1 + max(getHeight(A->left),getHeight(A->right));
        B->height = 1 + max(getHeight(B->left),getHeight(B->right));
        return B;
    }

    Node *LR_rotation(Node *A){
        Node *B = A->left;
        Node *C = B->right;
        Node *Cl = C->left;
        Node *Cr = C->right;
        /// rotation
        C->left = B;
        C->right = A;
        B->right = Cl;
        A->left = Cr;

        A->height = 1 + max(getHeight(A->left),getHeight(A->right));
        B->height = 1 + max(getHeight(B->left),getHeight(B->right));
        C->height = 1 + max(getHeight(C->left),getHeight(C->right));
        return C;
    }

    Node *RL_rotation(Node *A){
        Node *B = A->right;
        Node *C = B->left;
        Node *Cl = C->left;
        Node *Cr = C->right;
        /// rotation
        C->left = A;
        C->right = B;
        A->right = Cl;
        B->left = Cr;

        A->height = 1 + max(getHeight(A->left),getHeight(A->right));
        B->height = 1 + max(getHeight(B->left),getHeight(B->right));
        C->height = 1 + max(getHeight(C->left),getHeight(C->right));
        return C;
    }

    Node *RR_rotation(Node *A){
        Node *B = A->right;
        Node *Bl = B->left;
        /// rotation
        B->left = A;
        A->right = Bl;

        A->height = 1 + max(getHeight(A->left),getHeight(A->right));
        B->height = 1 + max(getHeight(B->left),getHeight(B->right));
        return B;
    }
public:
    void insertItem(int x){
        root = recursiveInsertItem(root,x);
    }
    void searchItem(int x){
        if(recursiveSearchItem(root,x))cout<<"True"<<endl;
        else cout<<"False"<<endl;
    }
    void deleteItem(int x){
        root = recursiveDeleteItem(root,x);
    }
    void Print(){
        recursivePreOrder(root);
        cout<<endl;
    }
};




int main(){
    BST bst;
    ifstream infile("input.txt");
    char cmd; int x;
    while(infile>>cmd>>x){
        cout<<cmd<<" "<<x<<endl;
        if(cmd == 'F'){
            bst.searchItem(x);
        }
        else if(cmd == 'I'){
            bst.insertItem(x);
            bst.Print();
        }
        else if(cmd == 'D'){
            bst.deleteItem(x);
            bst.Print();
        }
    }
}
