#include "InteresClass.h"
#include <fstream>

void InteresClass::generarCSVIntereses(const vector<Interes>& lista) {
    ofstream archivo("../../data/intereses.csv");
    if (archivo.is_open()) {
        archivo << "estudiante,area\n";
        for (const auto& i : lista) archivo << i.estudiante << "," << i.area << "\n";
        archivo.close();
    }
}

