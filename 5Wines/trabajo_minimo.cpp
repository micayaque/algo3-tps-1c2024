#include <iostream>
#include <vector>

using namespace std;

// calcula el trabajo mínimo necesario para vender/comprar la cantidad de vino de cada habitante
long long calcular_trabajo_minimo(vector<int>& ai) {
    long long trabajo_total = 0;
    long long acumulador = 0;
    // acumulador calcula el vino necesario (exceso o déficit) mientras recorremos las casas
    // positivo --> exceso de vino que necesita ser movido a casas siguientes
    // negativo --> demanda de vino que necesita ser satisfecha desde casas anteriores
    for (int cantidad : ai) {
        acumulador += cantidad;             
        trabajo_total += abs(acumulador);       // al sumar el abs(acumulador) estamos guardando el trabajo necesario para equilibrar el vino en cada punto de la línea de casas,
                                                // entonces el exceso de vino se mueve lo más cerca posible a la casa que lo necesita, minimizando la distancia total recorrida
    }
    return trabajo_total;
}

int main() {

    while (true) {
        int N;
        cin >> N; // lee el número de habitantes (N)
        if (N == 0) break; // si N es 0 llegamos al ultimo caso
        
        vector<int> ai(N); // cantidades de vino a comprar/vender de los habitantes
        for (int i = 0; i < N; ++i) {
            cin >> ai[i];
        }
        
        long long res = calcular_trabajo_minimo(ai);
        cout << res << endl;
    }
    
    return 0;
}
