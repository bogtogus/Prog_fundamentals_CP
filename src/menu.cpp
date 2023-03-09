#include <menu.h>

using namespace std;

void menu(WORKER*& workers_list) {
    bool MenuIsOpen = true;
    bool Inserting = true;
    string* used_files = nullptr;
    string text_command;
    int num_command = 0;
    int index = 0;
    int flag = 0;
    cout << "���� ���������� ��� ������ �� ������� �����������.\n��� ������ ������ ������� /help." << endl << endl;
    while (MenuIsOpen) {
        cout << "������� �������:" << endl;
        getline(cin, text_command);
        Inserting = true;
        switch (command(text_command)) {
        case cmd::Add:
            menu_add(workers_list);
            break;
        case cmd::Delete:
            menu_delete(workers_list);
            break;
        case cmd::Edit:
            menu_edit(workers_list);
            break;
        case cmd::Find:
            menu_find(workers_list);
            break;
        case cmd::Fread:
            menu_fread(workers_list, used_files);
            break;
        case cmd::Fwrite:
            menu_fwrite(workers_list);
            break;
        case cmd::Sort:
            menu_sort(workers_list);
            break;
        case cmd::Task:
            menu_task(workers_list);
            break;
        case cmd::Help:
            menu_help();
            break;
        case cmd::Show:
            menu_show(workers_list);
            break;
        case cmd::Exit:
            MenuIsOpen = false;
            break;
        default:
            cout << "������� �� ����������." << endl;
            break;
        }
        text_command.erase();
    }
    if (used_files != nullptr) {
        delete[] used_files;
    }
    cout << "�����." << endl;
}

void menu_add(WORKER*& workers_list) {
    bool Inserting = true;
    string text_command;
    string temp_fio;
    string temp_post;
    int temp_year = 0;
    int position = 0;
    int flag = 0;
    cout << " � ����������. ";
    while (Inserting) {
        cout << "������� ����� ������� (-1 ��� ������� � ����� ������): " << endl;
        getline(cin, text_command);
        if (to_number(text_command, position) == 0) { // ���� ������� �����
            if (position < 1 && position != -1) {
                cout << "�������� ����� �������. ���������� ������." << endl;
                continue;
            }
        }
        else { // ���� �� �����
            if (text_command == "/back") {
                cout << endl << "����������� � ����. " << endl;
                break;
            }
            else {
                cout << "������ �����. ���������� ������." << endl;
                cin.clear();
                cin.ignore(cin.rdbuf()->in_avail(), '\n');
                continue;
            }
        }
        flag = get_fields(temp_fio, temp_post, temp_year);
        if (!flag && is_exist(workers_list, temp_fio, temp_post, temp_year)) {
            cout << "��������� ��� ����������. ���������� ������ �������." << endl;
            temp_fio.erase();
            temp_post.erase();
            continue;
        }
        else if (flag == 2) {
            cout << endl << "����������� � ����. " << endl;
            break;
        }
        if (position == -1) {
            push_back(workers_list, temp_fio, temp_post, temp_year);
        }
        else {
            push_into(workers_list, position - 1, temp_fio, temp_post, temp_year);
        }
        cout << "��������� ��������." << endl;
        if (_AUTO_OUTPUT) {
            show_list(workers_list);
        }
        break;
    }
    temp_fio.erase();
    temp_post.erase();
}

void menu_delete(WORKER*& workers_list) {
    if (is_list_empty(workers_list)) {
        cout << "������ ����. �������� ���������� ����������. " << endl;
        return;
    }
    bool Inserting = true;
    string temp_fio;
    string temp_post;
    WORKER* found = nullptr;
    int temp_year;
    int position = 0;
    int flag = 0;
    cout << " � ��������. ";
    while (Inserting) {
        cout << "������� ������� � �������� ���������� ����������: " << endl;
        getline(cin, temp_fio);
        if (temp_fio == "/back") {
            cout << endl << "����������� � ����. " << endl;
            break;
        }
        format_fio(temp_fio);
        while (!check_fio(temp_fio)) {
            cout << "������� � �������� ������� �������. ���������� ������:" << endl;
            continue;
        }
        flag = find_in_list(workers_list, temp_fio, found, position);
        if (flag == 1) {
            cout << " [X] ��������� �� ������. ���������� ������ ��� ������� ������� /back." << endl;
            temp_fio.erase();
            temp_post.erase();
            continue;
        }
        else if (flag == 2) {
            cout << "��������� � ����� �������� � ���������� �� ������������.";
            cout << "������� ������ ��� ��������� ����:" << endl;
            get_fields(temp_fio, temp_post, temp_year, gf_flag::SearchAdd);
            flag = find_in_list(workers_list, temp_fio, temp_post, temp_year, found, position);
            if (flag == 1) {
                cout << " [X] ��������� �� ������. ���������� ������ ��� ������� ������� /back." << endl;
                temp_fio.erase();
                temp_post.erase();
                continue;
            }
        }
        pop_from(workers_list, position);
        cout << "��������� �����." << endl;
        if (_AUTO_OUTPUT) {
            show_list(workers_list);
        }
        break;
    }
}

void menu_edit(WORKER*& workers_list) {
    if (is_list_empty(workers_list)) {
        cout << "������ ����. �������������� ���������� ����������. " << endl;
        return;
    }
    bool Inserting = true;
    string temp_fio;
    string temp_post;
    WORKER* found = nullptr;
    int temp_year;
    int flag = 0;
    int position = 0;
    cout << " � ��������������. ";
    while (Inserting) {
        cout << "������� ������� � �������� �������������� ����������: " << endl;
        getline(cin, temp_fio);
        if (temp_fio == "/back") {
            cout << endl << "����������� � ����. " << endl;
            break;
        }
        format_fio(temp_fio);
        if (!check_fio(temp_fio)) {
            cout << "������� � �������� ������� �������. ���������� ������:" << endl;
            continue;
        }
        flag = find_in_list(workers_list, temp_fio, found, position);
        if (flag == 1) {
            cout << " [X] ��������� �� ������. ���������� ������ ��� ������� ������� /back." << endl;
            temp_fio.erase();
            temp_post.erase();
            continue;
        }
        else if (flag == 2) {
            cout << "��������� � ����� �������� � ���������� �� ������������.";
            cout << "������� ������ ��� ��������� ����:" << endl;
            get_fields(temp_fio, temp_post, temp_year, gf_flag::SearchAdd);
            flag = find_in_list(workers_list, temp_fio, temp_post, temp_year, found, position);
            if (flag == 1) {
                cout << " [X] ��������� �� ������. ���������� ������ ��� ������� ������� /back." << endl;
                temp_fio.erase();
                temp_post.erase();
                continue;
            }
        }
        cout << "��������� ������. ������� ����� ������:" << endl;
        temp_fio.erase();
        temp_post.erase();
        get_fields(temp_fio, temp_post, temp_year, gf_flag::Editing);
        if (!is_exist(workers_list, temp_fio, temp_post, temp_year)) {
            found->fio = temp_fio;
            found->post = temp_post;
            found->admission_year = temp_year;
            cout << "��������� ��������������." << endl;
            if (_AUTO_OUTPUT) {
                show_list(workers_list);
            }
        }
        else if (flag == 2) {
            cout << endl << "����������� � ����. " << endl;
            break;
        }
        else if (found->fio == temp_fio && found->post == temp_post && found->admission_year == temp_year) {
            cout << " [X] �������� ����� ������ ���������� ��������� ����������. " << endl;
        }
        else {
            cout << " |\\/| �������� ����� ������ ���������� �� ���������. " << endl;
            cout << " |/\\| �������������� �� ���������. " << endl << endl;
        }
        break;
    }
    temp_fio.erase();
    temp_post.erase();
}

void menu_find(WORKER*& workers_list) {
    if (is_list_empty(workers_list)) {
        cout << "������ ����. ����� ���������� ����������. " << endl;
        return;
    }
    bool Inserting = true;
    bool subInserting = true;
    WORKER* found = nullptr;
    string text_command;
    int command = 0;
    string temp_fio;
    string temp_post;
    int temp_year;
    int flag = 0;
    int index = 0;
    cout << " � ����� ����������. ";
    while (Inserting) {
        cout << "������� ������� � �������� �������� ����������: " << endl;
        getline(cin, temp_fio);
        if (temp_fio == "/back") {
            cout << endl << "����������� � ����. " << endl;
            break;
        }
        format_fio(temp_fio);
        if (!check_fio(temp_fio)) {
            cout << "������� � �������� ������� �������. ���������� ������:" << endl;
            continue;
        }
        flag = find_in_list(workers_list, temp_fio, found, index);
        if (flag == 1) {
            cout << " [X] ��������� �� ������. ���������� ������ ��� ������� ������� /back." << endl;
            temp_fio.erase();
            temp_post.erase();
            continue;
        }
        else if (flag == 2) {
            cout << "��������� � ����� �������� � ���������� �� ������������.";
            cout << "������� ������ ��� ��������� ����:" << endl;
            get_fields(temp_fio, temp_post, temp_year, gf_flag::SearchAdd);
            flag = find_in_list(workers_list, temp_fio, temp_post, temp_year, found, index);
            if (flag == 1) {
                cout << " [X] ��������� �� ������. ���������� ������ ��� ������� ������� /back." << endl;
                temp_fio.erase();
                temp_post.erase();
                continue;
            }
        }
        cout << "��������� ������. ��� ������:" << endl;
        cout << index + 1 << ": " << found->fio << ", " << found->post << ", " << found->admission_year << endl;
        cout << "�������� ���������� �������� : " << endl;
        cout << "1 - �������; 2 - �������������; 3 - ��������� � ����." << endl;
        getline(cin, text_command);
        while (subInserting) {
            if (to_number(text_command, command) == 0) {
                if (command < 1 || command > 3) {
                    cout << "�������� ����� �������. ���������� ������." << endl;
                    getline(cin, text_command);
                    continue;
                }
                break;
            }
            else {
                cout << "������� �� ����������. ���������� ������." << endl;
                getline(cin, text_command);
            }
        }

        switch (command) {
        case 1:
            pop_from(workers_list, index);
            cout << "��������� �����." << endl;
            subInserting = false;
            break;
        case 2: //��������������
            temp_fio.erase();
            temp_post.erase();
            get_fields(temp_fio, temp_post, temp_year, gf_flag::Editing);
            if (!is_exist(workers_list, temp_fio, temp_post, temp_year)) {
                found->fio = temp_fio;
                found->post = temp_post;
                found->admission_year = temp_year;
                cout << "��������� ��������������." << endl << endl;
            }
            else if (found->fio == temp_fio && found->post == temp_post && found->admission_year == temp_year) {
                cout << " [X] �������� ����� ������ ���������� ��������� ����������. " << endl << endl;
            }
            else {
                cout << " |\\/| �������� ����� ������ ���������� �� ���������. " << endl;
                cout << " |/\\| �������������� �� ���������. " << endl << endl;
            }
            subInserting = false;
            break;
        case 3:
            subInserting = false;
            Inserting = false;

            cout << endl << "����������� � ����." << endl;
            break;
        default:
            break;
        }
        
        break;
    }
    temp_fio.erase();
    temp_post.erase();
}

void menu_fread(WORKER*& workers_list, string*& used_files) {
    bool Inserting = true;
    bool subInserting = true;
    bool file_used = false;
    string text_command;
    int command=0;
    string path;
    string file;
    size_t firstchar = 0;
    size_t secondchar = 0;
    int flag = 0;
    cout << " � ������ �� �����. ";
    while (Inserting) {
        cout << "������� �������� ����� ��� ������ ���� � �����: " << endl;
        getline(cin, path);
        if (path == "/back") {
            cout << endl << "����������� � ����. " << endl;
            break;
        }
        else if (strcmp(path.c_str(), " ") == 0 || strcmp(path.c_str(), "\n") == 0 || strcmp(path.c_str(), "") == 0) {
            cout << " [X] ������� ������ ������. ���������� ������." << endl;
            continue;
        }
        size_t replpos=0;
        while ((replpos = path.find('\\', replpos)) != string::npos) {
            path.replace(replpos, 1, "/");
            replpos++;
        }
        if (path.rfind('/') != string::npos) { // ��������� �������� �����
            file = path.substr(path.rfind('/') + 1, string::npos);
        }
        else {
            file = path;
        }
        if (file.find('.') == string::npos) { // ���� ���� ��� �������� ����������
            file = file + ".txt";
            path = path + ".txt";
        }
        if (!file_valid(path)) {
            cout << " |\\/| ������ ������ �� �����. ������� ������ ���� � �����." << endl;
            cout << " |/\\| ���������� ������: ";
            path.erase();
            file.erase();
            continue;
        }
        if (check_if_used(used_files, file)) {
            cout << "���� � ����� ��������� ��� ��� �������� �����. ����������� ���������� ������ � ���?" << endl;
            cout << "(1 - �����������, 2 - ��������)" << endl;
            getline(cin, text_command);
            while (subInserting) {
                if (to_number(text_command, command) == 0) {
                    if (command < 1 || command > 2) {
                        cout << "�������� ����� �������. ���������� ������." << endl;
                        getline(cin, text_command);
                        continue;
                    }
                    break;
                }
                else {
                    cout << "������� �� ����������. ���������� ������." << endl;
                    getline(cin, text_command);
                }
            }
            if (command == 1) {
                file_used = true;
            }
            else if (command == 2) {
                continue;
            }
        }
        cout << "1 - �������� ������ � ����� ������; " << endl;
        cout << "2 - �������� ������ �� ������ �� �����; " << endl;
        cout << "3 - �������� ���� � �����; " << endl;
        cout << "4 - �������� ������ �����. " << endl;
        cin.ignore(cin.rdbuf()->in_avail(), '\n');
        getline(cin, text_command);
        while (subInserting) {
            if (to_number(text_command, command) == 0) {
                if (command < 1 || command > 4) {
                    cout << "�������� ����� �������. ���������� ������." << endl;
                    getline(cin, text_command);
                    continue;
                }
                break;
            }
            else {
                cout << "������� �� ����������. ���������� ������." << endl;
                getline(cin, text_command);
            }
        }
        switch (command) {
        case 1: //� �����
            break;
        case 2: //��������
            clear_list(workers_list);
            break;
        case 3: //�������� ����
            cout << endl << "�������� ���� � �����: " << endl;
            break;
        case 4:
            cout << endl << "����������� � ����. " << endl;
            Inserting = false;
            break;
        default:
            cout << "������� �� ����������. ���������� ������." << endl;
            break;
        }
        if (!Inserting && command == 4) break;
        else if (command == 3) continue;
        
        int flag = 0;
        flag = fread_list(workers_list, path);
        if (flag == 0) {
            cout << "������ ���� ���������." << endl;
            if (!file_used) {
                push_back(used_files, file);
            }
            if (_AUTO_OUTPUT) {
                show_list(workers_list);
            }
        }
        else if (flag == 2) {
            cout << " |\\/| ��� ������, �������� � �����, �� ������������� �������," << endl;
            cout << " |/\\| ��� ��������� ������������. ������ �� �����������. " << endl;
        }
        else if (flag == 1) {
            cout << " [X] �� ������� ������� ����. " << endl;
        }
        
        break;
    }
    path.erase();
}

void menu_fwrite(WORKER*& workers_list) {
    if (is_list_empty(workers_list)) {
        cout << "������ ����. ���������� ������ ���������� � ���� �� �����������. " << endl;
        return;
    }
    bool Inserting = true;
    string path;
    bool existing = false;
    int flag = 0;
    cout << " � ������ � ����. ";
    while (Inserting) {
        cout << "������� �������� ����� ��� ������ ���� � �����: " << endl;
        getline(cin, path);
        if (path == "/back") {
            cout << endl << "����������� � ����. " << endl;
            break;
        }
        else if (strcmp(path.c_str(), " ") == 0 || strcmp(path.c_str(), "\n") == 0 || strcmp(path.c_str(), "") == 0) {
            cout << " [X] ������� ������ ������. ���������� ������." << endl;
            continue;
        }
        size_t replpos = 0;
        while ((replpos = path.find('\\', replpos)) != string::npos) {
            path.replace(replpos, 1, "/");
            replpos++;
        }
        if (path.find('.') == string::npos) {
            path = path + ".txt";
        }
        existing = file_valid(path);
        flag = fwrite_list(workers_list, path);
        while (flag) {
            cout << " [X] ������ ������ � ����. ";
            if (flag == 1) {
                cout << "������� ������ ���� � �����." << endl;
            }
            cout << "���������� ������: " << endl;
            getline(cin, path);
            if (path == "/back") {
                cout << endl << "����������� � ����. " << endl;
                break;
            }
            if (path.find('.') == string::npos) {
                path = path + ".txt";
            }
            existing = file_valid(path);
            flag = fwrite_list(workers_list, path);
        }
        if (!flag) {
            if (!existing) {
                cout << "���� ������. ";
            }
            cout << "������ �����������." << endl;
        }
        path.erase();
        break;
    }
}

void menu_sort(WORKER*& workers_list) {
    if (is_list_empty(workers_list)) {
        cout << "������ ����. ���������� �� �����������. " << endl;
        return;
    }
    bool subInserting = true;
    string text_command;
    int command_1 = 0;
    int command_2 = 0;
    bool Direction = true; //true - �����������, false - ��������
    cout << " � ���������� ������. " << endl;
    cout << "1 - ���������� �� ������� � ���������; " << endl;
    cout << "2 - ���������� �� ���������; " << endl;
    cout << "3 - ���������� �� ���� ���������������; " << endl;
    cout << "4 - ������." << endl;
    cin.ignore(cin.rdbuf()->in_avail(), '\n');
    getline(cin, text_command);
    while (subInserting) { // ���� ������ �������
        if (text_command == "/back") {
            cout << "����������� � ����. " << endl;
            return;
        }
        else if (to_number(text_command, command_1) == 0) {
            if (command_1 < 1 || command_1 > 4) {
                cout << "�������� ����� �������. ���������� ������." << endl;
                getline(cin, text_command);
                continue;
            }
            break;
        }
        else {
            cout << "������� �� ����������. ���������� ������." << endl;
            getline(cin, text_command);
        }
    }
    if (command_1 == 4) {
        cout << "����������� � ����. " << endl;
        return;
    }
    cout << "1 - ���������� �� �����������(��� �� ��������); " << endl;
    cout << "2 - ���������� �� ��������; " << endl;
    cin.ignore(cin.rdbuf()->in_avail(), '\n');
    getline(cin, text_command);
    while (subInserting) { // ���� ������ �������
        if (to_number(text_command, command_2) == 0) {
            if (command_2 < 1 || command_2 > 2) {
                cout << "�������� ����� �������. ���������� ������." << endl;
                getline(cin, text_command);
                continue;
            }
            break;
        }
        else {
            cout << "������� �� ����������. ���������� ������." << endl;
            getline(cin, text_command);
        }
    }
    if (command_2 == 1) Direction = true;
    else if (command_2 == 2) Direction = false;

    switch (command_1) {
    case 1: 
        sort_list_byfio(workers_list, Direction);
        break;
    case 2:
        sort_list_bypost(workers_list, Direction);
        break;
    case 3:
        sort_list_byyear(workers_list, Direction);
        break;
    case 4:
        cout << "����������� � ����. " << endl;
        break;
    }
    if (command_1 == 4) return;

    if (check_list_accuracy(workers_list)) {
        cout << "������ ������������. " << endl;
    }
    else {
        cout << " [X] �������� ��������� ������." << endl;
    }
    if (_AUTO_OUTPUT) {
        show_list(workers_list);
    }
}

void menu_task(WORKER*& workers_list) {
    if (is_list_empty(workers_list)) {
        cout << "������ ����. ���������� ������ ����������. " << endl;
        return;
    }
    WORKER* found_workers = nullptr;
    string text_command;
    int year = 0;
    bool subInserting = true;
    cout << " � ����� ��������� � ������� ������ ������. " << endl;
    cout << " � ������� ������������ ���� ������: " << endl;
    while (subInserting) {
        getline(cin, text_command);
        if (to_number(text_command, year)) {
            if (text_command == "/back") {
                cout << "����������� � ����. " << endl;
                return;
            }
            cout << "��� ������ ���� ������. ���������� ������." << endl;
            continue;
        }
        else if (year > 100) {
            cout << "��� ������ ���� ���������. ���������� ������." << endl;
            continue;
        }
        else {
            break;
        }
    }
    found_workers = dotask_list(workers_list, year);
    if (found_workers != nullptr) {
        cout << "������ �������� �������: " << endl;
        show_list(found_workers);
        clear_list(found_workers);
    }
    else {
        cout << " [X] �� ���� ������� �� ������������� �������. " << endl;
    }
}

void menu_show(WORKER* workers_list) {
    if (!is_list_empty(workers_list)) {
        cout << " � ������: " << endl;
        show_list(workers_list);
    }
    else {
        cout << "������ ����. " << endl;
    }
}

void menu_help() {
    cout << endl << setw(44) << right << "**** ������ �� �������� ****" << endl << endl;
    cout << "/add - �������� ���������� � �������. ��������� �������:" << endl;
    cout << setw(5) << ' ' << setw(1) << "<����� �������> - �������� �� �������;" << endl;
    cout << setw(5) << ' ' << setw(1) << "������� -1 ��������� � �����." << endl;
    cout << endl;
    cout << "/delete - ������� ����������. ��������� �������:" << endl;
    cout << setw(5) << ' ' << setw(1) << "<����� �������> - ������� �� ���� �������;" << endl;
    cout << setw(5) << ' ' << setw(1) << "������� -1 ������� �� �����." << endl;
    cout << endl;
    cout << "/edit - ������������� ����������. ��������� �������: " << endl;
    cout << setw(5) << ' ' << setw(1) << "<����� �������>." << endl;
    cout << endl;
    cout << "/fread - ������� ������ ����������� �� �����. ��������� �������: " << endl;
    cout << setw(5) << ' ' << setw(1) << "<���� � �����>." << endl;
    cout << endl;
    cout << "/fwrite - �������� ������ ����������� � ����. ��������� �������: " << endl;
    cout << setw(5) << ' ' << setw(1) << "<���� � �����>." << endl;
    cout << endl;
    cout << "/sort - ���������� ������ �����������. ��������� �������: " << endl;
    cout << setw(5) << ' ' << setw(1) << "<���� ����������>." << endl;
    cout << setw(5) << ' ' << setw(1) << "<����������� ����������>." << endl;
    cout << endl;
    cout << "/find - ����� ����������. ��������� �������: " << endl;
    cout << setw(5) << ' ' << setw(1) << "<������ ����������>." << endl;
    cout << endl;
    cout << "/task - ����� ����������� � ������� ����� ���������������." << endl;
    cout << setw(5) << ' ' << setw(1) << "<��� ���������������>." << endl;
    cout << endl;
    cout << "/show - ����� ������ ����������� � �������." << endl;
    cout << endl;
    cout << "/back - ����������� � ����. ����� ������������ ������" << endl;
    cout << setw(5) << ' ' << setw(1) << "����� ����� ������ ������ ������." << endl;
    cout << endl;
    cout << "/help - ������." << endl;
    cout << endl;
    cout << "/exit - ���������� ������." << endl << endl;
    cout << "������ ����� ��� (�_� ��� ������):" << endl;
    cout << setw(5) << ' ' << setw(1) << "�������_�.�." << endl;
    cout << setw(5) << ' ' << setw(1) << "�������_�._�." << endl;
    cout << setw(5) << ' ' << setw(1) << "�������_�." << endl;
    cout << "��� ������ ���� � ��������� [1900; ��������]." << endl;
}
