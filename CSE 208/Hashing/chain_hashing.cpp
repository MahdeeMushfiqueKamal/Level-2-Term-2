#include<bits/stdc++.h>
#define watch(x) cout<<(#x)<<" is "<<(x)<<endl;
#define fastIO() ios_base::sync_with_stdio(false);cin.tie(NULL);
#define psi pair<string,int>
using namespace std;

typedef long long ll;
int T,tc,N=10007;
/// hash 1
unsigned int Hash1(const string str, unsigned int seed = 0){
    unsigned int hash = seed;
    for(int i=0; i<str.length(); i++){
        hash = hash * 101  +  int(str[i]);
    }
    return hash;
}
/// hash 2 - djb2
unsigned long Hash2(const string str){
    unsigned long hash = 5381;
    for(int i=0; i<str.length(); i++)
        hash = ((hash << 5) + hash) + int(str[i]);
    return hash;
}
/// hash 3
unsigned long Hash3(const string str){
    int p = 31;
    long long power_of_p = 1;
    unsigned long hash_val = 0;
    for (int i = 0; i < str.length(); i++) {
        hash_val = (hash_val+ (str[i] - 'a' + 1) * power_of_p)% N;
        power_of_p = (power_of_p * p) % N;
    }
    return (hash_val%N + N) % N;
}

class HashTable_Chaining{
    int N;
    vector<psi> *table;
    int collision_ = 0, prob_ = 0;
public:

    HashTable_Chaining(int N){
        this-> N = N;
        table = new vector<psi> [N];
    }
    void INSERT(string k, int v){
        unsigned int hv = Hash2(k)%N;       /// Hash() is called
        if(table[hv].size()== 0){
            //cout<<"No hash collision for "<<k<<endl;
            table[hv].push_back(psi(k,v));
        }
        else{
            //cout<<"Collision Occured for "<<k<<endl;
            collision_++;
            table[hv].push_back(psi(k,v));
        }
    }
    void SEARCH(const string k){
        bool found = false;
        unsigned int hv = Hash2(k)%N;   /// hash() called
        for(int i=0;i<table[hv].size();i++){
            prob_++;
            if(table[hv][i].first == k){
                cout<<"value for key "<<k<<" is: "<< table[hv][i].second<<endl;
                found = true;
                break;
            }
        }
        if(!found){cout<<"Key not found in hash table for "<<k<<endl;}
    }
    void DELETE(const string k){
        unsigned int hv = Hash2(k)%N;   /// hash() called
        for(auto it=table[hv].begin();it != table[hv].end();it++){
            if(it->first == k){
                table[hv].erase(it);
                break;
            }
        }

    }
    int getCollision_(){return collision_;}
    int getProb_(){return prob_;}
};

int main()
{
    fastIO();
    string word;
    ifstream infile("random_10000.txt");
    if(!infile.good()){
        cout<<"can't open file"<<endl;
    }

    HashTable_Chaining HT1(N);
    for(int i=0;i<10000;i++){
        infile>>word;
        HT1.INSERT(word,i+1);
    }
    cout<<"Chaining Method : Number of collisions: "<<HT1.getCollision_()<<endl;


    ifstream queryfile("random_1000.txt");
    if(!queryfile.good()){
        cout<<"can't open file"<<endl;
    }
    for(int i=0;i<1000;i++){
        queryfile>>word;
        HT1.SEARCH(word);
    }

    cout<<"Chaining Method : Number of Prob: "<<HT1.getProb_()<<endl;
    HT1.SEARCH("dhruboo");

    HT1.DELETE("mtklrlv");
    HT1.SEARCH("mtklrlv");
    return 0;
}


// Hash1 and 2:
// https://stackoverflow.com/questions/98153/whats-the-best-hashing-algorithm-to-use-on-a-stl-string-when-using-hash-map
// Hash 3: Geesks for geeks
