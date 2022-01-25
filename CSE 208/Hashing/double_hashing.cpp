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

class HashTable_Double{
    int N;
    vector<psi> table;
    long int collision_ = 0, prob_ = 0;
public:

    HashTable_Double(int N){
        this-> N = N;
        for(int i=0;i<N;i++)table.push_back(psi("0",0));
    }
    void INSERT(string k, int v){
        int i = 0;
        while(true){
            unsigned int hv = (Hash2(k)%N + i*(Hash3(k)) )%N;       /// Hash() is called
            if(table[hv] == psi("0",0)){
                collision_ += i;
                table[hv]=psi(k,v);
                break;
            }
            i++;
        }
    }
    void SEARCH(const string k){
        int i=0;
        while(true){
            prob_+= 1;
            unsigned int hv = (Hash2(k)%N + i*(Hash3(k)) )%N;       /// Hash() is called
            if(table[hv] == psi("0",0)){
                cout<<"Key not found in hash table for "<<k<<endl;
                break;
            }
            else if(table[hv].first == k){
                cout<<"value for key "<<k<<" is: "<< table[hv].second<<endl;
                break;
            }
            i++;
        }
    }

    void DELETE(const string k){
        int i=0;
        while(true){
            unsigned int hv = (Hash2(k)%N + i*(Hash3(k)) )%N;       /// Hash() is called
            if(table[hv].first == k){
                table[hv] = psi("0",0);
                break;
            }
            i++;
        }
    }

//    void DELETE(const string k){
//        unsigned int hv = Hash2(k)%N;   /// hash() called
//        for(auto it=table[hv].begin();it != table[hv].end();it++){
//            if(it->first == k){
//                table[hv].erase(it);
//                break;
//            }
//        }
//
//    }
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

    HashTable_Double HT1(N);
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
