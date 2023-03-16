#include <main.h>
#include <struct.h>
#include <functions.h>
#include <menu.h>
using namespace std;
/*
>1800l
Локальная директория направляет к main.cpp
*/

int main() {
    if (setlocale(LC_ALL, "Russian") == NULL) {
        cout << "[!] Failed to set encoding." << endl;
    }
    if (!SetConsoleCP(1251)) {
        cout << "[!] Failed to set consoleCP." << endl;
    }
    if (!SetConsoleOutputCP(1251)) {
        cout << "[!] Failed to set consoleOutputCP." << endl;
    }
    cin.sync_with_stdio(false);
    WORKER* workers_list = nullptr;
    
    menu(workers_list);
    clear_list(workers_list);
    if (workers_list != nullptr) { 
        clear_list(workers_list);
    }

    return 0;
}
