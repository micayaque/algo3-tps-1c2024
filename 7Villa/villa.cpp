#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <algorithm>
#include <utility>

using namespace std;

vector<string> path_res;

int solve_villa(int rooms, const vector<vector<int>>& graph, const vector<vector<int>>& light_switches) {
    // estado inicial:
    int initial_room = 1;
    int target_room = rooms;
    vector<bool> lights_on(rooms + 1, false);
    lights_on[1] = true; // la luz del pasillo inicialmente está encendida

    // BFS
    queue<pair<pair<int, vector<bool>>, vector<string>>> queue;
    queue.push({{initial_room, lights_on}, {}}); // {estado, camino}
    set<pair<int, vector<bool>>> visited;
    visited.insert({initial_room, lights_on});

    while (!queue.empty()) {
        auto [current_state, path] = queue.front();
        queue.pop();
        
        int current_room = current_state.first;
        vector<bool> current_lights = current_state.second;
        
        // Verificamos si llegamos a la habitación final con todas las luces de las habitaciones apagadas excepto la del dormitorio
        if (current_room == target_room) {
            bool valid = true;
            for (int i = 1; i <= rooms; ++i) {
                if (i == target_room && current_lights[i] != true) {
                    valid = false;
                    break;
                }
                if (i != target_room && current_lights[i] != false) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                path_res = path;
                return path.size();
            }
        }
        
        // Si no somos el ultimo cuarto, nos movemos a los adyacentes
        for (int next_room : graph[current_room]) { 
            if(current_lights[next_room]){ // solo podemos movernos si la luz esta encendida
            path.push_back("Move to room " + to_string(next_room));
                pair<pair<int, vector<bool>>,vector<string>> next_state = {{next_room, current_lights}, path};
                if (visited.find(next_state.first) == visited.end()) {
                    visited.insert(next_state.first);
                    queue.push(next_state);
                }
            }
        }
        // Cambiamos el estado de las luces
        for (int light : light_switches[current_room]) {
            vector<bool> new_lights = current_lights;
            new_lights[light] = !new_lights[light];
            string action = new_lights[light] ? "on" : "off";
            path.push_back("Switch " + action + " light in room " + to_string(light));
            pair<pair<int, vector<bool>>, vector<string>> next_state = {{current_room, new_lights}, path};
            
            if (visited.find(next_state.first) == visited.end()) {
                visited.insert(next_state.first);
                queue.push(next_state);
            }
        }
    }

    return -1;
}

int main() {
    int villa_id = 1;
    while (true) {
        int r, d, s;
        cin >> r >> d >> s;
        if (r == 0 && d == 0 && s == 0) break;  // si r = d = s = 0, terminamos
        
        vector<vector<int>> graph(r + 1);
        for (int i = 0; i < d; ++i) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        
        vector<vector<int>> switch_controls(r + 1); // switch_controls[i] contiene las habitaciones controladas por el interruptor en la habitación i
        for (int i = 0; i < s; ++i) {
            int u, v;
            cin >> u >> v;
            switch_controls[u].push_back(v);
        }
        
        int steps = solve_villa(r, graph, switch_controls);
        
        cout << "Villa #" << villa_id << "\n";
        if (steps != -1) {
            cout << "The problem can be solved in " << steps << " steps:\n";
            for (const auto& step : path_res) {
                cout << step << "\n";
            }
        } else {
            cout << "El problema no se puede resolver\n";
        }
        cout << "\n";
        
        ++villa_id;
        
        cin.ignore();
        cin.ignore(); // ignore the newline character left in the buffer
    }
    
    return 0;
}
