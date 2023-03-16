#include <main.h>
#include <functions.h>
#include <struct.h>
using namespace std;

string ltrim(const string str) {
    if (str.size() < 1) {
        return str;
    }
    string s;
    size_t start=0;
    while (str[start] == ' ') start++;
    while (start < str.size()) {
        s.push_back(str[start]);
        start++;
    }
    s.shrink_to_fit();
    return s;
}

string rtrim(const string str) {
    if (str.size() < 1) {
        return str;
    }
    string s;
    size_t end=str.size();
    size_t i = 0;
    while (str[end] == ' ') end--;
    while (i<= end) {
        s.push_back(str[i]);
        i++;
    }

    s.shrink_to_fit();
    return s;
}

string* split(const string str, const char separator) {
    string* tokens = nullptr;
    string::size_type start = 0;
    string::size_type end = 0;
    int n = 0;
    if (str.find(separator) == string::npos) {
        if (strcmp(str.c_str(), "") != 0) {
            push_back(tokens, n, str);
        }
        push_back(tokens, n, string("\0"));
        return tokens;
    }
    while (start < str.length() && str[start] == separator)
        start++;
    end = start + 1;
    while (end < str.length() - 1 && str[end] != separator)
        end++;
    while (end < str.length()) {
        if (end != start) {
            if (end == str.length() - 1 && str[end] != '\0' && str[end] != separator) { //костыль
                end++;
            }
            push_back(tokens, n, str.substr(start, end - start));
        }
        start = end;
        while (start < str.length() && str[start] == separator)
            start++;
        end = start + 1;
        while (end < str.length() - 1 && str[end] != separator)
            end++;
    }
    //for (int i = 0; i < n; i++) {
    //    cout << tokens[i] << ' ' << endl;
    //}
    push_back(tokens, n, string("\0"));
    return tokens;
}

void push_back(string*& arr, int& n, string str) {
    string* temp = new string[n + (int)1]{};
    for (int i = 0; i < n; i++) {
        temp[i] = arr[i];
    }
    temp[n] = str;
    if (arr != nullptr) {
        delete[] arr;
    }
    arr = temp;
    temp = nullptr;
    n++;
    return;
}

void push_back(string*& arr, string str) {
    int n = 1;
    if (arr != nullptr) {
        while (strcmp(arr[n].c_str(), "\0") != 0) {
            n++;
        }
    }
    string* temp = new string[n + (int)1];
    for (int i = 0; i < n - 1; i++) {
        temp[i] = arr[i];
    }
    temp[n - 1] = str;
    temp[n] = "\0";
    if (arr != nullptr) {
        delete[] arr;
    }
    arr = temp;
    temp = nullptr;
    return;
}

int to_number(string text, int& number) {
    text = ltrim(rtrim(text));
    try {
        number = stoi(text);
    }
    catch (std::invalid_argument) {
        return 1;
    }
    return 0;
}

int input_number(int& num) {
    cin >> num;
    if (!cin.good() || cin.peek() != '\n') {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(), '\n');
        return 1;
    }
    cin.ignore(cin.rdbuf()->in_avail(), '\n');
    return 0;
}

bool check_fio(const string fio) {
    string tfio = ltrim(rtrim(fio));
    bool ans = true;
    string* separated_fio = nullptr;
    string wrongl = "1234567890,?!@#$%^&*()_+=№;:=\"\'~`/\\";
    
    if (tfio.find(' ') == string::npos) {
        ans = false;
    }
    else if (tfio.find_first_of(wrongl) != string::npos) {
        ans = false;
    }
    else {
        separated_fio = split(tfio);
        int i = 0;
        while (strcmp(separated_fio[i].c_str(), "\0") != 0) { // количество блоков данных
            i++;
        }
        if (i > 3 || i < 2) {
            ans = false;
        }
        else if (i == 3) { // Фамилия_И._О.
            string::size_type first_dot1 = separated_fio[1].find('.'); 
            string::size_type first_dot2 = separated_fio[2].find('.');
            if (first_dot1 == string::npos || first_dot2 == string::npos) {
                ans = false;
            }
            else if (first_dot1 != separated_fio[1].rfind('.') ||
                     first_dot2 != separated_fio[2].rfind('.')) { // если слишком много точек в имени или отчестве
                ans = false;
            }
            else if (separated_fio[1].length() < 2 || 
                     separated_fio[1].length() > 3 ||
                     separated_fio[2].length() < 2 ||
                     separated_fio[2].length() > 3) { // если инициалы слишком коротки или длинны
                ans = false;
            }
            else if (first_dot1 + 1 != separated_fio[1].length() ||
                     first_dot2 + 1 != separated_fio[2].length()) { // если точки в инициалах не в их концах
                ans = false;
            }
            else if (!is_letter_upper(separated_fio[0][0]) ||
                     !is_letter_upper(separated_fio[1][0]) ||
                     !is_letter_upper(separated_fio[2][0])) { // регистр
                ans = false;
            }
            else {
                ans = true;
            }
        
        }
        else if (i == 2) { // Фамилия_И.
            string::size_type start = 0;
            int dots = 0;
            while (separated_fio[1].find('.', start) != string::npos) { //подсчёт точек
                start = separated_fio[1].find('.', start) + 1;
                dots++; 
            }
            if (dots > 1) {
                ans = false;
            }
            else {
                if (separated_fio[1].length() < (string::size_type)(2) ||
                    separated_fio[1].length() > (string::size_type)(3)) { // если инициалы слишком коротки или длинны
                    ans = false;
                }
                else if (separated_fio[1].find('.') == 0 || 
                         separated_fio[1].rfind('.') != separated_fio[1].length() - 1) { // если точка в начале или не в конце
                    ans = false;
                }
                else {
                    ans = true;
                    if (!is_letter_upper(separated_fio[0][0]) || 
                        !is_letter_upper(separated_fio[1][0]) ||
                        (separated_fio[1].find('.') + 1 < separated_fio[1].size() &&
                            !is_letter_upper(separated_fio[1][separated_fio[1].find('.') + 1]))) {
                        ans = false;
                    }
                }
            }
        }
        if (separated_fio != nullptr) {
            for (int s = 0; s < i; s++) {
                separated_fio[i].erase();
            }
            delete[] separated_fio;
            separated_fio = nullptr;
        }
    }
    return ans;
}

bool is_letter_upper(const char ch) {
    int first_up = (int)'А';
    int first_down = (int)'а';
    int last_down = (int)'я';
    int yo_down = (int)'ё';
    if ((int)ch < 0 &&
            (((int)ch >= first_down && (int)ch <= last_down) ||
            (int)ch == yo_down)) { // если расширенный символ - строчная буква или не буква
        return false;
    }
    else if ((int)ch > 0 && (islower(ch) || !isalpha(ch))) { // если ASCII - строчная буква или не буква
        return false;
    }
    return true;
}

bool check_post(const string post) {
    string pst = ltrim(rtrim(post));
    bool ans = true;
    string* separated_post = nullptr;
    if (pst.find_first_of(",?!@#$%^&*()_+=№;:=\"\'~`/\\") != string::npos) {
        ans = false;
    }
    return ans;
}

bool check_year(const int year) {
    if (year < 1900 || year > 2022) {
        return false;
    }
    return true;
}

void format_fio(string& fio) {
    string temp_fio = ltrim(rtrim(fio));
    string* separated_fio = nullptr;
    string* separated_io = nullptr;
    separated_fio = split(temp_fio);
    int i = 0;
    while (strcmp(separated_fio[i].c_str(), "\0") != 0) {
        i++;
    }
    string::size_type start = 0;
    int dots = 0;
    while (temp_fio.find('.', start) != string::npos) { //подсчёт точек
        start = temp_fio.find('.', start) + 1;
        dots++;
    }
    if (i == 3 && dots == 2) { // Фамилия_И._О.
        downcase_word(separated_fio[0]);
        downcase_word(separated_fio[1]);
        downcase_word(separated_fio[2]);
        uppercase_first(separated_fio[0]);
        uppercase_first(separated_fio[1]);
        uppercase_first(separated_fio[2]);
        string::size_type dash = separated_fio[0].find('-');
        if (dash != string::npos) {
            separated_fio[0][dash + 1] = uppercase_char(separated_fio[0][dash + 1]);
        }
        if (dots == 2) {
            fio = (separated_fio[0] + ' ' + separated_fio[1] + ' ' + separated_fio[2]);
        }
    }
    else if (i == 2 && dots == 2) { // Фамилия_И.О.
        separated_io = split(separated_fio[1], '.'); // разделённые инициалы БЕЗ точек
        fio.erase();
        downcase_word(separated_fio[0]);
        downcase_word(separated_io[0]);
        downcase_word(separated_io[1]);
        uppercase_first(separated_fio[0]);
        uppercase_first(separated_io[0]);
        uppercase_first(separated_io[1]);
        string::size_type dash = separated_fio[0].find('-');
        if (dash != string::npos) {
            separated_fio[0][dash + 1] = uppercase_char(separated_fio[0][dash + 1]);
        }
        if (dots == 2) {
            fio = (separated_fio[0] + ' ' + separated_io[0] + ". " + separated_io[1] + ".");
        }
    }
    else if (i == 2 && dots == 1) { // Фамилия_И.
        downcase_word(separated_fio[0]);
        downcase_word(separated_fio[1]);
        uppercase_first(separated_fio[0]);
        uppercase_first(separated_fio[1]);
        string::size_type dash = separated_fio[0].find('-');
        if (dash != string::npos) {
            separated_fio[0][dash + 1] = uppercase_char(separated_fio[0][dash + 1]);
        }
        fio = (separated_fio[0] + ' ' + separated_fio[1]);
    }
    if (separated_fio != nullptr)
        delete[] separated_fio;
    if (separated_io != nullptr)
        delete[] separated_io;
}

void format_post(string& post) {
    string temp_post;
    string* separated_post = nullptr;
    separated_post = split(post, ' ');
    int i = 0;
    while (strcmp(separated_post[i].c_str(), "\0") != 0) {
        i++;
    }
    for (string::size_type k = 0; k < i; k++) {
        downcase_word(separated_post[k]);
        uppercase_first(separated_post[k]);
        temp_post = temp_post + separated_post[k];
        if (k < i - 1) {
            temp_post = temp_post + ' ';
        }
    }
    if (separated_post != nullptr) {
        delete[] separated_post;
    }
    post = temp_post;
}

cmd command(const string text_cmd) {
    string tcmd = ltrim(rtrim(text_cmd));
    if (strcmp(tcmd.c_str(), "/add") == 0) {
        return cmd::Add;
    }
    else if (strcmp(tcmd.c_str(), "/delete") == 0) {
        return cmd::Delete;
    }
    else if (strcmp(tcmd.c_str(), "/edit") == 0) {
        return cmd::Edit;
    }
    else if (strcmp(tcmd.c_str(), "/find") == 0) {
        return cmd::Find;
    }
    else if (strcmp(tcmd.c_str(), "/fread") == 0) {
        return cmd::Fread;
    }
    else if (strcmp(tcmd.c_str(), "/fwrite") == 0) {
        return cmd::Fwrite;
    }
    else if (strcmp(tcmd.c_str(), "/dbread") == 0) {
        return cmd::DBread;
    }
    else if (strcmp(tcmd.c_str(), "/dbwrite") == 0) {
        return cmd::DBwrite;
    }
    else if (strcmp(tcmd.c_str(), "/help") == 0) {
        return cmd::Help;
    }
    else if (strcmp(tcmd.c_str(), "/show") == 0) {
        return cmd::Show;
    }
    else if (strcmp(tcmd.c_str(), "/sort") == 0) {
        return cmd::Sort;
    }
    else if (strcmp(tcmd.c_str(), "/task") == 0) {
        return cmd::Task;
    }
    else if (strcmp(tcmd.c_str(), "/back") == 0) {
        return cmd::Back;
    }
    else if (strcmp(tcmd.c_str(), "/exit") == 0) {
        return cmd::Exit;
    }
    tcmd.erase();
    return cmd::NoCmd;
}

int get_fields(string& fio, string& post, int& admy, gf_flag flag) {
    string addition;
    string temp_year;
    string temp_fio;
    string temp_post;
    int year = 0;
    bool subInserting = true;
    if (flag == gf_flag::SearchAdd) {
        addition = " (уточнение)";
        temp_fio = fio;
    }
    else if (flag == gf_flag::Editing) {
        addition = " (редактирование)";
    }
    else {
        addition = "";
    }
    cin.clear();
    cin.ignore(cin.rdbuf()->in_avail(), '\n');
    if (flag != gf_flag::SearchAdd) {
        cout << "Введите фамилию и инициалы сотрудника" << addition << ':' << endl;
        getline(cin, temp_fio);
        if (temp_fio == "/back" && flag == gf_flag::Nothing) {
            return 2;
        }
        format_fio(temp_fio);
        while (!check_fio(temp_fio)) {
            cout << "Фамилия и инициалы введены неверно. Попробуйте заново:" << endl;
            getline(cin, temp_fio);
            if (temp_fio == "/back" && flag == gf_flag::Nothing) {
                return 2;
            }
            format_fio(temp_fio);
        }
    }
    cout << "Введите должность сотрудника " << addition << ':' << endl;
    getline(cin, temp_post);
    format_post(temp_post);
    while (!check_post(temp_post)) {
        cout << "Должность введена неверно. Попробуйте заново:" << endl;
        getline(cin, temp_post);
        format_post(temp_post);
    }
    cout << "Введите год трудоустройства сотрудника " << addition << ':' << endl;
    while (subInserting) {
        getline(cin, temp_year);
        if (to_number(temp_year, year)) {
            cout << "Год должен быть числом. Попробуйте заново." << endl;
            continue;
        }
        else if (!check_year(year)) {
            cout << "Год должен быть настоящим. Попробуйте заново." << endl;
            continue;
        }
        else {
            break;
        }
    }
    fio = temp_fio;
    post = temp_post;
    admy = year;
    temp_fio.erase();
    temp_post.erase();
    return 0;
}

bool check_if_used(const string* used_files, const string file) {
    int i = 0;
    if (used_files == nullptr || used_files[i] == "\0") {
        return false;
    }
    while (used_files[i] != "\0") {
        if (strcmp(used_files[i].c_str(), file.c_str()) == 0) {
            return true;
        }
        i++;
    }
    return false;
}

bool file_valid(const string path) {
    ifstream file;
    file.open(path, ios_base::in);
    if (!file.is_open()) {
        file.close();
        return false;
    }
    file.close();
    return true;
}

void downcase_word(string& word) {
    int first_up = (int)'А';
    int last_up = (int)'Я';
    int yo_up = (int)'Ё';
    for (size_t i = 0; i < word.size(); i++) {
        if (is_letter_upper(word[i])) {
            if (word[i] > 0) {
                word[i] = tolower(word[i]);
            }
            else {
                if ((int)word[i] >= first_up && (int)word[i] <= last_up) {
                    word[i] = (char)((int)word[i] + 32);
                }
                else if ((int)word[0] == yo_up) {
                    word[i] = 'ё';
                }
                else {
                    continue;
                }
            }
        }
    }
}

void uppercase_first(string& word) {
    int first_up = (int)'А';
    int first_down = (int)'а';
    int last_down = (int)'я';
    int yo_down = (int)'ё';
    if (word[0] > 0) {
        word[0] = toupper(word[0]);
    }
    else {
        if ((int)word[0] >= first_down && (int)word[0] <= last_down) {
            word[0] = (char)((int)word[0] - 32);
        }
        else if ((int)word[0] == yo_down) {
            word[0] = 'Ё';
        }
        else { //слово уже с большой буквы
            return;
        }
    }
}

char uppercase_char(const char ch) {
    char retch = ch;
    int first_up = (int)'А';
    int first_down = (int)'а';
    int last_down = (int)'я';
    int yo_down = (int)'ё';
    if ((int)ch < 0) {
        if ((int)ch >= first_down && (int)ch <= last_down) {
            retch = (char)((int)ch - 32);
        }
        else if ((int)ch == yo_down) {
            retch = 'Ё';
        }
    }
    else {
        retch = toupper(ch);
    }
    return retch;
}

int callback(void* list, int argc, char** argv, char** azColName) {
    WORKER* head = (WORKER*)list;
    int adm_year = 0;
    string fio;
    string post;
    fio = utf8_to_cp1251(argv[0]);
    post = utf8_to_cp1251(argv[1]);
    adm_year = stoi(argv[2]);
    push_back(head, fio, post, adm_year);
    return 0;
}

string utf8_to_cp1251(const string str) {
    std::string res;
    WCHAR *ures = nullptr;
    char *cres = nullptr;
 
    int result_u = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, 0, 0);
    if (result_u != 0)
    {
        ures = new WCHAR[result_u];
        if (MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, ures, result_u))
        {
            int result_c = WideCharToMultiByte(1251, 0, ures, -1, 0, 0, 0, 0);
            if (result_c != 0)
            {
                cres = new char[result_c];
                if (WideCharToMultiByte(1251, 0, ures, -1, cres, result_c, 0, 0))
                {
                    res = cres;
                }
            }
        }
    }
 
    delete[] ures;
    delete[] cres;
 
    return res;
}

std::string cp1251_to_utf8(const string str) {
    std::string res;
    WCHAR *ures = nullptr;
    char *cres = nullptr;
 
    int result_u = MultiByteToWideChar(1251, 0, str.c_str(), -1, 0, 0);
    if (result_u != 0)
    {
        ures = new WCHAR[result_u];
        if (MultiByteToWideChar(1251, 0, str.c_str(), -1, ures, result_u))
        {
            int result_c = WideCharToMultiByte(CP_UTF8, 0, ures, -1, 0, 0, 0, 0);
            if (result_c != 0)
            {
                cres = new char[result_c];
                if (WideCharToMultiByte(CP_UTF8, 0, ures, -1, cres, result_c, 0, 0))
                {
                    res = cres;
                }
            }
        }
    }
 
    delete[] ures;
    delete[] cres;
 
    return res;
}

bool check_dbname(const string dbname) {
    regex word_regex(R"([A-Za-z\_\-0-9]+)");
    if(regex_match(dbname, word_regex)) {
        return true;
    }
    return false;
}
