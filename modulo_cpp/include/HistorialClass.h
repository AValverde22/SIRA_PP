#ifndef HISTORIAL_CLASS_H
#define HISTORIAL_CLASS_H

#include <string>
#include <vector>
using namespace std;

class HistorialClass {
    public:
        struct Historial {
            string estudiante;
            string codigoCurso;
            int nota;
        };

        static void generarCSVHistorial(const vector<Historial>& lista);
};


#endif //HISTORIAL_CLASS_H
