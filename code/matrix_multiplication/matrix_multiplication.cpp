#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <sys/resource.h>
#include "algorithms/naive.cpp"
#include "algorithms/strassen.cpp"

using namespace std;
using namespace chrono;

typedef vector<vector<int>> Matrix;

Matrix leer_matriz(const string& path) {
    ifstream archivo(path);
    Matrix matriz;
    string linea;
    while (getline(archivo, linea)) {
        istringstream iss(linea);
        vector<int> fila;
        int valor;
        while (iss >> valor) {
            fila.push_back(valor);
        }
        matriz.push_back(fila);
    }
    return matriz;
}

void guardar_matriz(const Matrix& matriz, const string& path) {
    ofstream archivo(path);
    for (const auto& fila : matriz) {
        for (size_t i = 0; i < fila.size(); ++i) {
            archivo << fila[i];
            if (i != fila.size() - 1) archivo << " ";
        }
        archivo << endl;
    }
}

//medir memoria en uso (en KB)
long long memoria_usada_kb() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Uso: " << argv[0] << " <nombre_base>" << endl;
        cout << "Ejemplo: " << argv[0] << " 64_densa_D0_a" << endl;
        return 1;
    }

    string nombre_base = argv[1];

    string path_matriz1 = "data/matrix_input/" + nombre_base + "_1.txt";
    string path_matriz2 = "data/matrix_input/" + nombre_base + "_2.txt";
    string path_medicion = "data/measurements/mediciones_" + nombre_base + ".txt";

    Matrix A = leer_matriz(path_matriz1);
    Matrix B = leer_matriz(path_matriz2);

    ofstream medicion(path_medicion);
    medicion << fixed << setprecision(6);
    medicion << "Algoritmo,Tiempo(s),Memoria(KB)" << endl;

    // --- Naive ---
    auto inicio_naive = high_resolution_clock::now();
    long long memoria_inicio_naive = memoria_usada_kb();
    Matrix C_naive = naiveMatrixMultiply(A, B);
    long long memoria_fin_naive = memoria_usada_kb();
    auto fin_naive = high_resolution_clock::now();
    long long memoria_naive = memoria_fin_naive - memoria_inicio_naive;
    chrono::duration<double> duracion_naive = fin_naive - inicio_naive;
    
    guardar_matriz(C_naive, "data/matrix_output/naive_" + nombre_base + ".txt");
    
    medicion << "naive," << duracion_naive.count() << "," << memoria_naive << endl;
    
    // --- Strassen ---
    auto inicio_strassen = high_resolution_clock::now();
    long long memoria_inicio_strassen = memoria_usada_kb();
    Matrix C_strassen = strassen(A, B);
    long long memoria_fin_strassen = memoria_usada_kb();
    auto fin_strassen = high_resolution_clock::now();
    long long memoria_strassen = memoria_fin_strassen - memoria_inicio_strassen;
    chrono::duration<double> duracion_strassen = fin_strassen - inicio_strassen;
    
    guardar_matriz(C_strassen, "data/matrix_output/strassen_" + nombre_base + ".txt");
    
    medicion << "strassen," << duracion_strassen.count() << "," << memoria_strassen << endl;


    cout << "Multiplicaciones realizadas exitosamente." << endl;

    return 0;
}