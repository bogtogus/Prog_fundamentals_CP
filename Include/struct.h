#pragma once
#include <main.h>

using namespace std;
struct WORKER {
    string fio;
    string post;
    int admission_year = 0;
    WORKER* next_elem = nullptr; 
    WORKER* prev_elem = nullptr;
};

void push_back(WORKER*&, string, string, const int);
void push_back(WORKER*&, WORKER* const);
void pop_back(WORKER*&);
int push_into(WORKER*&, const int, string, string, const int);
void pop_from(WORKER*&, const int);
void clear_list(WORKER*&);
bool is_list_empty(WORKER* const);
void show_list(WORKER* const);
int find_in_list(WORKER* const, string, WORKER*&, int&);
int find_in_list(WORKER* const, string, string, const int, WORKER*&, int&);
bool is_exist(WORKER* const, string, string, const int);
int fread_list(WORKER*&, string);
int fwrite_list(WORKER* const, string);
void sort_list_byfio(WORKER*&, bool=true);
void sort_list_bypost(WORKER*&, bool = true);
void sort_list_byyear(WORKER*&, bool = true);
void swap_elements(WORKER*&, WORKER*&, WORKER*&);
bool check_list_accuracy(WORKER* const);
WORKER* dotask_list(WORKER* const, const int);
