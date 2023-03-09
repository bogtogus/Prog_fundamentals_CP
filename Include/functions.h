#pragma once
#include <main.h>

using namespace std;

enum class cmd { NoCmd, Add, Delete, Edit, Find, Fread, Fwrite, Sort, Task, Help, Show, Back, Exit };
enum class gf_flag {Nothing, Editing, SearchAdd};

string ltrim(const string);
string rtrim(const string);
void push_back(string*&, int&, string);
void push_back(string*&, string);
string* split(const string, const char=' ');
bool check_fio(const string);
bool check_post(const string);
bool check_year(const int year);
void format_fio(string&);
void format_post(string&);
bool is_letter_upper(const char);
int to_number(string, int&);
int input_number(int&);
cmd command(const string);
int get_fields(string&, string&, int&, gf_flag=gf_flag::Nothing);
bool check_if_used(const string*, const string);
bool file_valid(const string);
void uppercase_first(string&);
char uppercase_char(const char);
void downcase_word(string&);
