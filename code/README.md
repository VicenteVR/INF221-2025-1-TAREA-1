# Documentación

## Multiplicación de matrices

### Programa principal
Se implementaron dos algoritmos de multiplicación de matrices: **Naive** y **Strassen**.  
En `matrix_multiplication.cpp` se ejecutan estos algoritmos para un par de matrices y se calcula su multiplicación.  
Además, se mide el tiempo de ejecución y la memoria utilizada por cada algoritmo.  
Los resultados de la multiplicación y las mediciones de desempeño se guardan en archivos `.txt`.

### Scripts
En el directorio `scripts/` se encuentran:

- `matrix_generator.py`: genera matrices de entrada de diferentes tipos (densa, dispersa, diagonal) y tamaños.
- `plot_generator.py`: procesa los archivos de mediciones y genera gráficos comparativos de tiempo y memoria.

**Para correr los programas:**

1. Generar matrices de entrada:

   ```bash
   python3 matrix_generator.py
   ```

2. Ejecutar las multiplicaciones:

   ```bash
   ./run_all_matrices.sh
   ```

3. Generar los gráficos:

   ```bash
   python3 plot_generator.py
   ```

Los resultados se guardan automáticamente en las carpetas correspondientes de `data/`.

---

## Ordenamiento de arreglo unidimensional

### Programa principal
Se implementaron cuatro algoritmos de ordenamiento: **SelectionSort**, **MergeSort**, **QuickSort** y **std::sort** (de la STL de C++).  
En `sorting.cpp` se ejecutan estos algoritmos sobre los arreglos generados.
Se mide el tiempo de ejecución y el consumo de memoria para cada algoritmo, y se guarda la información de salida y las mediciones en archivos `.txt`.

### Scripts
En el directorio `scripts/` se encuentran:

- `array_generator.py`: genera archivos de arreglos de distintos tamaños y tipos de orden (ascendente, descendente, aleatorio).
- `plot_generator.py`: procesa los archivos de mediciones y genera gráficos de comparación de tiempo y memoria para los algoritmos de ordenamiento.

**Para correr los programas:**

1. Generar los arreglos de entrada:

   ```bash
   python3 array_generator.py
   ```

2. Ejecutar los algoritmos de ordenamiento:

   ```bash
   ./run_all.sh
   ```

3. Generar los gráficos:

   ```bash
   python3 plot_generator.py
   ```

Los resultados se almacenan en las carpetas correspondientes de `data/`.

---


