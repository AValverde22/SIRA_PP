#ifndef INTERES_CLASS_H
#define INTERES_CLASS_H

#include <string>
#include <vector>
using namespace std;

class InteresClass {
    public:
        struct Interes {
            string estudiante;
            string area;
        };

    static void generarCSVIntereses(const vector<Interes>& lista);
};

#endif //INTERES_CLASS_H
