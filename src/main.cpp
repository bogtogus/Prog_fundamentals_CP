#include <main.h>

#include <struct.h>
#include <functions.h>
#include <menu.h>

using namespace std;
/*
Var.5, >1800l
Локальная директория направляет к main.cpp
C:/Users/BOGDAN/projects/GUAP_OP_curs_VS/src/datas/data.txt
C:/Users/BOGDAN/projects/GUAP_OP_curs_VS/src/datas/bigdata.txt
C:/Users/polzovatel/Desktop/LRs/GUAP_OP_curs_VS/src/datas/data.txt 
*/

int main() {
    setlocale(LC_ALL, "1251");
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


