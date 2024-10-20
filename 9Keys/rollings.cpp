#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int roll_cost(const string& k1, const string& k2) {
    int cost = 0;
    for (int i = 0; i < 4; ++i) {
        int diff = abs(k1[i] - k2[i]);
        cost += min(diff, 10 - diff);  //distancia mínima en un ciclo de 0 a 9
    }
    return cost;
}

int min_rolls(const vector<string>& keys) {
    int n = keys.size();
    vector<int> min_cost(n, 10e10);     // costo mínimo para incluir el nodo i en el AGM
    vector<bool> in_MST(n, false);      // indica si el nodo i está en el AGM

    int total_cost = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    //representamos a las aristas candidatas como pair<costo, vértice>
    //en c++ vector es el contenedor por defecto para priority_queue
    //greater<pair<int, int>> es el comparador que se utilizará para mantener el orden de los elementos en la cola de prioridad
    //indica que la cola de prioridad es una min-heap, lo que significa que el elemento con el valor más pequeño estará en la parte
    //superior de la cola
    //en una min-heap, priority_queue mantiene el orden ascendente, lo que permite extraer el elemento con el menor costo primero

    //costo de moverse desde '0000' a cada clave
    int cost_0000 = 10e10;    
    //clave más cercana a '0000'
    int initial_vertex = -1;
    for (int i = 0; i < n; ++i) {
        if (cost_0000 > roll_cost("0000", keys[i])) {
            cost_0000 = roll_cost("0000", keys[i]);
            initial_vertex = i;
        }
    }

    total_cost += cost_0000;

    //iniciar prim desde la clave más cercana a '0000'   
    for (int i = 0; i < n; ++i) {
        min_cost[i] = roll_cost(keys[initial_vertex], keys[i]);
        //pushear el costo mínimo para alcanzar cada nodo desde la clave más cercana a '0000'
        pq.push({min_cost[i], i});
    }

    //prim
    while (!pq.empty()) {
        auto [cost, u] = pq.top();
        pq.pop();

        //si el nodo ya está en el AGM, continuar
        if (in_MST[u]) continue;
        //sino marcar el nodo como incluido en el AGM
        in_MST[u] = true;
        total_cost += cost; //sumar el costo de la arista
        //considerar los costos de las aristas que conectan el nodo u con los nodos no incluidos en el AGM
        for (int v = 0; v < n; ++v) {
            if (!in_MST[v]) {
                int new_cost = roll_cost(keys[u], keys[v]);
                if (new_cost < min_cost[v]) {
                    min_cost[v] = new_cost;
                    pq.push({new_cost, v});
                }
            }
        }
    }

    //retornamos el minimo costo de rolls para desbloquear todas las claves
    return total_cost;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<string> keys(N);
        for (int i = 0; i < N; ++i) {
            cin >> keys[i];
        }
        cout << min_rolls(keys) << endl;
    }
    return 0;
}
