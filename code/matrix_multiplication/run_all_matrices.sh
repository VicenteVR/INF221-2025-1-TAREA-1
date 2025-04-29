#!/bin/bash


cd "$(dirname "$0")"

echo "Procesando matrices de menor a mayor tamaño..."

#ordenar los archivos por nombre
for archivo1 in $(ls data/matrix_input/*_1.txt | sort -V)
do
    base=$(basename "$archivo1" _1.txt)

    echo "Multiplicando $base con naive y strassen..."

    ./matrix_multiplication "$base"
done

echo "¡Todas las multiplicaciones fueron realizadas!"
