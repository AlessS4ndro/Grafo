#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Grafo{
private:
        int V,E;
        vector<pair<int,pair<int,int> > > aristas;
        vector<pair<int,pair<int,int> > > MST;
public:
        Grafo(int V,int E);
        void addArista(int u,int v,int w);
        int kruskalMST();
        void printMST();
};
Grafo::Grafo(int V,int E){
    this->V = V;
    this->E = E;
}
void Grafo::addArista(int u,int v,int w){
    aristas.push_back({w,{u,v}});
}

void Grafo::printMST(){
    vector<pair<int,pair<int,int> > >::iterator it;
    for(it = MST.begin();it!=MST.end();it++){
        cout << it->second.first << " - " << it->second.second << endl;
    }

}

struct DisjointSet{
    int *parent,*rnk;
    int n;

    DisjointSet(int n){
        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];

        for(int i=0;i<=n;i++){
            rnk[i] = 0;
            parent[i] = i;
        }
    }
    int Find(int u){
        if(u == parent[u]) return parent[u];
        else return Find(parent[u]);
    }

    void Union(int x,int y){
        x = Find(x);
        y = Find(y);
        if(x != y){
            if(rnk[x] < rnk[y]){
                rnk[y] += rnk[x];
                parent[x] = y;
            }
            else{
                rnk[x] += rnk[y];
                parent[y] = x;
            }
        }
    }
};
int Grafo::kruskalMST(){
    int MSTWeight = 0; //suma de todos los vertices
    sort(aristas.begin(),aristas.end());
    //para todos los vertices del grafo
    
    DisjointSet ds(this->V);

    vector<pair<int,pair<int,int> > >::iterator it;
    // para todos los vertices en el grafo
    for(it = aristas.begin(); it!=aristas.end();it++){
        int u = it->second.first;
        int v = it->second.second;

        int setU = ds.Find(u);
        int setV = ds.Find(v);


        if(setU != setV){
            int w = it->first;
            MST.push_back({w,{u,v}});
            MSTWeight += it->first;

            ds.Union(setU,setV);
        }
    }
    return MSTWeight;
}
int main(){
    int V,E;
    cout << "Numero de vertices: "<< endl;
    cin>>V;
    cout << "Numero de aristas: "<< endl;
    cin>>E;
    Grafo g(V,E);
    int u,v,w;
    for(int i=0;i<E;i++){
        cin >> u >> v >> w;
        g.addArista(u,v,w);
    }

    int weight = g.kruskalMST();
    cout << "MST: " << endl;
    g.printMST();
    cout << "peso de MST es: " << weight;

    return 0;
}
