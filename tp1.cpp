#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <set>

using namespace std;

class Vertice {
public:
    int id;
    int cor;
    int pai;
    int abertura;
    int fechamento;
    int profundidade;
    int lowpoint;

    Vertice() : cor(0), pai(-1) {}

    bool operator<(const Vertice& b) const {
        return id < b.id;
    }
};

void adicionarAresta(vector<vector<Vertice>>& adj, Vertice* u, Vertice* v) {
    adj[u->id].push_back(*v);
    adj[v->id].push_back(*u);
}

void DFSVisit(vector<vector<Vertice>>& adj, vector<Vertice>& vertices, Vertice& u, int& tempo, int depth, vector<Vertice>& verticesDeCorte, stack<pair<int, int>>& arestas, vector<set<pair<int, int>>>& biconnectedComponents) {
    tempo++;
    u.abertura = tempo;
    u.cor = 1;
    u.profundidade = depth;
    u.lowpoint = u.profundidade;
    int filhos = 0;
    bool verticeDeCorte = false;

    for (Vertice& v : adj[u.id]) { 
        if (vertices[v.id].cor == 0) {

            filhos++;
            vertices[v.id].pai = u.id;
            arestas.push(make_pair(u.id, v.id));
            DFSVisit(adj, vertices, vertices[v.id], tempo, depth+1, verticesDeCorte, arestas, biconnectedComponents);
            u.lowpoint = min(u.lowpoint, vertices[v.id].lowpoint);

            if(vertices[v.id].lowpoint >= u.profundidade && u.pai != -1) {
                verticeDeCorte = true;
            }

            if (vertices[v.id].lowpoint >= u.profundidade) {
                set<pair<int, int>> biconnectedComponent;
                while (!arestas.empty() && (arestas.top().first != u.id || arestas.top().second != v.id)) {
                    int uId = arestas.top().first;
                    int vId = arestas.top().second;
                    arestas.pop();
                    biconnectedComponent.insert(make_pair(min(uId, vId), max(uId, vId)));
                }
                if (!arestas.empty()) {
                    int uId = arestas.top().first;
                    int vId = arestas.top().second;
                    arestas.pop();
                    biconnectedComponent.insert(make_pair(min(uId, vId), max(uId, vId)));
                }
                
                biconnectedComponents.push_back(biconnectedComponent);
            }
        } else if (u.pai != v.id){
            u.lowpoint = min(u.lowpoint, vertices[v.id].profundidade);
            if (vertices[v.id].profundidade < u.profundidade) {
                arestas.push(make_pair(u.id, v.id));
            }
        }
    }

    if ((u.pai != -1 && verticeDeCorte) || (u.pai == -1 && filhos > 1)){
        verticesDeCorte.push_back(u);
    }

    tempo++;
    u.fechamento = tempo;
    u.cor = 2;
}

void DFS(vector<vector<Vertice>>& adj, vector<Vertice>& vertices, vector<Vertice>& verticesDeCorte, vector<set<pair<int, int>>>& biconnectedComponents){

    for (auto& v : vertices) {
        v.cor = 0;
    }

    int tempo = 0;
    stack<pair<int, int>> arestas;
    
    for (auto& v : vertices){
        if(v.cor == 0 && v.id != 0){
            DFSVisit(adj, vertices, v, tempo, 0, verticesDeCorte, arestas, biconnectedComponents);
        }
    }    
}

void printVertexCutClusterForest(const vector<Vertice>& verticesDeCorte, const vector<set<pair<int, int>>>& biconnectedComponents, int n) {
    vector<pair<int, int>> forest;
    int clusterNumber = n + 1;
    for (int j = 0; j < biconnectedComponents.size(); j++) {
        for (const auto& verticeDeCorte : verticesDeCorte) {
            for (const auto& cluster : biconnectedComponents[j]) {
                if (cluster.first == verticeDeCorte.id || cluster.second == verticeDeCorte.id) {
                    forest.push_back(make_pair(verticeDeCorte.id, clusterNumber));
                    break;
                }
            }
        }
        clusterNumber++;
    }
    sort(forest.begin(), forest.end());
    
    int numVertices = verticesDeCorte.size() + biconnectedComponents.size();
    int numArestas = forest.size();
    printf("%d %d\n", numVertices, numArestas);

    for (const auto& p : forest) {
        printf("%d %d\n", p.first, p.second);
    }
}


int main(){

    //Entrada
    
    int n, m;
    if (scanf("%d%d", &n, &m) != 2) {
        cerr << "Erro ao ler entrada" << endl;
        return 1;
    }

    vector<vector<Vertice>> adj(n+1); // uma posição a mais, porque não vou usar o 0
    vector<Vertice> vertices(n+1);

    for(int i = 1; i <= n; i++){
        vertices[i].id = i;
    }

    Vertice v, u;
    for(int i = 1; i <= m; i++){
        if (scanf("%d%d", &v.id, &u.id) != 2) {
            cerr << "Erro ao ler entrada" << endl;
            return 1;
        }
        adicionarAresta(adj, &vertices[v.id], &vertices[u.id]);
    }

    vector<Vertice> verticesDeCorte;
    vector<set<pair<int, int>>> biconnectedComponents;

    DFS(adj, vertices, verticesDeCorte, biconnectedComponents);

    //Saída

    int f = verticesDeCorte.size();
    printf("%d\n", f);

    sort(verticesDeCorte.begin(), verticesDeCorte.end());

    for(int i = 0; i < f; i++){
        printf("%d\n", verticesDeCorte[i].id);
    }

    int c = biconnectedComponents.size();
    printf("%d", c);

    sort(biconnectedComponents.begin(), biconnectedComponents.end(), [](const set<pair<int, int>>& a, const set<pair<int, int>>& b) {
        return *a.begin() < *b.begin();
    });

    for(int j = 0; j < c; j++) {
        set<int> uniqueVertices; // para armazenar vértices únicos
        for (auto it = biconnectedComponents[j].begin(); it != biconnectedComponents[j].end(); ++it) {
            uniqueVertices.insert(it->first);
            uniqueVertices.insert(it->second);
        }
        

        printf("\n%d %lu ", n + j + 1, uniqueVertices.size());
        for (auto vertex : uniqueVertices) {
            printf("%d ", vertex);
        }
    }

    printf("\n");


    printVertexCutClusterForest(verticesDeCorte, biconnectedComponents, n);

    return 0;
}
