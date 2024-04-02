#include <iostream>
#include <vector>
#include <algorithm>
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


void printGraph(const vector<vector<Vertice>>& adj, vector<Vertice>& vertices) {
    int V = adj.size()-1;
    for (int i = 1; i <= V; ++i) {
        cout << "Vértice " << i << " tem vizinhos:";
        for (const Vertice& v : adj[i])
            cout << " -> " << vertices[v.id].id << "(" << vertices[v.id].cor << ", "
            << vertices[v.id].abertura << ", " << vertices[v.id].fechamento << ", "
            << vertices[v.id].profundidade << ", " << vertices[v.id].lowpoint << ", " << vertices[v.id].pai << ")";
        cout << endl;
    }
}

void DFSVisit(vector<vector<Vertice>>& adj, vector<Vertice>& vertices, Vertice& u, int& tempo, int depth, vector<Vertice>& verticesDeCorte) {
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
            DFSVisit(adj, vertices, vertices[v.id], tempo, depth+1, verticesDeCorte);
            u.lowpoint = min(u.lowpoint, vertices[v.id].lowpoint);

            if(vertices[v.id].lowpoint >= u.profundidade && u.pai != -1) {
                verticeDeCorte = true;
            }
        } else if (u.pai != v.id){
            u.lowpoint = min(u.lowpoint, vertices[v.id].profundidade);
        }
    }

    if ((u.pai != -1 && verticeDeCorte) || (u.pai == -1 && filhos > 1)){
        verticesDeCorte.push_back(u);
    }

    tempo++;
    u.fechamento = tempo;
    u.cor = 2;
}

void DFS(vector<vector<Vertice>>& adj, vector<Vertice>& vertices, vector<Vertice>& verticesDeCorte){

    for (auto& v : vertices) {
        v.cor = 0;
    }

    int tempo = 0;
    
    for (auto& v : vertices){
        if(v.cor == 0 && v.id != 0){
            DFSVisit(adj, vertices, v, tempo, 0, verticesDeCorte);
        }
    }    
}

void DFSWithoutCutVerticesVisit(vector<vector<Vertice>>& adj, vector<Vertice>& vertices, Vertice& u, const set<int>& cutVertices, vector<Vertice>& clusterAtual) {
    u.cor = 1;
    clusterAtual.push_back(u);

    if (cutVertices.find(u.id) == cutVertices.end()) {
        for (Vertice& v : adj[u.id]) { 
            if (vertices[v.id].cor == 0 ) {
                DFSWithoutCutVerticesVisit(adj, vertices, vertices[v.id], cutVertices, clusterAtual);
            }
        }
    }

    u.cor = 2;
}

void DFSWithoutCutVertices(vector<vector<Vertice>>& adj, vector<Vertice>& vertices, vector<Vertice>& verticesDeCorte, vector<vector<Vertice>>& clusters) {
    
    for (auto& v : vertices) {
        v.cor = 0;
    }

    set<int> cutVertices;
    for (const Vertice& v : verticesDeCorte) {
        cutVertices.insert(v.id);
    }

    for (auto& v : vertices) {
        vector<Vertice> clusterAtual;
        if (v.cor == 0 && v.id != 0) { 
            DFSWithoutCutVerticesVisit(adj, vertices, vertices[v.id], cutVertices, clusterAtual);
        }
        if (!clusterAtual.empty()) {
            clusters.push_back(clusterAtual);
            clusterAtual.clear();
        }
    }
}

int main(){

    //Entrada
    
    int n, m;
    printf("Número de vértices e arestas: ");
    scanf("%d%d", &n, &m);

    vector<vector<Vertice>> adj(n+1); // uma posição a mais, porque não vou usar o 0
    vector<Vertice> vertices(n+1);

    for(int i = 1; i <= n; i++){
        vertices[i].id = i;
    }

    Vertice v, u;
    for(int i = 1; i <= m; i++){
        scanf("%d%d", &v.id, &u.id);
        adicionarAresta(adj, &vertices[v.id], &vertices[u.id]);
    }

    vector<Vertice> verticesDeCorte;
    DFS(adj, vertices, verticesDeCorte);

    vector<vector<Vertice>> clusters;
    DFSWithoutCutVertices(adj, vertices, verticesDeCorte, clusters);

    printGraph(adj, vertices);
    sort(verticesDeCorte.begin(), verticesDeCorte.end());
    //Saída

    int f = verticesDeCorte.size();
    printf("Número de vértices de corte: %d\n", f);

    for(int i = 0; i < f; i++){
        printf("%d ", verticesDeCorte[i].id);
    }

    int c = clusters.size();
    printf("\nNúmero de clusters: %d\n", c);
    for(int j = 0; j < c; j++){ //mudar o for para tamanho da tabela de cluster
        printf("\n%d ", j+n+1);
        for(int k = 0; k < clusters[j].size(); k++){
            printf("%d ", clusters[j][k].id);
        }
    }
    return 0;
}

