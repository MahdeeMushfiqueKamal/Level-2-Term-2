#include<bits/stdc++.h>
#define watch(x) cout<<(#x)<<" is "<<(x)<<endl;
#define fastIO() ios_base::sync_with_stdio(false);cin.tie(NULL);
#define pii pair<int,int>
using namespace std;

typedef long long ll;
int T,tc;

struct Node{             //B0...B1...B2...Bk-1
    int key;
	int degree;
	Node *parent;
	Node *child; //B0
	Node *sibling; //B1...B2...B3....Bk-1

	Node(int k = 0){
	    key = k;
	    degree = 0;
        parent = NULL;
        child = NULL;
        sibling = NULL;
	}

	void printNode(){
	    cout<<"Node: "<<this<<"\nKey: "<<key<<"\nDegree: "<<degree<<"\nLeft most Child: "<<child<<"\nNext Sibling: "<<sibling<<endl;

	}
};

void printBinomialTree(Node *n){
    int total_levels = n->degree+1;
    vector<Node*> tree[total_levels];
    tree[0].push_back(n);

    for(int level = 1;level<total_levels;level++){
        for(Node *par_ : tree[level-1]){
            if(par_->child != NULL){
                //ei level er parents er child ase
                Node *child_ = par_ ->child;
                while(true){
                    tree[level].push_back(child_);
                    child_ = child_ ->sibling;
                    if(child_ == NULL) break;
                }
            }
        }
    }

    for(int level=0;level<total_levels;level++){
        cout<<"Level "<<level<<" : ";
        for(Node *x: tree[level]) cout<<x->key<<" ";
        cout<<endl;
    }

}

Node *addNodes(Node *a, Node *b){
    if(a->degree != b->degree)cout<<"INVALID ADD NODE\n";
    if(a->key < b->key) swap(a,b);
    //a er child er left most sibling e b k rakhbo
    Node *c = a->child;
    if(a->degree == 0){
        a->child = b;
    }
    else{
        while(c->sibling != NULL) c = c->sibling;
        c->sibling = b;
    }
    a->degree = a->degree + 1;
    return a;
}

int main()
{
    fastIO();
    cout<<"Creating first node: "<<endl;
    Node *n1 = new Node(7);
    n1->printNode();

    cout<<"creating 2nd node: "<<endl;
    Node *n2 = new Node(12);
    n2->printNode();

    cout<<"Adding 2 nodes\n-------------\n";
    n1 = addNodes(n1,n2);
    printBinomialTree(n1);

    cout<<"Adding 4 nodes\n-------------\n";
    Node *n3 = addNodes(new Node(9),new Node(5));

    n1 = addNodes(n1,n3);
    printBinomialTree(n1);

    cout<<"Adding 8 nodes\n-------------\n";
    Node *n4 = addNodes(addNodes(new Node(17),new Node(1)),addNodes(new Node(19),new Node(11)));
    n1 = addNodes(n1,n4);
    printBinomialTree(n1);
    return 0;
}
