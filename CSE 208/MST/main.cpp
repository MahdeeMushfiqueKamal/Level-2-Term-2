#include<bits/stdc++.h>
#define watch(x) cout<<(#x)<<" is "<<(x)<<endl;
#define fastIO() ios_base::sync_with_stdio(false);cin.tie(NULL);
#define pii pair<int,int>
#define pid pair<int,double>
using namespace std;

typedef long long ll;
int T,tc;

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
    void prim_MST(int src){
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
