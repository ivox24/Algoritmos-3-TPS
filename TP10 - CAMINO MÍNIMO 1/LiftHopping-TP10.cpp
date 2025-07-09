//#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

typedef tuple<int, int> arista; // (destino, peso)

class Grafo {
    int V;
    vector<vector<arista>> adj; // Lista de adyacencia: (origen, destino, peso)

public:
    Grafo(int V);
    void addArista(int u, int v, int w);
    unordered_map<int, int> dijkstra(int inicio);

};

Grafo::Grafo(int V) {
    this->V = V;
    adj.resize(V);
}

void Grafo::addArista(int u, int v, int w) {
    adj[u].push_back(make_tuple(v, w)); // Añadir arista de u a v con peso w
    adj[v].push_back(make_tuple(u, w)); // Añadir arista de v a u con peso w (grafo no dirigido)
    //cout << "Arista agregada entre nodos " << u << " y " << v << " con peso " << w << endl;
}

unordered_map<int, int> Grafo::dijkstra(int inicio) {
    unordered_map<int, int> dist;
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
    }
    dist[inicio] = 0;

    //auto comp = [&dist](int u, int v) { return dist[u] > dist[v]; };
    auto comp = [](const pair<int, int> &a, const pair<int, int> &b) {
        return a.second > b.second;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> cola(comp);
    cola.push({inicio, 0});

    while (!cola.empty()) {
        int u = cola.top().first;
        int d = cola.top().second;
        cola.pop();

        if (d > dist[u]) {
            continue;
        }

        for (auto &[v, peso] : adj[u]) {
            if (dist[u] != INT_MAX && dist[v] > dist[u] + peso) {
                dist[v] = dist[u] + peso;
                cola.push({v, dist[v]});
            }
        }
    }
    return dist;
}


void construirGrafo(Grafo &G, const vector<int> &tiempos, const vector<vector<int>> &pisos, unordered_map<int, vector<int>> &piso_a_nodo, unordered_map<int,int> &nodo_a_piso) {
    //piso_a_nodo es un diccionario que guarda para cada piso los nodos que tiene
    int nodo = 0;
    vector<int> nodos_pb; // Para guardar los nodos de planta baja

    for (int ascensor = 0; ascensor < pisos.size(); ascensor++) {
        for (int p = 0; p < pisos[ascensor].size(); p++) {
            int piso_actual = pisos[ascensor][p];
            if (piso_actual == 0) {
                nodos_pb.push_back(nodo);
            }
            piso_a_nodo[piso_actual].push_back(nodo);
            nodo_a_piso[nodo]=piso_actual;
            nodo++;
        }
    }

    int largo=0;
    for (int t=0; t< tiempos.size(); t++){
        for(int i=0; i < pisos[t].size(); i++){
            for(int j = 0; j < i; j++){
                G.addArista(i + largo, j + largo, tiempos[t] * (nodo_a_piso[i+largo]-nodo_a_piso[j+largo]));
            }
        }
        largo+=pisos[t].size();
    }

    //conexiones de costo 0 entre nodos de planta baja
    for (int i = 0; i < nodos_pb.size(); i++) {
        for (int j = i + 1; j < nodos_pb.size(); j++) {
            G.addArista(nodos_pb[i], nodos_pb[j], 0);
        }
    }
    //Los que están en el mismo piso, conectalos a costo 60, excepto en planta baja
    for (const auto &[piso, nodos] : piso_a_nodo) {
        if (piso !=0){      // No quiero que me cambie los costos del piso 0!!!
            for (int i =0; i < nodos.size(); i++) {
                for (int j = i + 1; j < nodos.size(); j++) {
                    G.addArista(nodos[i], nodos[j], 60);
                }
            }
        }    
    }

}

int main() {
    string linea;
    vector<string> resultados;
    while (getline(cin, linea) && !linea.empty()) { 
        istringstream datos(linea); // Convierte la línea leída en un flujo de entrada para procesar n y k.
        int n, k;
        datos >> n >> k;

        vector<int> tiempos(n);
        for (int i = 0; i < n; i++) {
            int tiempo;
            cin >> tiempo;
            tiempos[i] = tiempo;
        }
        
        cin.ignore();

        vector<vector<int>> pisos(n);
        for (int j = 0; j < n; j++) {
            string pisos_linea;
            getline(cin, pisos_linea);
            istringstream pisosInt(pisos_linea);
            int num;
            while (pisosInt >> num) {
                pisos[j].push_back(num);
            }
        }

        int numNodos = 0;
        for (const auto &p : pisos) {
            numNodos += p.size();
        }

        Grafo G(numNodos);
        unordered_map<int, vector<int>> piso_a_nodo;
        unordered_map<int, int> nodo_a_piso;
        construirGrafo(G, tiempos, pisos, piso_a_nodo, nodo_a_piso);

        int nodo_inicial= piso_a_nodo[0][0];
        unordered_map<int, int> distancias = G.dijkstra(nodo_inicial);

        int min_distancia = INT_MAX;
        if (piso_a_nodo.find(k) != piso_a_nodo.end()) {
            for (int nodo : piso_a_nodo[k]) {
                if (distancias.find(nodo) != distancias.end()) {
                    min_distancia = min(min_distancia, distancias[nodo]);
                }
            }
        }

        if (min_distancia == INT_MAX) {
            resultados.push_back("IMPOSSIBLE");
        } else {
            resultados.push_back(to_string(min_distancia));
        }
    }

    for (const auto &resultado : resultados) {
        cout << resultado << endl;
    }

    return 0;
}