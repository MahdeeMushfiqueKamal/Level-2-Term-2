#include<bits/stdc++.h>
#define watch(x) cout<<(#x)<<" is "<<(x)<<endl;
#define fastIO() ios_base::sync_with_stdio(false);cin.tie(NULL);
#define pii pair<int,int>
#define pid pair<int,double>
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

class Graph{
    int N;
    vector<pid> *adj;
public:
    Graph(int N){
        this->N = N;
        adj = new vector<pid> [N];
    }
    void showGraph();
    void addEdge(int u, int v, double w){
        adj[u].push_back(pid(v,w));
        adj[v].push_back(pid(u,w));
    }
    void prim_MST(int src);
    void kruskal_MST(){
        DSU dsu(N);
        double ans = 0;
        vector<pii> MST;
        vector<pair<double,pii>> edgeList;
        for(int u=0;u<N;u++){
            for(int i=0;i<adj[u].size();i++){
                int v = adj[u][i].first;
                double w = adj[u][i].second;
                edgeList.push_back(pair<double,pii>(w,pii(u,v)));
            }
        }
        sort(edgeList.begin(),edgeList.end());

        for(int i=0;i<edgeList.size();i++){
            //debugging Edgelist
            //cout<<edgeList[i].first<<" ,("<<edgeList[i].second.first<<","<<edgeList[i].second.second<<")\n";
            int u = edgeList[i].second.first;
            int v = edgeList[i].second.second;
            double w = edgeList[i].first;
            if(dsu.Find(u)!= dsu.Find(v)){
                MST.push_back(pii(u,v));
                dsu.Union(u,v);
                ans+=w;
            }
        }
        //cout<<"Cost of the minimum spanning tree :"<<ans<<endl;
        cout<<"List of edges selected by Kruskal's: {";
        for(int i=0;i<MST.size()-1;i++)cout<<"("<<MST[i].first<<","<<MST[i].second<<"),";
        cout<<"("<<MST[N-2].first<<","<<MST[N-2].second<<")}\n";
    }
};



int main()
{
    fastIO();
    ifstream infile("mst.txt");
    int n,m,u,v;
    double w;
    infile>>n>>m;
    Graph g(n);
    for(int i=0;i<m;i++){
        infile>>u>>v>>w;
        g.addEdge(u,v,w);
    }
    //g.showGraph();
    g.prim_MST(0);
    g.kruskal_MST();
    //ofstream out;
    //out.open("out.txt");

    return 0;
}

void Graph::showGraph(){
    for(int i=0;i<N; i++){
        cout<<i<<" --> ";
        for(auto node: adj[i]) cout<<"("<<node.first<<","<<node.second<<") ";
        cout<<endl;
    }
}

void Graph::prim_MST(int src){
    double ans = 0;
    vector<pii> MST;
    priority_queue<pair<double,pii>,vector<pair<double,pii>>, greater<pair<double,pii>> > q;   //weight, u->v
    bool *visited = new bool[N]{0};
    q.push(pair<double,pii>(0,pii(src,src)));

    while(!q.empty()){
        int came_from = q.top().second.first;
        int u = q.top().second.second; //current_node
        double w = q.top().first;
        q.pop();

        if(visited[u])continue;


        ans += w;
        MST.push_back(pii(came_from,u));

        visited[u]= true;
        //cout<<"Inside PQ operation: w="<<w<<" u="<<u<<endl;


        //adding the active edges to the PQ
        for(int i=0;i<adj[u].size();i++){
            int v = adj[u][i].first;
            double weight = adj[u][i].second;
            if(!visited[v]){
                //cout<<"Adding to PQ: weight="<<weight<<" u="<<u<<" v="<<v<<endl;
                q.push(pair<double,pii>(weight,pii(u,v)));
                //visited[v] = true;
            }
        }
    }
    cout<<"Cost of the minimum spanning tree :"<<ans<<endl;
    cout<<"List of edges selected by Prim's: {("<<MST[1].first<<","<<MST[1].second<<")";
    for(int i=2;i<N;i++)cout<<",("<<MST[i].first<<","<<MST[i].second<<")";
    cout<<"}\n";
    //return 0;
}
