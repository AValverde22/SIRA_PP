#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>


#include "../include/Banner.h"
#include "../include/CursoClass.h"
#include "../include/HistorialClass.h"
#include "../include/InteresClass.h"
#include "../include/PrerrequisitoClass.h"
#include "../include/Opciones.h"

using namespace std;

// Punto de entrada del programa. Inicializa los datos de ejemplo, muestra el banner de bienvenida y lanza el menú de opciones del sistema.
int main() {
    vector<CursoClass::Curso> cursos = {
        {"CS101", "Programacion I", "Programacion", 4}, {"CS102", "Programacion II", "Programacion", 4},
        {"BD101", "Base de Datos I", "Datos", 4}, {"IA101", "Inteligencia Artificial", "IA", 4},
        {"SO101", "Sistemas Operativos", "Sistemas", 4}, {"RE101", "Redes de Computadoras", "Redes", 3},
        {"SI101", "Seguridad Informatica", "Seguridad", 3}, {"IS101", "Ingenieria de Software", "Sistemas", 4}
    };
    vector<PrerrequisitoClass::Prerrequisito> prerrequisitos = {
        {"CS102", "CS101"}, {"BD101", "CS102"}, {"IA101", "CS102"},
        {"SO101", "CS101"}, {"RE101", "SO101"}, {"SI101", "RE101"}
    };
    vector<HistorialClass::Historial> historial = {
        {"estudiantel", "CS101", 15}, {"estudiantel", "CS102", 12}, {"estudiantel", "BD101", 9}, {"estudiantel", "IA101", 14},
        {"estudiante2", "CS101", 18}, {"estudiante2", "CS102", 16}, {"estudiante2", "SO101", 10}, {"estudiante2", "IS101", 14}
    };
    vector<InteresClass::Interes> intereses = {
        {"estudiantel", "Programacion"}, {"estudiantel", "IA"}, {"estudiantel", "Datos"},
        {"estudiante2", "Sistemas"}, {"estudiante2", "Seguridad"}
    };


    system("cls");
    Banner::imprimirBannerGrande();

    Opciones opciones(cursos, prerrequisitos, historial, intereses);
    return 0;
}