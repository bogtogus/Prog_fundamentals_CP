#pragma once
#include <main.h>
#include <struct.h>
#include <functions.h>

#define _AUTO_OUTPUT true

void menu(WORKER*&);
void menu_help();
void menu_add(WORKER*&);
void menu_delete(WORKER*&);
void menu_edit(WORKER*&);
void menu_find(WORKER*&);
void menu_fread(WORKER*&, string*&);
void menu_fwrite(WORKER* const);
void menu_dbread(WORKER*&);
void menu_dbwrite(WORKER* const);
void menu_show(WORKER* const);
void menu_sort(WORKER*&);
void menu_task(WORKER*&);
