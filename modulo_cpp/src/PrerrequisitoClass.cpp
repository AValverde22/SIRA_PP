//
// Created by aleja on 30/06/2026.
//

#include "PrerrequisitoClass.h"
#include <fstream>

void PrerrequisitoClass::generarCSVPrerrequisitos(const vector<Prerrequisito>& lista) {
    ofstream archivo("../../data/prerrequisitos.csv");
    if (archivo.is_open()) {
        archivo << "curso,prerrequisito\n";
        for (const auto& p : lista) archivo << p.curso << "," << p.prerrequisito << "\n";
        archivo.close();
    }
}