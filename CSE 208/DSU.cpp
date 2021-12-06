#include<bits/stdc++.h>
#define watch(x) cout<<(#x)<<" is "<<(x)<<endl;
#define fastIO() ios_base::sync_with_stdio(false);cin.tie(NULL);
#define pii pair<int,int>
using namespace std;

typedef long long ll;
int T,tc;

class DSU{
    int N,*parent,*rnk;

public:
    DSU(int N){
        this->N = N;
        parent = new int[N];
        for(int i=0; i<N; i++)parent[i] = -1;
        rnk = new int[N];
        for(int i=0; i<N; i++)rnk[i] = 1;
    }
    int Find(int i){
        if(parent[i] == -1) return i;
        else return Find(parent[i]);
    }
    void Union(int a,int b){
        int parent_a = Find(a);
        int parent_b = Find(b);
        if( parent_a == parent_b){
            cout<<"Already are in the same set\n"; return;
        }
        else if(rnk[parent_a] >= rnk[parent_b]){
            parent[parent_b] = parent_a;
            rnk[parent_a] += rnk[parent_b];
        }
        else{
            parent[parent_a] = parent_b;
            rnk[parent_b] += rnk[parent_b];
        }
    }
    void showParents(){
        for(int i=0;i<N;i++)cout<<parent[i]<<" ";
        cout<<endl;
    }
};

int main()
{
    fastIO();
    DSU dsu(5);
    dsu.showParents();
    dsu.Union(1,2);
    dsu.showParents();
    dsu.Union(3,4);
    dsu.showParents();
    dsu.Union(1,4);
    dsu.showParents();
    dsu.Union(3,2);
    dsu.showParents();

    //ofstream out;
    //out.open("out.txt");

    return 0;
}
