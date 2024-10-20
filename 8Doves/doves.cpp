#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> tree_edges;
vector<int> discovery;
vector<vector<int>> edges;

enum Estado{
    NO_LO_VI,   //-1
    EMPECE_A_VER,
    TERMINE_DE_VER
};

int dfs_count = 0;

vector<int> low;
vector<int> parent;

vector<bool> is_articulation_point;

void dfs(int v, int p=-1){
    dfs_count++;  
    discovery[v] = dfs_count;
    low[v] = dfs_count; 
    int root_children = 0;  

    for(int u : edges[v]){
        if(discovery[u] == NO_LO_VI){
            tree_edges[v].push_back(u);
            parent[u] = v;
            root_children++;
            dfs(u, v);

            low[v] = min(low[v], low[u]);
        
            if(p != -1 && low[u] >= discovery[v]) is_articulation_point[v] = true;
            if(p == -1 && root_children > 1) is_articulation_point[v] = true;
        } else if(u != p){
            low[v] = min(low[v], discovery[u]);
        }
    }
}

void find_articulation_points(int n){
    tree_edges = vector<vector<int>>(n);
    discovery = vector<int>(n, NO_LO_VI);
    low = vector<int>(n, NO_LO_VI);
    parent = vector<int>(n, NO_LO_VI);
    is_articulation_point = vector<bool>(n, false);

    for(int i=0; i<n; i++){
        if(discovery[i] == NO_LO_VI){
            dfs(i);
        }
    }
}

vector<pair<int, int>> pigeon_value(int n, int m, vector<bool>& is_articulation_point,  vector<vector<int>>& graph) {
        vector<pair<int, int>> res;           // vector de pares (pigeon_value, estación)
            for (int i = 0; i < n; ++i) {           // para cada estación i
            // calcula pigeon_value (dfs) solo para los puntos de corte y no para todos los nodos (lento)
            if (is_articulation_point[i]) {                     
                int pigeon_value = 0;               
                vector<bool> visited(n, false);     // inicializar vector de visitados para buscar componentes conexas
                visited[i] = true;                  

                for (int j = 0; j < n; ++j) {       
                    if (!visited[j]) {              // si j no ha sido visitado entonces tenemos una nueva componente conexa
                        pigeon_value++;             
                        vector<int> stack;          // inicializar stack
                        stack.push_back(j);         // agregar j al stack
                        visited[j] = true;          

                        while (!stack.empty()) {        // mientras el stack no esté vacío
                            int node = stack.back();    
                            stack.pop_back();           

                            for (int v : graph[node]) {                
                                if (!visited[v] && v != i) {      
                                    visited[v] = true;                 
                                    stack.push_back(v);                
                                }
                            }
                        }
                    }
                }

                res.push_back({pigeon_value, i});
            }
            // si i no es un punto de corte, entonces pigeon_value = 1 porque solo tenemos una componente conexa asi que solo necesitamos una paloma de la estación central hacia alguna otra estación
            else {
                res.push_back({1, i});
            }
        }
        return res;
}

int main() {
    int n, m;
    while (cin >> n >> m && (n != 0 || m != 0)) {   // mientras n y m no sean 0

        edges = vector<vector<int>>(n);   
        int u, v;
        while (cin >> u >> v && (u != -1 || v != -1)) {  // mientras u y v no sean -1
            edges[u].push_back(v);                      // agregar arista u -> v
            edges[v].push_back(u);
        }

        find_articulation_points(n);

        vector<pair<int, int>> res = pigeon_value(n, m, is_articulation_point, edges);                 

        sort(res.rbegin(), res.rend(), [](const pair<int, int>& a, const pair<int, int>& b) {   
            if (a.first == b.first)
                return a.second > b.second;
            return a.first < b.first;
        });

        for (int i = 0; i < m; ++i) {
            cout << res[i].second << " " << res[i].first << endl;   
        }

        cout << endl;
    }

    return 0;
}