#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>
using namespace std;

int cantApariciones(vector<int>& posBellotas, int elem) {
    int j = 0;
    for (int i = 0; i < posBellotas.size(); i++) {
        if (posBellotas[i] == elem) {
            j++;
        }
    }
    return j;
}

//Se podría optimizar más si al estar en el nivel X, descartás los niveles menores a X-f. Así ocupás menos memoria

int Acorn(vector<vector<int>> &arboles, int t, int h, int f) {
    vector<vector<int>> maxAcorns(h+1, vector<int>(t, 0));
    vector<int>maxAcornsEnAlturaA(h+1,0); 

    for (int a = 0; a < h+1; a++) {
        for (int arb = 0; arb < t; arb++) {
            int bellotasAct=0;
            int maximasBellotasEnFmenos=0;
            if(a==0){
                maxAcorns[0][arb]=cantApariciones(arboles[arb],0);//dame las bellotas de esa pos

            } else if(a<f){
                maxAcorns[a][arb]= maxAcorns[a-1][arb] + cantApariciones(arboles[arb],a); //sumo las bellotas de abajo a las de la pos actual

            } else{
                bellotasAct = cantApariciones(arboles[arb], a);
                maximasBellotasEnFmenos= maxAcornsEnAlturaA[a-f];
                maxAcorns[a][arb] = max(maximasBellotasEnFmenos + bellotasAct, maxAcorns[a-1][arb] + bellotasAct);
            } //sería el máximo entre las actuales + el máximo en un nivel x-f, o las actuales + las de abajo
            
            if(maxAcornsEnAlturaA[a]<maxAcorns[a][arb]){ //actualizo la max cant de bellotas de cada altura
                maxAcornsEnAlturaA[a]=maxAcorns[a][arb];
            }           
        }

    }
    int maximoTotal = 0;
    for (int i = 0; i < t; i++) {
        maximoTotal = max(maximoTotal, maxAcorns[h][i]);
    }
    return maximoTotal;
}


int main(){
    int datasets;
    cin >> datasets;
    int i=0;
    vector<int> results;
    while(i< datasets){
        int t, h, f;
        cin >> t >> h >> f;
        vector<vector<int>> arboles(t); //cada arbol contiene los datos de las posiciones de las bellotas (t x pos)

        for (int j=0; j<t; j++){
            int b;
            cin >> b;
            for(int a=0; a<b; a++){
                int pos;
                cin >> pos;
                arboles[j].push_back(pos);
            }
        }
        
        int maxAcornsPossible=Acorn(arboles,t, h, f);
        results.push_back(maxAcornsPossible);

        i++;
    }
    int cero;
    cin>>cero;
    
    for(int i=0;i<results.size();i++){
        cout << results[i] << endl;
    }
        
    return 0;

}

//Se podría haber hecho más fácil si desde un principio la matriz arboles
// la hacía con ceros en las posiciones donde no había bellotas, 
//así en vez de tener que calcular todo el tiempo la cantidad de veces 
//que aparece esa posición en cada fila de la matriz arboles, lo tenía ya en la matriz
//Ya lo tenía muy desarrollado cuando me di cuenta y no quise volver atrás. (error)