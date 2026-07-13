#include "InteresClass.h"
#include <fstream>

// Exporta la lista de intereses de los estudiantes a un archivo CSV llamado "intereses.csv" en el directorio "data".
void InteresClass::generarCSVIntereses(const vector<Interes>& lista) {
    ofstream archivo("../../data/intereses.csv");
    if (archivo.is_open()) {
        archivo << "estudiante,area\n";
        for (const auto& i : lista) archivo << i.estudiante << "," << i.area << "\n";
        archivo.close();
    }
}

