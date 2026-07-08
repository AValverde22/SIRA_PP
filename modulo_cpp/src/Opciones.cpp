#include "Opciones.h"
#include "Util.h"


#include <unistd.h>
#include <string>
#include <iomanip>
#include <iostream>

void guardarTodosLosCSV(const vector<CursoClass::Curso>& c, const vector<PrerrequisitoClass::Prerrequisito>& p, const vector<HistorialClass::Historial>& h, const vector<InteresClass::Interes>& i, bool inicial) {
    CursoClass::generarCSVCursos(c);
    PrerrequisitoClass::generarCSVPrerrequisitos(p);
    HistorialClass::generarCSVHistorial(h);
    InteresClass::generarCSVIntereses(i);

    cout << "\n[EXITO] Todos los datos han sido guardados en los archivos CSV.\n";

    if (!inicial) Util::regresar();
}

// 3. REGISTRO
void registrarNota(vector<HistorialClass::Historial>& lista) {
    system("cls");
    HistorialClass::Historial h;
    cout << "\n ================= REGISTRAR NOTA ================= \n";
    cout << "ID del Estudiante: "; cin >> h.estudiante;
    cout << "Codigo del Curso: "; cin >> h.codigoCurso;
    cout << "Nota obtenida: "; cin >> h.nota;
    lista.push_back(h);

    cout << "\n[OK] Nota registrada temporalmente en memoria.\n";
    Util::regresar();
}

// 4. CONSULTA Y REPORTE
void mostrarHistorial(const vector<HistorialClass::Historial>& lista) {
    system("cls");
    string id;
    cout << "\n =============== CONSULTA HISTORIAL =============== \n";
    cout << "Ingrese ID del Estudiante: "; cin >> id;

    cout << "\nCursos de " << id << ":\n";
    bool encontrado = false;
    for (const auto& h : lista) {
        if (h.estudiante == id) {
            cout << "- Curso: " << h.codigoCurso << " | Nota: " << h.nota;
            if (h.nota >= 11) cout << " (Aprobado)\n";
            else cout << " (Desaprobado)\n";
            encontrado = true;
        }
    }
    if (!encontrado) cout << "\nNo se encontraron registros para este estudiante.\n";
    Util::regresar();
}

void reporteGeneral(const vector<HistorialClass::Historial>& historial, const vector<CursoClass::Curso>& cursos) {
    system("cls");
    string id;
    cout << "\n ================= REPORTE GENERAL ================= \n";
    cout << " Ingrese ID del Estudiante: "; cin >> id;

    int aprobados = 0, desaprobados = 0;
    int sumaNotas = 0, cantidadCursos = 0;
    int notaMax = -1, notaMin = 21;
    string cursoMax, cursoMin;
    bool encontrado = false;

    for (const auto& h : historial) {
        if (h.estudiante == id) {
            encontrado = true;
            sumaNotas += h.nota;
            cantidadCursos++;

            if (h.nota >= 11) aprobados++;
            else desaprobados++;

            if (h.nota > notaMax) { notaMax = h.nota; cursoMax = h.codigoCurso; }
            if (h.nota < notaMin) { notaMin = h.nota; cursoMin = h.codigoCurso; }
        }
    }

    if (!encontrado) {
        cout << "\nEstudiante no encontrado.\n";
        Util::regresar();
        return;
    }

    // Buscar nombres de los cursos para el reporte
    string nombreMax = cursoMax, nombreMin = cursoMin;
    for (const auto& c : cursos) {
        if (c.codigo == cursoMax) nombreMax = c.nombre;
        if (c.codigo == cursoMin) nombreMin = c.nombre;
    }

    float promedio = (float)sumaNotas / cantidadCursos;

    cout << "\n   Estudiante: " << id << "\n";
    cout << fixed << setprecision(1); // Formato para un decimal
    cout << "   Promedio general: " << promedio << "\n";
    cout << "   Cursos aprobados: " << aprobados << "\n";
    cout << "   Cursos desaprobados: " << desaprobados << "\n";
    cout << "   Curso con mayor nota: " << nombreMax << " (" << notaMax << ")\n";
    cout << "   Curso con menor nota: " << nombreMin << " (" << notaMin << ")\n";
    cout << " ==================================================\n";
    Util::regresar();
}

Opciones::Opciones(vector<CursoClass::Curso>& c, vector<PrerrequisitoClass::Prerrequisito>& p, vector<HistorialClass::Historial>& h, vector<InteresClass::Interes>& i) {
    // Generar CSV iniciales al abrir el programa
    guardarTodosLosCSV(c, p, h, i, true);

    const int length = 9;
    const int opciones = 5;
    string pantalla[] = {
        " ====================== SIRA ====================== ",
        " ||                                              || ",
        " || 1. Registrar nueva nota en historial         || ",
        " || 2. Consultar historial de un estudiante      || ",
        " || 3. Ver Reporte General del estudiante        || ",
        " || 4. Guardar cambios en archivos CSV           || ",
        " || 5. Salir                                     || ",
        " ||                                              || ",
        " ================================================== "
    };

    int seleccionado;
    do {
        Util::imprimir(pantalla, length);

        seleccionado = Util::devolverInput(pantalla, length, opciones);
        switch (seleccionado) {
            case 1: registrarNota(h); break;
            case 2: mostrarHistorial(h); break;
            case 3: reporteGeneral(h, c); break;
            case 4: guardarTodosLosCSV(c, p, h, i, false); break;
            default: cout << "\nSaliendo del sistema imperativo...\n"; break;
        }
    } while (seleccionado != opciones);
}