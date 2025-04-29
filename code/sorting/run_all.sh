#!/bin/bash

cd "$(dirname "$0")"

echo "Listando archivos en data/array_input/:"
ls data/array_input/

#recorrer archivos ordenados de menor a mayor
for archivo in $(ls data/array_input/*.txt | sort -V)
do
    nombre_archivo=$(basename "$archivo")

    #saltar archivos que empiezan con 10000000_ (n = 10^7) (toma mucho tiempo su ejecución) 
    #descartar if en caso de querer correr los casos de 10^7
    if [[ "$nombre_archivo" == 10000000_* ]]; then
        echo "Saltando $nombre_archivo (n = 10^7)"
        continue
    fi

    echo "Procesando $nombre_archivo..."
    ./sorting "$nombre_archivo"
done

echo "¡Todos los archivos han sido procesados!"
