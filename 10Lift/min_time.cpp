#include <iostream>
#include <queue>
#include <map>
#include <algorithm>
#include <sstream>

using namespace std;

using Vertice = tuple<int, int, int>;     // (tiempo, ascensor, piso)

int min_tiempo(int n, int k, const vector<int>& tiempos, const vector<vector<int>>& pisos) {    
    if (k == 0) return 0;
    if (n == 0) return -1;

    priority_queue<Vertice, vector<Vertice>, greater<Vertice>> pq;
    map<int, map<int, int>> dist;   // dist[elevator][floor] = tiempo para llegar al piso con el elevador

    // inicializamos la cola de prioridad con los pisos a los que se puede llegar desde el piso 0
    for (int i = 0; i < n; ++i) {
        if (find(pisos[i].begin(), pisos[i].end(), 0) != pisos[i].end()) {
            pq.push({0, i, 0});
            dist[i][0] = 0;
        }
    }

    // Dijkstra
    while (!pq.empty()) {
        auto [tiempo, ascensor_actual, piso_actual] = pq.top();
        pq.pop();

        if (piso_actual == k) {
            return tiempo;
        }

        // nos movemos a los pisos adyacentes en el mismo ascensor  
        for (int piso_siguiente : pisos[ascensor_actual]) {
            if (piso_siguiente != piso_actual) {
                int tiempo_cambio = abs(piso_siguiente - piso_actual) * tiempos[ascensor_actual];
                int tiempo_nuevo = tiempo + tiempo_cambio;
                if (dist[ascensor_actual].find(piso_siguiente) == dist[ascensor_actual].end() || tiempo_nuevo < dist[ascensor_actual][piso_siguiente]) {
                    dist[ascensor_actual][piso_siguiente] = tiempo_nuevo;
                    pq.push({tiempo_nuevo, ascensor_actual, piso_siguiente});
                }
            }
        }

        // nos movemos a los pisos adyacentes en otro ascensor
        for (int ascensor_siguiente = 0; ascensor_siguiente < n; ascensor_siguiente++) {
            if (ascensor_siguiente != ascensor_actual && find(pisos[ascensor_siguiente].begin(), pisos[ascensor_siguiente].end(), piso_actual) != pisos[ascensor_siguiente].end()) {
                int tiempo_nuevo = tiempo + 60; 
                if (dist[ascensor_siguiente].find(piso_actual) == dist[ascensor_siguiente].end() || tiempo_nuevo < dist[ascensor_siguiente][piso_actual]) {
                    // update the time to reach the current floor with the next elevator
                    dist[ascensor_siguiente][piso_actual] = tiempo_nuevo;
                    pq.push({tiempo_nuevo, ascensor_siguiente, piso_actual});
                }
            }
        }
    }

    return -1;  // "IMPOSSIBLE"
}

int main() {
    string linea;
    while (getline(cin, linea)) {
        istringstream n_k(linea);
        int n, k;
        n_k >> n >> k;

        // leer tiempos de cambio de piso para cada ascensor     
        vector<int> tiempos(n);
        getline(cin, linea); 
        istringstream tiempos_stream(linea);
        for (int i = 0; i < n; ++i) {
            tiempos_stream >> tiempos[i];
        }

        // leer los pisos a los que se puede llegar con cada ascensor
        vector<vector<int>> pisos(n);
        for (int i = 0; i < n; ++i) {
            getline(cin, linea);
            istringstream pisos_stream(linea);
            int piso;
            while (pisos_stream >> piso) {
                pisos[i].push_back(piso);
            }
        }

        int res = min_tiempo(n, k, tiempos, pisos);
        if (res == -1) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            cout << res << endl;
        }
    }

    return 0;
}