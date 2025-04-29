import os
import matplotlib.pyplot as plt
from collections import defaultdict

#rutas
measurements_dir = "../data/measurements/"
plots_dir = "../data/plots/"


#diccionarios para almacenar los datos
resultados_tiempo = defaultdict(lambda: defaultdict(list))
resultados_memoria = defaultdict(lambda: defaultdict(list))

#procesar archivos
for filename in os.listdir(measurements_dir):
    if filename.startswith("mediciones_") and filename.endswith(".txt"):
        path = os.path.join(measurements_dir, filename)

        nombre_base = filename[len("mediciones_"):-len(".txt")]
        n = int(nombre_base.split('_')[0])

        with open(path, "r") as f:
            next(f)
            for linea in f:
                partes = linea.strip().split(',')
                if len(partes) == 3:
                    algoritmo, tiempo_us, memoria_kb = partes
                    tiempo_s = float(tiempo_us) / 1e6  #convertir us -> segundos
                    memoria = float(memoria_kb)
                    resultados_tiempo[algoritmo][n].append(tiempo_s)
                    resultados_memoria[algoritmo][n].append(memoria)

#calcular promedios
promedios_tiempo = defaultdict(list)
promedios_memoria = defaultdict(list)
n_values = sorted({n for alg in resultados_tiempo.values() for n in alg.keys()})

for algoritmo in resultados_tiempo:
    for n in n_values:
        tiempos = resultados_tiempo[algoritmo].get(n, [])
        memorias = resultados_memoria[algoritmo].get(n, [])
        
        if tiempos:
            promedio_tiempo = sum(tiempos) / len(tiempos)
            promedios_tiempo[algoritmo].append(promedio_tiempo)
        else:
            promedios_tiempo[algoritmo].append(None)

        if memorias:
            promedio_memoria = sum(memorias) / len(memorias)
            promedios_memoria[algoritmo].append(promedio_memoria)
        else:
            promedios_memoria[algoritmo].append(None)

#graficar tiempo
plt.figure(figsize=(10, 6))
for algoritmo, tiempos_prom in promedios_tiempo.items():
    plt.plot(n_values, tiempos_prom, marker='o', label=algoritmo)

plt.xlabel("Tamaño del arreglo (n)")
plt.ylabel("Tiempo promedio (segundos)")
plt.title("Comparación de algoritmos de ordenamiento (Tiempo)")
plt.legend()
plt.grid(True)
plt.xscale('log')
plt.yscale('log')

#guardar gráfico de tiempo
output_path = os.path.join(plots_dir, "sorting_comparison_time.png")
plt.savefig(output_path)
plt.close()

#graficar memoria
plt.figure(figsize=(10, 6))
for algoritmo, memorias_prom in promedios_memoria.items():
    plt.plot(n_values, memorias_prom, marker='o', label=algoritmo)

plt.xlabel("Tamaño del arreglo (n)")
plt.ylabel("Memoria promedio (KB)")
plt.title("Comparación de algoritmos de ordenamiento (Memoria)")
plt.legend()
plt.grid(True)
plt.xscale('log')

#guardar gráfico de memoria
output_path = os.path.join(plots_dir, "sorting_comparison_memory.png")
plt.savefig(output_path)
plt.close()