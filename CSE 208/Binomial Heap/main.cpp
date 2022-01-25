#include<bits/stdc++.h>
#define watch(x) cout<<(#x)<<" is "<<(x)<<endl;
#define fastIO() ios_base::sync_with_stdio(false);cin.tie(NULL);
#define pii pair<int,int>
using namespace std;

typedef long long ll;
int T,tc;

struct Node{
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
	    cout<<"Node: "<<this<<"\nKey: "<<key<<"\nDegree: "<<degree<<"\nParent: "<<parent<<"\nLeft most Child: "<<child<<"\nNext Sibling: "<<sibling<<endl;

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
    b->parent= a;
    a->degree = a->degree + 1;
    return a;
}


class Binomial_Heap{
    vector<Node*> binomial_trees;
public:
    Binomial_Heap(){binomial_trees.push_back(NULL);}

    void Union_Heap(Node *n){
        binomial_trees.push_back(NULL); //one extra bit for carry

        vector<Node*> line1,line2,carry;        // copy of original trees

        for(int i=0; i<binomial_trees.size();i++){
            line1.push_back(binomial_trees[i]);
            carry.push_back(NULL);
        }

        for(int i=0;i<n->degree;i++)line2.push_back(NULL);
        line2.push_back(n);
        while(line2.size() != line1.size())line2.push_back(NULL);

//        //DEBUG
//        cout<<"Line1\n";
//        for(Node *x :line1)cout<<x<<" ";
//        cout<<endl;
//
//        for(Node *x :line1){
//            cout<<x<<" -->\n";
//            if(x!=NULL)printBinomialTree(x);
//        }
//        cout<<endl;
//
//        cout<<"Line2\n";
//        for(Node *x :line1)cout<<x<<" ";
//        cout<<endl;
//
//        for(Node *x :line2){
//            cout<<x<<" -->\n";
//            if(x!=NULL)printBinomialTree(x);
//        }
//        cout<<endl;
//
//        cout<<"Carry\n";
//        for(Node *x :carry)cout<<x<<" ";
//        cout<<endl;
//        //END-DEBUG

        // Doing the sum
        for(int i=0;i<binomial_trees.size();i++){
            vector<Node*> notNullBits;
            if(line1[i] != NULL)notNullBits.push_back(line1[i]);
            if(line2[i] != NULL)notNullBits.push_back(line2[i]);
            if(carry[i] != NULL)notNullBits.push_back(carry[i]);

            if(notNullBits.size() == 0){
                binomial_trees[i] = NULL;
            }
            else if(notNullBits.size() == 1){
                binomial_trees[i] = notNullBits[0];
            }
            else if(notNullBits.size() == 2){
                binomial_trees[i] = NULL;
                carry[i+1] = addNodes(notNullBits[0],notNullBits[1]);
            }
            else if(notNullBits.size() == 3){
                binomial_trees[i] = notNullBits[2];
                carry[i+1] = addNodes(notNullBits[0],notNullBits[1]);
            }
        }
        if(binomial_trees[binomial_trees.size()-1]==NULL) binomial_trees.pop_back();

//        //DEBUG
//        cout<<"binomial_trees\n";
//        for(Node *x :binomial_trees)cout<<x<<" ";
//        cout<<endl;
//        //END DEBUG
    }

    void Insert(int k){
        Node *new_B0 = new Node(k);
        //new_B0->printNode();
        Union_Heap(new_B0);
    }

    void Print(){
        for(int i=0;i<binomial_trees.size();i++){
            if(binomial_trees[i]==NULL)continue;
            cout<<"Binomial Tree, B"<<i<<endl;
            printBinomialTree(binomial_trees[i]);
        }
    }

    Node* FindKey(Node *x,int k){
//        cout<<"findkey called for "<<x<<endl;
        if(x==NULL){
            return NULL;
        }
        if(x->key==k)return x;

        if(x->child != NULL){
            Node *ans = FindKey(x->child,k);
            if(ans != NULL) return ans;
        }
        if(x->sibling != NULL){
            Node *ans = FindKey(x->sibling,k);
            if(ans != NULL) return ans;
        }
    }

    void IncreaseKey(int k,int x){
        for(int i=0;i<binomial_trees.size();i++){
            Node *ans = FindKey(binomial_trees[i],k);
            if(ans != NULL){
                //found key
                //ans->printNode();
                ans->key = x;

                //adjust with parents
                Node *par_;
                while(true){
                    par_ = ans->parent;
                    if(par_== NULL)break;
                    if(par_->key > ans->key) break;

//                    watch(par_->key);
//                    watch(ans->key)
                    if(par_->key < ans->key){
                        ans->key = par_->key;
                        par_->key = x;
                        ans = ans->parent;
                    }
                }
            }
        }
    }
    int FindMax(){
        int mx = 0;
        for(int i=0;i<binomial_trees.size();i++){
            if(binomial_trees[i]!= NULL) mx = max(mx,binomial_trees[i]->key);
        }
        return mx;
    }

    int ExtractMax(){
        int mx = FindMax();
        vector<Node*> children;

        for(int i=0;i<binomial_trees.size();i++){
            if(binomial_trees[i] == NULL) continue;
            if(binomial_trees[i]->key == mx){
                //found the node to be deleted;
                Node *child = binomial_trees[i]->child;
                while(child != NULL){
                    children.push_back(child);
                    child = child->sibling;
                }
                //watch(children.size())
                binomial_trees[i] = NULL;
                //deleted the node;
                //Print();
            }
        }
        // adding back the children nodes
        for(Node *x:children){
            x->sibling = NULL;
            Union_Heap(x);
//            cout<<"After union\n";
//            Print();
        }
        return mx;
    }

};
int main()
{
    ifstream infile("INPUT.txt");
    Binomial_Heap bh1;
    string cmd; int k,x;
    while(infile>>cmd){
        if(cmd=="INS"){
            infile>>k;
            bh1.Insert(k);
            cout<<"Inserted "<<k<<endl;
        }
        else if(cmd=="PRI"){
            cout<<"Printing Binomial Heap...\n-------------------------"<<endl;
            bh1.Print();
        }
        else if(cmd=="FIN"){
            cout<<"FindMax returned "<<bh1.FindMax()<<endl;
        }
        else if(cmd=="EXT"){
            cout<<"ExtractMax returned "<<bh1.ExtractMax()<<endl;
        }
        else if(cmd == "INC"){
            infile>>k>>x;
            bh1.IncreaseKey(k,x);
        }
    }
    return 0;
}
