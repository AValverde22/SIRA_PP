#include "Banner.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

// Imprime el título grande "SIRA" en formato ASCII.
void Banner::banner_grande() {
    cout << endl;
    cout << "  /$$$$$$  /$$$$$$ /$$$$$$$   /$$$$$$" << endl;
    cout << " /$$__  $$|_  $$_/| $$__  $$ /$$__  $$" << endl;
    cout << "| $$  \\__/  | $$  | $$  \\ $$| $$  \\ $$" << endl;
    cout << "|  $$$$$$   | $$  | $$$$$$$/| $$$$$$$$" << endl;
    cout << " \\____  $$  | $$  | $$__  $$| $$__  $$" << endl;
    cout << " /$$  \\ $$  | $$  | $$  \\ $$| $$  | $$" << endl;
    cout << "|  $$$$$$/ /$$$$$$| $$  | $$| $$  | $$" << endl;
    cout << " \\______/ |______/|__/  |__/|__/  |__/" << endl;
    cout << endl;
}

// Imprime una animación de "Cargando" con puntos suspensivos según la posición.
void Banner::loading(int pos) {
    string puntos[4] = {"    ", ".   ", "..  ", "... "};
    cout << "Cargando" << *(puntos + (pos % 4)) << endl;
}

// Ejecuta la animación combinada del banner y el mensaje de carga, limpiando la pantalla iterativamente.
void Banner::imprimirBannerGrande() {
    for (int i = 0; i < 8; i++) {
        banner_grande();
        loading(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        system("cls");
    }
}