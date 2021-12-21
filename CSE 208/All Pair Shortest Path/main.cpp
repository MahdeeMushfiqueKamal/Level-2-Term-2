#include<bits/stdc++.h>
#define watch(x) cout<<(#x)<<" is "<<(x)<<endl;
#define fastIO() ios_base::sync_with_stdio(false);cin.tie(NULL);
#define pii pair<int,int>
#define INF 2000000
using namespace std;

typedef long long ll;
int T,tc;

class Graph{
    int N;
    int **adj;
public:
    Graph(int N){
        this->N = N;
        adj = new int*[N];
        for(int i=0;i<N;i++)adj[i] = new int[N];

        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(i==j)adj[i][j] = 0;
                else adj[i][j] = INF;
            }
        }
    }

    void addDirectedPath(int u, int v, int w){
        adj[u][v] = w;
    }
    void floyedWarshal(){
        for(int iv=0;iv<N;iv++){
            for(int i=0;i<N;i++){
                for(int j=0;j<N; j++){
                    if(i==j || i==iv || j==iv)continue;
                    adj[i][j] = min(adj[i][j], adj[i][iv] + adj[iv][j]);
                }
            }
        }
    }

    void showDistances(){
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(adj[i][j] == INF)cout<<"INF\t";
                else cout<<adj[i][j]<<"\t";
            }
            cout<<endl;
        }
    }


};

int main()
{
    fastIO();
    int n,m,u,v,w;
    ifstream inputfile("input2.txt");
    inputfile>>n>>m;
    Graph g(n);
    for(int i=0;i<m;i++){
        inputfile>>u>>v>>w;
        g.addDirectedPath(u-1,v-1,w);
    }

    g.floyedWarshal();
    cout<<"Shortest  distance  matrix"<<endl;
    g.showDistances();


    return 0;
}
