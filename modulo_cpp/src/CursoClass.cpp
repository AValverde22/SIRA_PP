#include "CursoClass.h"
#include <fstream>

void CursoClass::generarCSVCursos(const vector<Curso> & lista) {
    ofstream archivo("../../data/cursos.csv");
    if (archivo.is_open()) {
        archivo << "codigo,nombre,area,creditos\n";
        for (const auto& c : lista) archivo << c.codigo << "," << c.nombre << "," << c.area << "," << c.creditos << "\n";
        archivo.close();
    }
}

