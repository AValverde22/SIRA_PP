#include "Banner.h"

#include <iostream>
#include <string>
#include <windows.h>
#include <unistd.h>

using namespace std;

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

void Banner::loading(int pos) {
    string puntos[4] = {"    ", ".   ", "..  ", "... "};
    cout << "Cargando" << *(puntos + (pos % 4)) << endl;
}

void Banner::imprimirBannerGrande() {
    for (int i = 0; i < 12; i++) {
        banner_grande();
        loading(i);
        usleep(250000);
        system("cls");
    }
}