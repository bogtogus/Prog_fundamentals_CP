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
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    WORKER* workers_list = nullptr;
    
    menu(workers_list);
    clear_list(workers_list);
    if (workers_list != nullptr) { 
        clear_list(workers_list);
    }

    return 0;
}


