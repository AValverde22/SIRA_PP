#ifndef CURSO_CLASS_H
#define CURSO_CLASS_H

#include <string>
#include <vector>
using namespace std;

class CursoClass {
    public:
        struct Curso {
            string codigo;
            string nombre;
            string area;
            int creditos;
        };

        static void generarCSVCursos(const vector<Curso> & lista);
};


#endif //CURSO_H
