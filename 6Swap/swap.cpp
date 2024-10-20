#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<pair<int, int>> swaps;

int min_swaps(int n, string s, string t) {

    if( s == t ) return 0;

    int res = 0;

    vector<int> ab_positions;
    vector<int> ba_positions;

    // identificar posiciones a swapear 
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'a' && t[i] == 'b') {
            ab_positions.push_back(i+1);
        } else if (s[i] == 'b' && t[i] == 'a') {
            ba_positions.push_back(i+1);
        }
    }

    // verificar si es posible emparejar los desajustes 
    if ((ab_positions.size() + ba_positions.size()) % 2 != 0) {
        return -1;
    }

    // recorro los desajustes del estilo (s,t) --> (a,b) y los swapeo de a pares
    if(ab_positions.size() > 1){
        for (int i=0; i < ab_positions.size()-1; i+=2) {
            int pos1 = ab_positions[i];
            int pos2 = ab_positions[i+1];
            swaps.push_back({pos1, pos2});
            res++;
        }
    }

    // recorro los desajustes del estilo (s,t) --> (b,a) y los swapeo de a pares
    if(ba_positions.size() > 1){
        for (int i=0; i < ba_positions.size()-1; i+=2) {
            int pos1 = ba_positions[i];
            int pos2 = ba_positions[i+1];
            swaps.push_back({pos1, pos2});
            res++;
        }
    }

    // desajustes impares
    if ((ab_positions.size() % 2) == 1) {
        int pos1 = ab_positions.back();
        int pos2 = ba_positions.back();
        swaps.push_back({pos1, pos1});
        res++;
        swaps.push_back({pos1, pos2});
        res++;
    }

    return res;
}

int main() {

    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;

    int result = min_swaps(n, s, t);
    cout << result << endl;
    for (pair<int,int> s : swaps) {
        cout << s.first << " " << s.second << endl;
    }

    return 0;
}