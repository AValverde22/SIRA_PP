#ifndef OPCIONES_H
#define OPCIONES_H

#include "CursoClass.h"
#include "HistorialClass.h"
#include "InteresClass.h"
#include "PrerrequisitoClass.h"
#include <vector>

using namespace std;

class Opciones {
    public:
        Opciones(vector<CursoClass::Curso>& c, vector<PrerrequisitoClass::Prerrequisito>& p, vector<HistorialClass::Historial>& h, vector<InteresClass::Interes>& i);
        static void consultas();
};


#endif //OPCIONES_H
