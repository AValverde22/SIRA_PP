#include "Util.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Pausa la ejecución del programa hasta que el usuario presione la tecla Enter para continuar.
void Util::regresar() {
    cout << "\nPresione enter para continuar... ";
    cin.get();
    cin.get();
}

// Limpia la pantalla e imprime un menú o conjunto de cadenas pasadas como arreglo.
void Util::imprimir(string pantalla[], int size) {
    system("cls");
    cout << endl;
    for (int i = 0; i < size; i++) cout << *(pantalla + i) << endl;
    cout << endl;
}

// Solicita y valida la entrada numérica del usuario dentro de un rango específico, reimprimiendo el menú si hay error.
int Util::devolverInput(string pantalla[], int size, int max) {
    int opcion = 0;

    cout << "Ingrese opcion (1 - " << max << "):" << endl;
    cout << "> ";
    cin >> opcion;

    while (opcion < 0 || opcion > max) {
        system("cls");
        imprimir(pantalla, size);

        cout << "Opción fuera del rango." << endl;
        cout << "Ingrese una opción válida (1 - " << max << "):" << endl;
        cout << "> ";
        cin >> opcion;
    }

    return opcion;
}
