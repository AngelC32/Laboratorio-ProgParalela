#include <omp.h>
#include <iostream>
using namespace std;
int main(){
    const int N = 100000;
    int a[N]; // Array de 100000 elementos

    // Inicialización del array
    for(int i=0; i<N; i++)
        a[i] = i;
    
    // Suma local de cada hilo - suma total de todos los hilos
    int local_sum = 0, sum=0;

    // Sección paralela
    #pragma omp parallel for private(local_sum) shared(sum)
    {
        for(int i=0; i<N; i++){
            local_sum += a[i];
        }
    }

    return 0;
}