#include<bits/stdc++.h>
#define watch(x) cout<<(#x)<<" is "<<(x)<<endl;
#define fastIO() ios_base::sync_with_stdio(false);cin.tie(NULL);
#define pii pair<int,int>
#define pid pair<int,double>
# define INF 1000000
using namespace std;

typedef long long ll;
int T,tc;

class Graph{
    int N;
    vector<pii> *adj;
public:
    Graph(int N){
        this->N = N;
        adj = new vector<pii> [N];
    }
    void showGraph();
    void addUndirectedEdge(int u, int v, int w){
        adj[u].push_back(pii(v,w));
        adj[v].push_back(pii(u,w));
    }
    void addDirectedEdge(int u, int v, int w){adj[u].push_back(pii(v,w));}
    void dijsktra(int source, int destination);
    void BellmanFord(int source, int destination){
        bool contains_NEC = false;
        int *dist = new int[N];
        for(int i=0;i<N;i++)dist[i] = INF;
        dist[source] = 0;
        int *parent = new int[N];
        for(int i=0;i<N;i++)parent[i] = -1;


        for(int step=0; step<N-1; step++){          //O(V)
            //taking all edge                       //O(E)
            for(int u=0;u<N;u++){
                for(int i=0;i<adj[u].size();i++){
                    int v = adj[u][i].first;
                    int w = adj[u][i].second;
                    if(dist[u] + w < dist[v]){
                        dist[v] = dist[u] + w;
                        parent[v] = u;
                    }
                }
            }
        }
        //taking all edge                       //O(E)
        for(int u=0;u<N;u++){
            for(int i=0;i<adj[u].size();i++){
                int v = adj[u][i].first;
                int w = adj[u][i].second;
                if(dist[u] + w < dist[v]){
                    contains_NEC = true;
                    //cout<<"The graph contains a negative cycle"<<endl;
                    break;
                }
            }
            if(contains_NEC)break;
        }
        if(contains_NEC){
            cout<<"The graph contains a negative cycle"<<endl;
        }
        else{
            cout<<"The graph does not contain a negative cycle"<<endl;
            cout<<"Shortest path cost: "<<dist[destination]<<endl;
            vector<int> path;
            int u = destination;
            while(1){
                path.push_back(u);
                u = parent[u];
                if(u==-1)break;
            }
            reverse(path.begin(),path.end());
            for(int i=0; i<path.size()-1;i++)cout<<path[i]<<" -> ";
            cout<<path[path.size()-1]<<endl;
        }
    }
};



int main()
{
    fastIO();
    ifstream infile("input3.txt");
    int m,n,u,v,w,s,t;
    infile>>n>>m;
    Graph g(n);
    for(int i=0;i<m;i++){
        infile>>u>>v>>w;
        g.addDirectedEdge(u,v,w);
    }
    //g.showGraph();
    //g.dijsktra(0,5);
    g.BellmanFord(0,5);
    return 0;
}

void Graph::showGraph(){
    for(int i=0;i<N; i++){
        cout<<i<<" --> ";
        for(auto node: adj[i]) cout<<"("<<node.first<<","<<node.second<<") ";
        cout<<endl;
    }
}


void Graph::dijsktra(int source, int destination){
    bool *visited = new bool[N];
    for(int i=0;i<N;i++)visited[i] = false;
    int *dist = new int[N];
    for(int i=0;i<N;i++)dist[i] = INF;
    int *parent = new int[N];
    for(int i=0;i<N;i++)parent[i] = -1;

    priority_queue<pii,vector<pii>, greater<pii>> q;
    q.push(pii(0,source));
    dist[source] = 0;

    while(!q.empty()){
        int u = q.top().second;
        q.pop();

        if(visited[u])continue;

        visited[u] = true;
        //cout<<"visiting: "<<u<<endl;
        for(int i=0;i<adj[u].size();i++){
            int v = adj[u][i].first;
            int w = adj[u][i].second;
            //cout<<"Relaxing node "<<v<<" with weight "<<w<<endl;
            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                parent[v] = u;
                q.push(pii(dist[v],v));
            }
        }
    }
    cout<<"Shortest path cost: "<<dist[destination]<<endl;
    vector<int> path;
    int u = destination;
    while(1){
        path.push_back(u);
        u = parent[u];
        if(u==-1)break;
    }
    reverse(path.begin(),path.end());
    for(int i=0; i<path.size()-1;i++)cout<<path[i]<<" -> ";
    cout<<path[path.size()-1]<<endl;
}
