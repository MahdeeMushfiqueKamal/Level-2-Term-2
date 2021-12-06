#include<bits/stdc++.h>
#define watch(x) cout<<(#x)<<" is "<<(x)<<endl;
#define fastIO() ios_base::sync_with_stdio(false);cin.tie(NULL);
#define pii pair<int,int>
using namespace std;

typedef long long ll;
int T,tc;

class Graph{
    int N;
    vector<int> *adj;
public:
    Graph(int N){
        this-> N = N;
        adj = new vector<int> [N];
    }
    void addDirectedEdge(int u, int v){adj[u].push_back(v);}
    void addUndirectedEdge(int u, int v){adj[u].push_back(v);adj[v].push_back(u);}
    void showGraph();
    void BFS(int source);
    void BFS_shortest_path(int source, int destination);
    void DFS(int source){
        bool *visited = new bool[N]{0};
        visited[source] = true;
        dfs_visit(source, visited);
    }
    void dfs_visit(int u, bool *visited);
    void topological_sort_using_BFS();
};

int main()
{
    fastIO();
    //ofstream out;
    //out.open("out.txt");

    Graph g1(6);
    g1.addDirectedEdge(0,2);
    g1.addDirectedEdge(1,2);
    g1.addDirectedEdge(1,4);
    g1.addDirectedEdge(2,3);
    g1.addDirectedEdge(3,5);
    g1.addDirectedEdge(4,5);

    g1.showGraph();
    g1.topological_sort_using_BFS();
    return 0;
}

void Graph::showGraph(){
    for(int i=0;i<N; i++){
        cout<<i<<" --> ";
        for(auto node: adj[i]) cout<<node<<" ";
        cout<<endl;
    }
}

void Graph::BFS(int source){
    queue<int> q;
    bool *visited = new bool[N]{0};

    q.push(source);
    visited[source] = true;

    while(!q.empty()){
        int u = q.front();
        q.pop();

        for(int i=0;i<adj[u].size(); i++){
            int v = adj[u][i];
            if(!visited[v]){
                q.push(v);
                visited[v] = true;
            }
        }
    }
}

void Graph::BFS_shortest_path(int source, int destination){
    queue<int> q;
    bool *visited = new bool[N]{0};
    int *dist = new int[N]{0};
    int *parent = new int[N]{0};

    q.push(source);
    visited[source] = true;
    parent[source] = -1;
    dist[source] = 0;

    while(!q.empty()){
        int u = q.front();
        q.pop();

        for(int i=0;i<adj[u].size(); i++){
            int v = adj[u][i];
            if(!visited[v]){
                q.push(v);
                visited[v] = true;
                //adjusting parent and distance
                parent[v] = u;
                dist[v] = dist[u]+1;
            }
        }
    }
    if(!visited[destination]){
        cout<<"Destination is not connected to source\n";
    }
    else{
        cout<<"Shortest distance: "<<dist[destination]<<endl;
        stack<int> path;
        int v = destination;
        while(1){
            path.push(v);
            v = parent[v];
            if (v == -1)break;
        }
        while(!path.empty()){
            cout<<path.top()<<" ";
            path.pop();
        }
    }
}

void Graph::dfs_visit(int u, bool *visited){
    //visit node
    cout<<u<<" ";
    visited[u] = true;

    for(int i=0;i<adj[u].size();i++){
        int v = adj[u][i];
        if(!visited[v]){
            visited[v] = true;
            dfs_visit(v, visited);
        }
    }
}

void Graph::topological_sort_using_BFS(){
    int *indegree = new int[N]{0};
    for(int u=0;u<N;u++){
        for(int i =0; i<adj[u].size(); i++){
            int v = adj[u][i];
            indegree[v]++;
        }
    }


    queue<int> q;
    for(int i=0;i<N;i++){
        if(indegree[i]==0)q.push(i);
    }

    while(!q.empty()){
        int u = q.front();
        cout<<u<<" ";
        q.pop();

        for(int i=0;i<adj[u].size();i++){
            int v = adj[u][i];
            indegree[v]--;
            if(indegree[v]==0)q.push(v);
        }
    }
}
