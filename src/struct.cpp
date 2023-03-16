#include <struct.h>
#include <functions.h>
using namespace std;

void push_back(WORKER*& head, string fio, string post, const int admission_year) {
    WORKER* p = new WORKER{fio, post, admission_year, nullptr, nullptr};
    WORKER* current = head;
    if (head == nullptr) {
        head = p;
    }
    else {
        while (current->next_elem != nullptr) {
            current = current->next_elem;
        }
        p->prev_elem = current;
        current->next_elem = p;
    }
}

void push_back(WORKER*& head, WORKER* const worker) {
    WORKER* p = new WORKER{ worker->fio, worker->post, worker->admission_year, nullptr, nullptr };
    WORKER* current = head;
    if (head == nullptr) {
        head = p;
    }
    else {
        while (current->next_elem != nullptr) {
            current = current->next_elem;
        }
        p->prev_elem = current;
        current->next_elem = p;
    }
}

int push_into(WORKER*& head, const int index, string fio, string post, const int admission_year) {
    WORKER* p = new WORKER{fio, post, admission_year, nullptr, nullptr};
    WORKER* current = head;
    if (head == nullptr) {
        head = p;
    }
    else if (index < 0) {
        return 1;
    }
    else if (index==0) {
        head->prev_elem = p;
        p->next_elem = head;
        head = p;
    }
    else {
        int i=0;
        while (i < index - 1 && current->next_elem != nullptr) {
            current = current->next_elem;
            i++;
        }
        if (current->next_elem == nullptr) {
            p->prev_elem = current;
            current->next_elem = p;
        }
        else {
            p->prev_elem = current;
            p->next_elem = current->next_elem;
            current->next_elem = p;
        }
    }
    return 0;
}

void pop_back(WORKER*& head) {
    WORKER* current = head;
    if (head == nullptr) {
        return;
    }
    else if (head->next_elem == nullptr) {
        delete head;
        head = nullptr;
    }
    else {
        while (current->next_elem->next_elem != nullptr) {
            current = current->next_elem;
        }
        delete current->next_elem;
        current->next_elem = nullptr;
    }
}

void pop_from(WORKER*& head, const int index) {
    WORKER* current = head;
    WORKER* new_next = nullptr;
    if (head == nullptr) {
        return;
    }
    else if (head->next_elem == nullptr) {
        delete head;
        head = nullptr;
    }
    else if (index == 0) {
        new_next = head->next_elem;
        delete head;
        new_next->prev_elem = nullptr;
        head = new_next;
    }
    else {
        int i = 0;
        while (i < index - 1 && current->next_elem != nullptr) {
            current = current->next_elem;
            i++;
        }
        if (current->next_elem == nullptr) {
            current = current->prev_elem;
            delete current->next_elem;
            current->next_elem = nullptr;
        }
        else {
            new_next = (current->next_elem)->next_elem;
            delete current->next_elem;
            if (new_next != nullptr) {
                new_next->prev_elem = current;
            }
            current->next_elem = new_next;
        }
    }
}

void show_list(WORKER* const head) {
    WORKER* current = head;
    int iw = 3; //ширина позиции
    int nw = 25; //ширина имени
    int pw = 25; //ширина должности
    int dw = 10; //ширина года
    int position = 1;
    if (head == nullptr) {
        return;
    }
    else {
        cout << setw(iw)  << "№"         << setw(1) << "|";
        cout << setw(nw) << "ФИО"        << setw(1) << "|";
        cout << setw(pw) << "Должность"  << setw(1) << "|";
        cout << setw(dw) << "Трудоустр." << setw(1) << "|" << endl;
        cout << "---+-------------------------+-------------------------+----------+" << endl;
        while (current != nullptr) {
            cout << setw(iw)  << position                   << setw(1) << "|";
            cout << setw(nw) << current->fio.substr(0, 25)  << setw(1) << "|";
            cout << setw(pw) << current->post.substr(0, 25) << setw(1) << "|";
            cout << setw(dw) << current->admission_year     << setw(1) << "|" << endl;
            cout << "---+-------------------------+-------------------------+----------+" << endl;
            current = current->next_elem;
            position++;
        }
    }
}

void clear_list(WORKER*& head) {
    WORKER* nexthead = head;
    if (head == nullptr) {
        return;
    }
    else {
        while (nexthead != nullptr) {
            nexthead = head->next_elem;
            delete head;
            head = nexthead;
        }
    }
    head = nullptr;
}

bool is_list_empty(WORKER* const head) {
    return (bool)(head == nullptr);
}

int fread_list(WORKER*& head, string path) {
    ifstream file;
    string fio;
    string post;
    string year;
    int adm_year=0;
    bool something_red = false;
    file.open(path);
    if (!file.is_open()) {
        file.close();
        return 1;
    }
    while (!file.eof()) {
        getline(file, fio);
        if (fio == "" || fio == "@") {
            continue;
        }
        if (!file.eof() && file.good()) {
            getline(file, post);
            if (post == "" || post == "@") {
                continue;
            }
            if (!file.eof() && file.good()) {
                getline(file, year);
                if (year == "" || year == "@") {
                    continue;
                }
                if (!file.fail() && !file.bad()) {
                    try {
                        adm_year = stoi(year);
                        format_fio(fio);
                        format_post(post);
                        if (!check_fio(fio)) {
                            throw std::invalid_argument("FIO is incorrect.");
                        }
                        else if (!check_post(post)) {
                            throw std::invalid_argument("Post is incorrect.");
                        }
                        else if (!check_year(adm_year)) {
                            throw std::invalid_argument("Year is incorrect.");
                        }
                        else if (is_exist(head, fio, post, adm_year)) {
                            throw std::invalid_argument("Already exists.");
                        }
                        push_back(head, fio, post, adm_year);
                        if (!something_red) something_red = true;
                    }
                    catch (std::invalid_argument) {
                        file.clear();
                        file.ignore(file.rdbuf()->in_avail(), '@');
                        continue;
                    }
                }
                else {
                    file.clear();
                    file.ignore(file.rdbuf()->in_avail(), '@');
                    continue;
                }
            }
            else {
                file.clear();
                file.ignore(file.rdbuf()->in_avail(), '@');
                continue;
            }
        }
        else {
            file.clear();
            file.ignore(file.rdbuf()->in_avail(), EOF);
            break;
        }
    }
    file.close();
    fio.erase();
    post.erase();
    year.erase();
    if (!something_red) {
        return 2;
    }
    return 0;
}

int fwrite_list(WORKER* const head, string path) {
    ofstream file;
    WORKER* current = head;
    file.open(path, ios_base::out | ios_base::trunc);
    if (!file.is_open()) {
        return 1;
    }
    while (current != nullptr) {
        file << current->fio << '\n' << current->post << '\n' << current->admission_year << '\n';
        current = current->next_elem;
        if (current != nullptr) {
            file << "@\n";
        }
    }
    file.close();
    return 0;
}

int dbwrite_list(WORKER* const head, sqlite3*& dbase, bool opened) {
    int flag = 0;
    char* error = nullptr;  
    WORKER* current = head;
    string fio;
    string post;
    string year;
    string sqlstatement;
    if (!opened) {
        return 1;
    }
    while (current != nullptr) {
        fio = current->fio;
        post = current->post;
        try {
            year = to_string(current->admission_year);
        } catch (invalid_argument) {
            current = current->next_elem;
            continue;
        }
        sqlstatement = (string)"INSERT INTO workers " + "(fio, post, [admission year])" + 
            " VALUES (\'" + cp1251_to_utf8(fio) + "\', \'" + cp1251_to_utf8(post) + "\', " + cp1251_to_utf8(year) + ")";
        //cout << sqlstatement << endl;
        flag = sqlite3_exec(dbase, sqlstatement.c_str(), 
                            nullptr, nullptr, &error);
        if (flag != SQLITE_OK) {
            // !
        }
        current = current->next_elem;
        
    }
    sqlite3_close_v2(dbase);
    return 0;
}

int find_in_list(WORKER* const head, string name, WORKER*& found, int& index) {
    name = ltrim(rtrim(name));
    WORKER* current = head;
    int coincidences = 0;
    int i = 0;
    int indx = 0;
    while (current != nullptr) {
        if (strcmp(current->fio.c_str(), name.c_str()) == 0) {
            found = current;
            indx = i;
            coincidences++;
        }
        current = current->next_elem;
        i++;
    }
    if (coincidences == 0) {
        return 1;
    }
    else if (coincidences > 1) {
        return 2;
    }
    index = indx;
    return 0;
}

int find_in_list(WORKER* const head, string name, string post, const int adm_year, WORKER*& found, int& index) {
    string sname = ltrim(rtrim(name));
    format_fio(sname);
    WORKER* current = head;
    int coincidences = 0;
    int indx = 0;
    while (current != nullptr) {
        if (strcmp(current->fio.c_str(), sname.c_str()) == 0 &&
            strcmp(current->post.c_str(), post.c_str()) == 0 &&
            current->admission_year == adm_year) {
            break;
        }
        current = current->next_elem;
        indx++;
    }
    if (current == nullptr) {
        return 1;
    }
    found = current;
    index = indx;
    return 0;
}

bool is_exist(WORKER* const head, const string name, const string post, const int adm_year) {
    string temp_name = ltrim(rtrim(name));
    string temp_post = ltrim(rtrim(post));
    string cur_post;
    downcase_word(temp_post);
    WORKER* current = head;
    while (current != nullptr) {
        cur_post = current->post;
        downcase_word(cur_post);
        if (strcmp(current->fio.c_str(), temp_name.c_str()) == 0 &&
            strcmp(cur_post.c_str(), temp_post.c_str()) == 0 &&
            current->admission_year == adm_year) {
            return true;
        }
        current = current->next_elem;
    }
    return false;
}

void sort_list_byfio(WORKER*& head, bool Direction) {
    WORKER* current = nullptr;
    WORKER* previous = nullptr;
    bool swap = false;
    int name_to_name = 0;
    int post_to_post = 0;
    int year_to_year = 0;
    if (head == nullptr) {
        return;
    }
    else if (head->next_elem == nullptr) {
        return;
    }
    else {
        previous = head;
        current = head->next_elem;
        while (current != nullptr) {
            name_to_name = strcmp(current->fio.c_str(), previous->fio.c_str());

            // if current FIO is smaller(1)/bigger(0) than previous
            if (name_to_name != 0 && (name_to_name < 0) == Direction) {
                swap_elements(head, previous, current);
                swap = true;
            }
            else if (name_to_name == 0) {
                post_to_post = strcmp(current->post.c_str(), previous->post.c_str());

                // if current POST is smaller(1)/bigger(0) than previous
                if (post_to_post != 0 && (post_to_post < 0) == Direction) {
                    swap_elements(head, previous, current);
                    swap = true;
                }
                else if (post_to_post == 0) {
                    year_to_year = (current->admission_year == previous->admission_year) ? 0 :
                        ((current->admission_year > previous->admission_year) ? 1 : -1);

                    // if current YEAR is smaller(1)/bigger(0) than previous
                    if (year_to_year != 0 && (year_to_year < 0) == Direction) {
                        swap_elements(head, previous, current);
                        swap = true;
                    }
                    else {
                        previous = current;
                        current = current->next_elem;
                    }
                }
                else {
                    previous = current;
                    current = current->next_elem;
                }
            }
            else { //if elements are placed correctly
                previous = current;
                current = current->next_elem;
            }
            if (current == nullptr) { // if end is reached
                if (swap) { // if there was swapping
                    swap = false;
                }
                else {
                    break;
                }
                previous = head;
                current = head->next_elem;
            }
        }
    }
}

void sort_list_bypost(WORKER*& head, bool Direction) {
    WORKER* current = nullptr;
    WORKER* previous = nullptr;
    bool swap = false;
    int name_to_name = 0;
    int post_to_post = 0;
    int year_to_year = 0;
    if (head == nullptr) {
        return;
    }
    else if (head->next_elem == nullptr) {
        return;
    }
    else {
        previous = head;
        current = head->next_elem;
        while (current != nullptr) {
            post_to_post = strcmp(current->post.c_str(), previous->post.c_str());

            // if current POST is smaller(1)/bigger(0) than previous
            if (post_to_post != 0 && (post_to_post < 0) == Direction) {
                swap_elements(head, previous, current);
                swap = true;
            }
            else if (post_to_post == 0) {
                name_to_name = strcmp(current->fio.c_str(), previous->fio.c_str());

                // if current FIO is smaller(1)/bigger(0) than previous
                if (name_to_name != 0 && (name_to_name < 0) == Direction) {
                    swap_elements(head, previous, current);
                    swap = true;
                }
                else if (name_to_name == 0) {
                    year_to_year = (current->admission_year == previous->admission_year) ? 0 :
                        ((current->admission_year > previous->admission_year) ? 1 : -1);

                    // if current YEAR is smaller(1)/bigger(0) than previous
                    if (year_to_year != 0 && (year_to_year < 0) == Direction) {
                        swap_elements(head, previous, current);
                        swap = true;
                    }
                    else {
                        previous = current;
                        current = current->next_elem;
                    }
                }
                else {
                    previous = current;
                    current = current->next_elem;
                }
            }
            else { //if elements are placed correctly
                previous = current;
                current = current->next_elem;
            }
            if (current == nullptr) { // if end is reached
                if (swap) { // if there was swapping
                    swap = false;
                }
                else {
                    break;
                }
                previous = head;
                current = head->next_elem;
            }
        }
    }
}

void sort_list_byyear(WORKER*& head, bool Direction) {
    WORKER* current = nullptr;
    WORKER* previous = nullptr;
    bool swap = false;
    int name_to_name = 0;
    int post_to_post = 0;
    int year_to_year = 0;
    if (head == nullptr) {
        return;
    }
    else if (head->next_elem == nullptr) {
        return;
    }
    else {
        previous = head;
        current = head->next_elem;
        while (current != nullptr) {
            year_to_year = (current->admission_year == previous->admission_year) ? 0 :
                ((current->admission_year > previous->admission_year) ? 1 : -1);

            // if current YEAR is smaller(1)/bigger(0) than previous
            if (year_to_year != 0 && (year_to_year < 0) == Direction) {
                swap_elements(head, previous, current);
                swap = true;
            }
            else if (year_to_year == 0) {
                name_to_name = strcmp(current->fio.c_str(), previous->fio.c_str());

                // if current FIO is smaller(1)/bigger(0) than previous
                if (name_to_name != 0 && (name_to_name < 0) == Direction) {
                    swap_elements(head, previous, current);
                    swap = true;
                }
                else if (name_to_name == 0) {
                    // if current POST is smaller than previous
                    if (post_to_post != 0 && (post_to_post < 0) == Direction) {
                        swap_elements(head, previous, current);
                        swap = true;
                    }
                    else {
                        previous = current;
                        current = current->next_elem;
                    }
                }
                else {
                    previous = current;
                    current = current->next_elem;
                }
            }
            else { //if elements are placed correctly
                previous = current;
                current = current->next_elem;
            }
            if (current == nullptr) { // if end is reached
                if (swap) { // if there was swapping
                    swap = false;
                }
                else {
                    break;
                }
                previous = head;
                current = head->next_elem;
            }
        }
    }
}

void swap_elements(WORKER*& head, WORKER*& previous, WORKER*& current) {
    previous->next_elem = current->next_elem;
    current->prev_elem = previous->prev_elem;
    previous->prev_elem = current;
    current->next_elem = previous;
    if (previous->next_elem != nullptr) {
        (previous->next_elem)->prev_elem = previous;
    }
    if (current->prev_elem == nullptr) {
        head = current;
    }
    else {
        (current->prev_elem)->next_elem = current;
    }
    current = previous->next_elem;
}

bool check_list_accuracy(WORKER* const head) {
    WORKER* current = head;
    if (head == nullptr) {
        return true;
    }
    else if (head->next_elem == nullptr) {
        if (head->prev_elem == nullptr) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        if ((head->next_elem)->prev_elem != head) {
            return false;
        }
        current = current->next_elem;
        while (current->next_elem != nullptr) {
            if (current->prev_elem == nullptr || (current->prev_elem)->next_elem != current) {
                return false;
            }
            current = current->next_elem;
        }
    }
    return true;
}

WORKER* dotask_list(WORKER* const head, const int year) {
    WORKER* found_workers = nullptr;
    WORKER* current = head;
    struct tm date;
    _putenv("TZ=Europe/Moscow");
    time_t t = time(NULL);
    gmtime_s(&date , &t);
    int currentdate = 1900 + date.tm_year;

    if (head == nullptr) {
        return nullptr;
    }
    else {
        while (current != nullptr) {
            if (currentdate - current->admission_year > year) {
                push_back(found_workers, current);
            }
            current = current->next_elem;
        }
    }
    return found_workers;
}
