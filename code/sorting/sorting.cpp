#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>
#include "algorithms/selectionsort.cpp"
#include "algorithms/mergesort.cpp"
#include "algorithms/quicksort.cpp"
#include "algorithms/sort.cpp"


using namespace std;
using namespace std::chrono;

//leer arreglo desde archivo
vector<int> leer_arreglo(const string& nombre_archivo) {
    vector<int> arreglo;
    ifstream archivo(nombre_archivo);
    int numero;
    while (archivo >> numero) {
        arreglo.push_back(numero);
    }
    archivo.close();
    return arreglo;
}

//guardar arreglo en archivo
void guardar_arreglo(const string& nombre_archivo, const vector<int>& arreglo) {
    ofstream archivo(nombre_archivo);
    for (size_t i = 0; i < arreglo.size(); ++i) {
        archivo << arreglo[i];
        if (i != arreglo.size() - 1) archivo << " ";
    }
    archivo.close();
}

//medir memoria (en KB)
long long memoria_usada_kb() {
    ifstream status("/proc/self/status");
    string linea;
    while (getline(status, linea)) {
        if (linea.find("VmRSS:") == 0) {
            long long memoria;
            sscanf(linea.c_str(), "VmRSS: %lld kB", &memoria);
            return memoria;
        }
    }
    return -1;
}

//medir tiempo y memoria de un algoritmo
template<typename Func>
double medir_tiempo_y_memoria(Func algoritmo, vector<int>& arreglo, long long& memoria) {
    auto inicio = chrono::high_resolution_clock::now();
    long long memoria_inicio = memoria_usada_kb();

    algoritmo(arreglo);

    long long memoria_fin = memoria_usada_kb();
    auto fin = chrono::high_resolution_clock::now();

    memoria = memoria_fin - memoria_inicio;

    chrono::duration<double> duracion = fin - inicio;
    return duracion.count() * 1e6; // microsegundos
}


// -------------------- Programa principal ---------------------

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Uso: " << argv[0] << " <nombre_archivo_entrada>" << endl;
        return 1;
    }

    string nombre_archivo = argv[1];
    string path_entrada = "data/array_input/" + nombre_archivo;
    string path_salida = "data/array_output/";
    string path_mediciones = "data/measurements/";

    vector<int> arreglo_original = leer_arreglo(path_entrada);
    cout << "Elementos leídos: " << arreglo_original.size() << endl;


    // 1. Selection Sort
    vector<int> arr_selection = arreglo_original;
    long long memoria_selection;
    long long tiempo_selection = medir_tiempo_y_memoria(selectionSort, arr_selection, memoria_selection);
    guardar_arreglo(path_salida + "selection_" + nombre_archivo, arr_selection);

    // 2. Merge Sort
    vector<int> arr_merge = arreglo_original;
    
    auto medir_mergeSort = [](vector<int>& arr) {
        mergeSort(arr, 0, arr.size() - 1);
    };
    long long memoria_merge;
    double tiempo_merge = medir_tiempo_y_memoria(medir_mergeSort, arr_merge, memoria_merge);
    guardar_arreglo(path_salida + "merge_" + nombre_archivo, arr_merge);

    // 3. Quick Sort
    vector<int> arr_quick = arreglo_original;
    
    auto medir_quickSort = [](vector<int>& arr) {
        quickSort(arr, 0, arr.size() - 1);
    };
    long long memoria_quick;
    double tiempo_quick = medir_tiempo_y_memoria(medir_quickSort, arr_quick, memoria_quick);
    guardar_arreglo(path_salida + "quick_" + nombre_archivo, arr_quick);

    // 4. std::sort
    vector<int> arr_std = arreglo_original;
    long long memoria_std;
    auto medir_sortArray = [](vector<int>& a){ a = sortArray(a); };
    long long tiempo_std = medir_tiempo_y_memoria(medir_sortArray, arr_std, memoria_std);
    guardar_arreglo(path_salida + "std_" + nombre_archivo, arr_std);

    // Guardar mediciones
    ofstream medicion(path_mediciones + "mediciones_" + nombre_archivo + ".txt");
    medicion << fixed << setprecision(2);
    medicion << "Algoritmo,Tiempo(us),Memoria(KB)" << endl;
    medicion << "SelectionSort," << tiempo_selection << "," << memoria_selection << endl;
    medicion << "MergeSort," << tiempo_merge << "," << memoria_merge << endl;
    medicion << "QuickSort," << tiempo_quick << "," << memoria_quick << endl;
    medicion << "std::sort," << tiempo_std << "," << memoria_std << endl;
    medicion.close();

    cout << "Procesado " << nombre_archivo << " exitosamente." << endl;

    return 0;
}
