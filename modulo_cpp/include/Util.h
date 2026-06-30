#ifndef UTIL_H
#define UTIL_H

#include <string>

using namespace std;

class Util {
    public:
        static void regresar();
        static void imprimir(string pantalla[], int size);
        static int devolverInput(string pantalla[], int size, int max);
};


#endif //UTIL_H
