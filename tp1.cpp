#include <iostream>
#include <vector>

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

    Vertice() : cor(0) {}
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

void DFSVisit(vector<vector<Vertice>>& adj, vector<Vertice>& vertices, Vertice& u, int& tempo, int depth) {
    tempo++;
    u.abertura = tempo;
    u.cor = 1;
    u.profundidade = depth;
    u.lowpoint = u.profundidade;

    for (Vertice& v : adj[u.id]) { 
        if (vertices[v.id].cor == 0) {
            vertices[v.id].pai = u.id;
            DFSVisit(adj, vertices, vertices[v.id], tempo, depth+1);
            u.lowpoint = min(u.lowpoint, vertices[v.id].lowpoint);
        } else if (u.pai != v.id){
            printf("%d : %d, %d\n", vertices[v.id].id, vertices[v.id].pai, vertices[u.id].id);
            u.lowpoint = min(u.lowpoint, vertices[v.id].profundidade);
        }
    }

    tempo++;
    u.fechamento = tempo;
    u.cor = 2;
}

void DFS(vector<vector<Vertice>>& adj, vector<Vertice>& vertices){

    for (auto& v : vertices) {
        v.cor = 0;
    }

    int tempo = 0;
    
    for (auto& v : vertices){
        if(v.cor == 0 && v.id != 0){
            DFSVisit(adj, vertices, v, tempo, 0);
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
        printf("Aresta %d: ", i);
        scanf("%d%d", &v.id, &u.id);
        adicionarAresta(adj, &vertices[v.id], &vertices[u.id]);
    }


    DFS(adj, vertices);

    printGraph(adj, vertices);

    //Saída

    int f = -1;
    printf("Número de vértices de corte: %d\n", f);

    for(int i = 1; i <= n; i++){
        if(true){ // mudar para: se for vértice de corte
            printf("%d ", i);
        }
    }

    int c = -1;
    printf("\nNúmero de clusters: %d\n", c);
    for(int j = 1; j < 2; j++){ //mudar o for para tamanho da tabela de cluster
        printf("%d ", n+j);
        for(int k = 1; k < n; k++){
            printf("%d", k);
        }
    }
    return 0;
}

