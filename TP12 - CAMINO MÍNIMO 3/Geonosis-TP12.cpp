#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <sstream>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

//Se puede poner long long int solo sobre los valores de la suma de matrices/resultados. Pero así tarda 3000ms.
//Si le pongo long long int a TODO, tarda 2009ms. Curioso.

//De la teórica
//Modificado para que me devuelva la suma de las distancias de las submatrices
long long int Dantzig(vector<vector<long long int>>& L) {
    int n = L.size();
    long long int sumaMatrices = 0;
    
    for (int k = 0; k < n-1; k++) {
        for (int i = 0; i <= k; i++) {
            for (int j = 0; j <= k; j++){
                L[i][k + 1] = min(L[i][k + 1], L[i][j] + L[j][k + 1]);
                L[k + 1][i] = min(L[k + 1][i], L[k + 1][j] + L[j][i]);

            }

        }
        for (int i = 0; i <= k; i++) {
            for (int j = 0; j <= k; ++j) {
                L[i][j] = min(L[i][j], L[i][k + 1] + L[k + 1][j]);          
            }
        }
        for (int i = 0; i <= k+1; i++) {
            for (int j = 0; j <= k+1; ++j) {
                sumaMatrices += L[i][j];
            }
        }
    }

    return sumaMatrices;
}


vector<vector<long long int>> reordenarMatrizEnergia(vector<vector<long long int>>& matriz_energia, vector<long long int>& orden_a_destruir) {
    long long int torres = matriz_energia.size();
    vector<vector<long long int>> matriz_reordenada(torres, vector<long long int>(torres));

    for (int i = 0; i < torres; i++) {
        for (int j = 0; j < torres; j++) {
            matriz_reordenada[i][j] = matriz_energia[orden_a_destruir[i]][orden_a_destruir[j]];
        }
    }

    return matriz_reordenada;
}


//La idea inicial era calcular dantzig, para tener las distancias de todos a todos
//Luego hacer la suma de todas las distancias, elimina la torre deseada, recalcular
// las distancias con dantzig y así sucesivamente. Pero esto es muy costoso, ya que
//estás recalculando dantzig todo el tiempo.

//Lo mejor es reordenar la matriz, es decir, acomodarla para eliminar en el orden que
//vos querés, así no tengo que recalcular

//Pongo primero las últimas torres que quiero eliminar y al final las primeras en
//eliminar

//Lo mejor es empezar asumiendo que ya eliminé todas las torres. Entonces me voy guardando
//la suma de las distancias de todos a todos en cada matriz cuadrada de nxn que hace
//dantzig mientras calculas las distancias 
int main() {
    int cases;
    cin >> cases;

    vector<long long int> resultados(cases);

    for (int caso = 0; caso < cases; caso++) {
        long long int torres;
        cin >> torres;
        vector<vector<long long int>> matriz_energia(torres,vector<long long int>(torres)); //Matriz cuadrada
        vector<long long int> orden_a_destruir(torres); //Siempre se destruyen todas las torres

        for (int i = 0; i < torres; i++) {
            for (int j = 0; j < torres; j++) {
                cin >> matriz_energia[i][j];
            }
        }

        for (int i = 0; i < torres; i++) {
            cin >> orden_a_destruir[i];
        }
        reverse(orden_a_destruir.begin(), orden_a_destruir.end());

        vector<vector<long long int>>matriz_energia_ordenada = reordenarMatrizEnergia(matriz_energia, orden_a_destruir);

        long long int suma_total = Dantzig(matriz_energia_ordenada);
        
        resultados[caso] = suma_total;
    
        }

        for (long long int resultado : resultados) {
                cout << resultado << endl;
            }
        return 0;
    }