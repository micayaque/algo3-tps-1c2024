#include <iostream>
#include <string>

using namespace std;

bool equivalent_strings(string s1, string s2){

    if(s1 == s2) return true;

    if (s1.length() % 2 == 1) return false;

    int n = s1.length();

    string a1 = s1.substr(0, n/2);
    string a2 = s1.substr(n/2, n);

    string b1 = s2.substr(0, n/2);
    string b2 = s2.substr(n/2, n);

    return (equivalent_strings(a1, b2) and equivalent_strings(a2, b1)) 
            or (equivalent_strings(a1, b1) and equivalent_strings(a2, b2));
}

int main() {
    string s1, s2;

    getline(cin, s1);
    getline(cin, s2);

    equivalent_strings(s1, s2) ? cout << "YES" : cout << "NO";

    return 0;
}