#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>
using namespace std;

int skylineCreciente(vector<int> &alturas, vector<int> &anchos, vector<int> &lis_anchos){
    int max_lis_anchos=0;
    for (int i = 0; i < alturas.size(); i++){ //La suma de anchos de la "subsecuencia creciente más larga" de alturas de edificios que termina en cada posición i
        lis_anchos[i] = anchos[i];
        for (int j = 0; j < i; j++){
            if (alturas[j]<alturas[i]){ //Si una altura previa a i es menor, existe una subsecuencia creciente
                lis_anchos[i] = max(lis_anchos[j] + anchos[i], lis_anchos[i]); //Nos quedamos con la subsecuencia creciente que maximice el ancho
            }
            }
            max_lis_anchos = max(max_lis_anchos, lis_anchos[i]); // Nos quedamos con la mayor
        }
    return max_lis_anchos;
    
}


int main(){
    int cantCasos;
    cin >> cantCasos;
    vector<pair<int, int>> resultados;
    for(int i = 1; i <= cantCasos; i++){
        int cEdificios;
        cin >> cEdificios;
        vector<int> alturas(cEdificios);
        vector<int> anchos(cEdificios);
        for (int j=0;j< cEdificios; j++){      
            cin>> alturas[j];
        }
        for(int j=0;j<cEdificios;j++){
            cin>>anchos[j];
        }

        int Crecimiento=0;
        int Decrecimiento=0;
        vector<int> lis_anchos(cEdificios); //La suma de anchos de la subsecuencia creciente más larga de alturas de edificios
        if(alturas.size()>1){
            Crecimiento= skylineCreciente(alturas,anchos,lis_anchos);
            vector<int> alturas_copy = alturas;
            vector<int> anchos_copy = anchos;

            reverse(alturas_copy.begin(), alturas_copy.end());
            reverse(anchos_copy.begin(), anchos_copy.end());
            Decrecimiento=skylineCreciente(alturas_copy,anchos_copy,lis_anchos);

        } else{
            Crecimiento=anchos[0];
            Decrecimiento=anchos[0];
        }
        resultados.push_back({Crecimiento, Decrecimiento});
    }
    for(int i=0;i<resultados.size();i++){
        int Crecimiento=resultados[i].first;
        int Decrecimiento= resultados[i].second;
        if(Crecimiento >= Decrecimiento){
            cout <<"Case "<< i+1 << ". Increasing (" << Crecimiento << "). Decreasing (" << Decrecimiento << ")." << endl;
        }else{
            cout << "Case " <<i+1<< ". Decreasing (" << Decrecimiento << "). Increasing (" << Crecimiento << ")." << endl;
        }
     }
    return 0;
}

//Inspirado en el problema de Longest Increasing Subsequence