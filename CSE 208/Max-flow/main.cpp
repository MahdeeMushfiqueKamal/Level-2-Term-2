#include<bits/stdc++.h>
#define watch(x) cout<<(#x)<<" is "<<(x)<<endl;
#define INF 1000000
using namespace std;
typedef long long ll;
bool DEBUG_MODE = false;

// Global variables
string Teams[100];
int NoOfTeams, Win[100], Lose[100], Remain[100], Games[100][100];

class Edmonds_Karp{
    int N;
    vector<int> *capasity, *residual, *passedFlow;

public:
    Edmonds_Karp(int N){
        this->N = N;
        capasity = new vector<int>[N];
        residual = new vector<int>[N];
        passedFlow = new vector<int>[N];
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                capasity[i].push_back(0);
                residual[i].push_back(0);
                passedFlow[i].push_back(0);
            }
        }

    }
    void addCapasity(int u,int v,int w){
        //cout<<"addCapasity is called for "<<u<<" "<<v<<" "<<w<<endl;
        capasity[u][v] = w;
        residual[u][v] = w;
    }
    int getCapasity(int u,int v){return capasity[u][v];}
    int getResidual(int u,int v){return residual[u][v];}

    void FindMaxFlow(int source, int sink){
        int maxFlow = 0;
        while(true){
            // do a bfs and find new flow.
            bool *visited = new bool[N]{0};
            int *parent = new int[N]{0};
            queue<int> q;

            q.push(source);
            visited[source] = true;
            parent[source] = -1;

            while(!q.empty()){
                int u = q.front();
                q.pop();

                for(int i=0;i<N;i++){
                    if(residual[u][i] > 0 && visited[i] == false){
                        // i needs to be visited
                        visited[i] = true;
                        parent[i] = u;
                        q.push(i);
                    }
                }
            }
            // end BFS
            if(visited[sink] == false){
                break; // ar kono path nai
            }
            // constructing path and find newFlow
            int newFlow = INF, i=sink;
            int pr = parent[i];
            while(true){
                newFlow = min(newFlow, residual[pr][i]);
                i = pr;
                pr = parent[i];
                if(pr==-1)break;
            }
            if(DEBUG_MODE)watch(newFlow);
            if(newFlow == 0) break;
            maxFlow+=newFlow;
            // updating residual and passedFlow
            i=sink; pr = parent[i];
            while(true){
                if(DEBUG_MODE) cout<<"updating residual and passedFlow for "<<pr<<" to "<<i<<endl;

                residual[pr][i] -= newFlow;
                passedFlow[pr][i] += newFlow;

                i = pr;
                pr = parent[i];
                if(pr==-1)break;
            }
        }
        //return maxFlow;
    }
};

int main()
{
    ifstream infile("input.txt");
    cin>>NoOfTeams;

    for(int i=0;i<NoOfTeams;i++){
        cin>>Teams[i]>>Win[i]>>Lose[i]>>Remain[i];
        for(int j=0;j<NoOfTeams;j++)cin>>Games[i][j];
    }


    /// output
    for(int team=0;team<NoOfTeams;team++){
        //cout<<"Finding things for team "<<Teams[team]<<endl;
        /// create and find max-flow
        //watch((NoOfTeams-1)*(NoOfTeams-2)/2)
        int flowSize = 2 + (NoOfTeams-1)*(NoOfTeams-2)/2 + NoOfTeams;
        int teamOffset = (NoOfTeams-1)*(NoOfTeams-2)/2 + 1;
        //watch(teamOffset)
        int placeToAdd = 1;

        Edmonds_Karp flowObj(flowSize);

        for(int i=0;i<NoOfTeams;i++){
            for(int j=0;j<NoOfTeams;j++){
                if(i>j || i==j || i==team || j==team) continue;
                //if(DEBUG_MODE)cout<<"Adding remaining match for "<<i<<" and "<<j<<endl;

                flowObj.addCapasity(0,placeToAdd,Games[i][j]);

                flowObj.addCapasity(placeToAdd,teamOffset+i,INF);
                flowObj.addCapasity(placeToAdd,teamOffset+j,INF);
                placeToAdd++;
            }
        }
        for(int i=0;i<NoOfTeams;i++){
            if(i==team) continue;
            flowObj.addCapasity(teamOffset+i,flowSize-1,Win[team]+Remain[team]-Win[i]);
        }

        //if(DEBUG_MODE)cout<<"max flow for team "<<Teams[team]<<flowObj.FindMaxFlow(0,flowSize-1)<<endl;
        bool qualify = true;
        flowObj.FindMaxFlow(0,flowSize-1);
        for(int i=1; i<= (NoOfTeams-1)*(NoOfTeams-2)/2; i++){
            if(flowObj.getResidual(0,i)>0){
                qualify = false;
            }
        }
        if(!qualify)cout<<Teams[team]<<" is eliminated"<<endl;

    }



    return 0;
}
