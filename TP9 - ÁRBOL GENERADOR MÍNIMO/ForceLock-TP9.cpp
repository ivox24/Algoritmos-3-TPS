#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cmath>
#include <queue>
using namespace std;

typedef tuple<int, int> arista; // (destino, peso)

class Grafo {
    int V;
    vector<vector<arista>> adj; // Lista de adyacencia: (origen, destino, peso)

public:
    Grafo(int V);
    void addArista(int u, int v, int w);
    int prim(int r);
};

Grafo::Grafo(int V) {
    this->V = V;
    adj.resize(V);
}

void Grafo::addArista(int u, int v, int w) {
    adj[u].push_back(make_tuple(v, w)); // Añadir arista de u a v con peso w
    adj[v].push_back(make_tuple(u, w)); // Añadir arista de v a u con peso w (grafo no dirigido)
}


//Cuando se encuentra una arista que tiene un peso menor al peso mínimo conocido para llegar a un vértice específico,
// se actualiza el peso mínimo y se agrega la arista a la cola de prioridad. Esto garantiza que en cada iteración del algoritmo,
//se seleccione la arista de menor peso que conecta un vértice en el AGM actual con un vértice fuera del AGM.

//Aclaración: En la matriz de adyacencia se guardan las aristas como tuplas de (destino,peso).
// Pero en la cola de prioridad se guardan como tuplas de (peso, vertice).
//Esto para no modificar el comparador greater.
int Grafo::prim(int r) { 
    vector<int> key(V, INT_MAX); //el peso o costo de llegar a cada vértice
    vector<bool> enAGM(V, false);

    priority_queue<arista, vector<arista>, greater<arista>> cola; //cola de prioridad, greater es el comparador

    int costoTotal = 0;

    key[r] = 0;
    cola.push(make_tuple(0, r)); //peso 0, vertice r 

    while (!cola.empty()) {
        int u = get<1>(cola.top()); //vertice actual. Extrae el de menor peso (mayor prioridad)
        cola.pop(); //borramos este elemento de mayor prioridad

        if (enAGM[u]) continue;

        enAGM[u] = true;
        costoTotal += key[u];

        for (auto& x : adj[u]) { //veo los vecinos
            int v = get<0>(x);
            int peso = get<1>(x); //de la arista que conecta a u con v

            if (!enAGM[v] && peso < key[v]) {
                key[v] = peso; //encontré un peso menor para v (vecino de u)
                cola.push(make_tuple(key[v], v));
            }
        }
    }

    return costoTotal;
}

int cantRolls(int key1, int key2) {
    int rolls = 0;
    for (int i = 0; i < 4; i++) {
        int d1 = key1 % 10;
        int d2 = key2 % 10;
        int dif = abs(d1 - d2);
        rolls += min(dif, 10 - dif);
        key1 /= 10;
        key2 /= 10;
    }
    return rolls;
}

int main() {
    int cases;
    cin >> cases;

    vector<int> resultados(cases);

    for (int i = 0; i < cases; i++) {
        int ckeys;
        cin >> ckeys;

        vector<int> keys(ckeys);
        for (int j = 0; j < ckeys; j++) {
            cin >> keys[j];
        }

        Grafo g(ckeys);

        int costoInicial = INT_MAX;
        int nodoMasCercanoAl0 = 0;
        for (int l = 0; l < ckeys; l++) {
            int rolls = cantRolls(0, keys[l]);
            if (rolls < costoInicial) {
                costoInicial = rolls;
                nodoMasCercanoAl0 = l;
            }
        }

        //Agrego las aristas con sus costos
        for (int u = 0; u < ckeys; u++) {
            for (int v = u + 1; v < ckeys; v++) {
                int rolls = cantRolls(keys[u], keys[v]);
                g.addArista(u, v, rolls);
            }
        }

        resultados[i] = costoInicial + g.prim(nodoMasCercanoAl0);
    }

    for (int resultado : resultados) {
        cout << resultado << endl;
    }
    
    return 0;
}
