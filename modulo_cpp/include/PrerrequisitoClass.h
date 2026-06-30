#ifndef PRERREQUISITO_CLASS_H
#define PRERREQUISITO_CLASS_H

#include <string>
#include <vector>

using namespace std;

class PrerrequisitoClass {
    public:
        struct Prerrequisito {
            string curso;
            std::string prerrequisito;
        };

        static void generarCSVPrerrequisitos(const std::vector<Prerrequisito>& lista);
};


#endif //PRERREQUISITO_CLASS_H
