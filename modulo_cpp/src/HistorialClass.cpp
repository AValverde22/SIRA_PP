#include "HistorialClass.h"

#include <fstream>
#include <iostream>

// Exporta la lista del historial académico a un archivo CSV llamado "historial.csv" en el directorio "data".
void HistorialClass::generarCSVHistorial(const vector<Historial>& lista) {
    ofstream archivo("../../data/historial.csv");
    if (archivo.is_open()) {
        archivo << "estudiante,codigoCurso,nota\n";
        for (const auto& h : lista) archivo << h.estudiante << "," << h.codigoCurso << "," << h.nota << "\n";
        archivo.close();
    }
}
