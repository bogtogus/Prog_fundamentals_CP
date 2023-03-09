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
    cout << "Меню приложения для работы со списком сотрудников.\nДля списка команд введите /help." << endl << endl;
    while (MenuIsOpen) {
        cout << "Введите команду:" << endl;
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
            cout << "Команда не распознана." << endl;
            break;
        }
        text_command.erase();
    }
    if (used_files != nullptr) {
        delete[] used_files;
    }
    cout << "Выход." << endl;
}

void menu_add(WORKER*& workers_list) {
    bool Inserting = true;
    string text_command;
    string temp_fio;
    string temp_post;
    int temp_year = 0;
    int position = 0;
    int flag = 0;
    cout << " • Добавление. ";
    while (Inserting) {
        cout << "Введите номер позиции (-1 для вставки в конец списка): " << endl;
        getline(cin, text_command);
        if (to_number(text_command, position) == 0) { // если введено число
            if (position < 1 && position != -1) {
                cout << "Неверный номер позиции. Попробуйте заново." << endl;
                continue;
            }
        }
        else { // если не число
            if (text_command == "/back") {
                cout << endl << "Возвращение в меню. " << endl;
                break;
            }
            else {
                cout << "Ошибка ввода. Попробуйте заново." << endl;
                cin.clear();
                cin.ignore(cin.rdbuf()->in_avail(), '\n');
                continue;
            }
        }
        flag = get_fields(temp_fio, temp_post, temp_year);
        if (!flag && is_exist(workers_list, temp_fio, temp_post, temp_year)) {
            cout << "Сотрудник уже существует. Попробуйте ввести другого." << endl;
            temp_fio.erase();
            temp_post.erase();
            continue;
        }
        else if (flag == 2) {
            cout << endl << "Возвращение в меню. " << endl;
            break;
        }
        if (position == -1) {
            push_back(workers_list, temp_fio, temp_post, temp_year);
        }
        else {
            push_into(workers_list, position - 1, temp_fio, temp_post, temp_year);
        }
        cout << "Сотрудник добавлен." << endl;
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
        cout << "Список пуст. Удаление работников невозможно. " << endl;
        return;
    }
    bool Inserting = true;
    string temp_fio;
    string temp_post;
    WORKER* found = nullptr;
    int temp_year;
    int position = 0;
    int flag = 0;
    cout << " • Удаление. ";
    while (Inserting) {
        cout << "Введите фамилию и инициалы удаляемого сотрудника: " << endl;
        getline(cin, temp_fio);
        if (temp_fio == "/back") {
            cout << endl << "Возвращение в меню. " << endl;
            break;
        }
        format_fio(temp_fio);
        while (!check_fio(temp_fio)) {
            cout << "Фамилия и инициалы введены неверно. Попробуйте заново:" << endl;
            continue;
        }
        flag = find_in_list(workers_list, temp_fio, found, position);
        if (flag == 1) {
            cout << " [X] Сотрудник не найден. Попробуйте заново или введите команду /back." << endl;
            temp_fio.erase();
            temp_post.erase();
            continue;
        }
        else if (flag == 2) {
            cout << "Сотрудник с такой фамилией и инициалами не единственный.";
            cout << "Введите данные для уточнения ниже:" << endl;
            get_fields(temp_fio, temp_post, temp_year, gf_flag::SearchAdd);
            flag = find_in_list(workers_list, temp_fio, temp_post, temp_year, found, position);
            if (flag == 1) {
                cout << " [X] Сотрудник не найден. Попробуйте заново или введите команду /back." << endl;
                temp_fio.erase();
                temp_post.erase();
                continue;
            }
        }
        pop_from(workers_list, position);
        cout << "Сотрудник удалён." << endl;
        if (_AUTO_OUTPUT) {
            show_list(workers_list);
        }
        break;
    }
}

void menu_edit(WORKER*& workers_list) {
    if (is_list_empty(workers_list)) {
        cout << "Список пуст. Редактирование работников невозможно. " << endl;
        return;
    }
    bool Inserting = true;
    string temp_fio;
    string temp_post;
    WORKER* found = nullptr;
    int temp_year;
    int flag = 0;
    int position = 0;
    cout << " • Редактирование. ";
    while (Inserting) {
        cout << "Введите Фамилию и инициалы редактируемого сотрудника: " << endl;
        getline(cin, temp_fio);
        if (temp_fio == "/back") {
            cout << endl << "Возвращение в меню. " << endl;
            break;
        }
        format_fio(temp_fio);
        if (!check_fio(temp_fio)) {
            cout << "Фамилия и инициалы введены неверно. Попробуйте заново:" << endl;
            continue;
        }
        flag = find_in_list(workers_list, temp_fio, found, position);
        if (flag == 1) {
            cout << " [X] Сотрудник не найден. Попробуйте заново или введите команду /back." << endl;
            temp_fio.erase();
            temp_post.erase();
            continue;
        }
        else if (flag == 2) {
            cout << "Сотрудник с такой фамилией и инициалами не единственный.";
            cout << "Введите данные для уточнения ниже:" << endl;
            get_fields(temp_fio, temp_post, temp_year, gf_flag::SearchAdd);
            flag = find_in_list(workers_list, temp_fio, temp_post, temp_year, found, position);
            if (flag == 1) {
                cout << " [X] Сотрудник не найден. Попробуйте заново или введите команду /back." << endl;
                temp_fio.erase();
                temp_post.erase();
                continue;
            }
        }
        cout << "Сотрудник найден. Введите новые данные:" << endl;
        temp_fio.erase();
        temp_post.erase();
        get_fields(temp_fio, temp_post, temp_year, gf_flag::Editing);
        if (!is_exist(workers_list, temp_fio, temp_post, temp_year)) {
            found->fio = temp_fio;
            found->post = temp_post;
            found->admission_year = temp_year;
            cout << "Сотрудник отредактирован." << endl;
            if (_AUTO_OUTPUT) {
                show_list(workers_list);
            }
        }
        else if (flag == 2) {
            cout << endl << "Возвращение в меню. " << endl;
            break;
        }
        else if (found->fio == temp_fio && found->post == temp_post && found->admission_year == temp_year) {
            cout << " [X] Введённые новые данные сотрудника идентичны предыдущим. " << endl;
        }
        else {
            cout << " |\\/| Введённые новые данные сотрудника не уникальны. " << endl;
            cout << " |/\\| Редактирование не выполнено. " << endl << endl;
        }
        break;
    }
    temp_fio.erase();
    temp_post.erase();
}

void menu_find(WORKER*& workers_list) {
    if (is_list_empty(workers_list)) {
        cout << "Список пуст. Поиск работников невозможен. " << endl;
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
    cout << " • Поиск сотрудника. ";
    while (Inserting) {
        cout << "Введите Фамилию и инициалы искомого сотрудника: " << endl;
        getline(cin, temp_fio);
        if (temp_fio == "/back") {
            cout << endl << "Возвращение в меню. " << endl;
            break;
        }
        format_fio(temp_fio);
        if (!check_fio(temp_fio)) {
            cout << "Фамилия и инициалы введены неверно. Попробуйте заново:" << endl;
            continue;
        }
        flag = find_in_list(workers_list, temp_fio, found, index);
        if (flag == 1) {
            cout << " [X] Сотрудник не найден. Попробуйте заново или введите команду /back." << endl;
            temp_fio.erase();
            temp_post.erase();
            continue;
        }
        else if (flag == 2) {
            cout << "Сотрудник с такой фамилией и инициалами не единственный.";
            cout << "Введите данные для уточнения ниже:" << endl;
            get_fields(temp_fio, temp_post, temp_year, gf_flag::SearchAdd);
            flag = find_in_list(workers_list, temp_fio, temp_post, temp_year, found, index);
            if (flag == 1) {
                cout << " [X] Сотрудник не найден. Попробуйте заново или введите команду /back." << endl;
                temp_fio.erase();
                temp_post.erase();
                continue;
            }
        }
        cout << "Сотрудник найден. Его данные:" << endl;
        cout << index + 1 << ": " << found->fio << ", " << found->post << ", " << found->admission_year << endl;
        cout << "Выберите дальнейшее действие : " << endl;
        cout << "1 - удалить; 2 - редактировать; 3 - вернуться в меню." << endl;
        getline(cin, text_command);
        while (subInserting) {
            if (to_number(text_command, command) == 0) {
                if (command < 1 || command > 3) {
                    cout << "Неверный номер команды. Попробуйте заново." << endl;
                    getline(cin, text_command);
                    continue;
                }
                break;
            }
            else {
                cout << "Команда не распознана. Попробуйте заново." << endl;
                getline(cin, text_command);
            }
        }

        switch (command) {
        case 1:
            pop_from(workers_list, index);
            cout << "Сотрудник удалён." << endl;
            subInserting = false;
            break;
        case 2: //редактирование
            temp_fio.erase();
            temp_post.erase();
            get_fields(temp_fio, temp_post, temp_year, gf_flag::Editing);
            if (!is_exist(workers_list, temp_fio, temp_post, temp_year)) {
                found->fio = temp_fio;
                found->post = temp_post;
                found->admission_year = temp_year;
                cout << "Сотрудник отредактирован." << endl << endl;
            }
            else if (found->fio == temp_fio && found->post == temp_post && found->admission_year == temp_year) {
                cout << " [X] Введённые новые данные сотрудника идентичны предыдущим. " << endl << endl;
            }
            else {
                cout << " |\\/| Введённые новые данные сотрудника не уникальны. " << endl;
                cout << " |/\\| Редактирование не выполнено. " << endl << endl;
            }
            subInserting = false;
            break;
        case 3:
            subInserting = false;
            Inserting = false;

            cout << endl << "Возвращение в меню." << endl;
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
    cout << " • Чтение из файла. ";
    while (Inserting) {
        cout << "Введите название файла или полный путь к файлу: " << endl;
        getline(cin, path);
        if (path == "/back") {
            cout << endl << "Возвращение в меню. " << endl;
            break;
        }
        else if (strcmp(path.c_str(), " ") == 0 || strcmp(path.c_str(), "\n") == 0 || strcmp(path.c_str(), "") == 0) {
            cout << " [X] Введена пустая строка. Попробуйте заново." << endl;
            continue;
        }
        size_t replpos=0;
        while ((replpos = path.find('\\', replpos)) != string::npos) {
            path.replace(replpos, 1, "/");
            replpos++;
        }
        if (path.rfind('/') != string::npos) { // выделение названия файла
            file = path.substr(path.rfind('/') + 1, string::npos);
        }
        else {
            file = path;
        }
        if (file.find('.') == string::npos) { // если файл без указания расширения
            file = file + ".txt";
            path = path + ".txt";
        }
        if (!file_valid(path)) {
            cout << " |\\/| Ошибка чтения из файла. Неверно указан путь к файлу." << endl;
            cout << " |/\\| Попробуйте заново: ";
            path.erase();
            file.erase();
            continue;
        }
        if (check_if_used(used_files, file)) {
            cout << "Файл с таким названием уже был прочитан ранее. Подтвердить дальнейшую работу с ним?" << endl;
            cout << "(1 - подтвердить, 2 - отменить)" << endl;
            getline(cin, text_command);
            while (subInserting) {
                if (to_number(text_command, command) == 0) {
                    if (command < 1 || command > 2) {
                        cout << "Неверный номер команды. Попробуйте заново." << endl;
                        getline(cin, text_command);
                        continue;
                    }
                    break;
                }
                else {
                    cout << "Команда не распознана. Попробуйте заново." << endl;
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
        cout << "1 - записать данные в конец списка; " << endl;
        cout << "2 - заменить список на данные из файла; " << endl;
        cout << "3 - изменить путь к файлу; " << endl;
        cout << "4 - отменить чтение файла. " << endl;
        cin.ignore(cin.rdbuf()->in_avail(), '\n');
        getline(cin, text_command);
        while (subInserting) {
            if (to_number(text_command, command) == 0) {
                if (command < 1 || command > 4) {
                    cout << "Неверный номер команды. Попробуйте заново." << endl;
                    getline(cin, text_command);
                    continue;
                }
                break;
            }
            else {
                cout << "Команда не распознана. Попробуйте заново." << endl;
                getline(cin, text_command);
            }
        }
        switch (command) {
        case 1: //в конец
            break;
        case 2: //заменить
            clear_list(workers_list);
            break;
        case 3: //изменить путь
            cout << endl << "Измените путь к файлу: " << endl;
            break;
        case 4:
            cout << endl << "Возвращение в меню. " << endl;
            Inserting = false;
            break;
        default:
            cout << "Команда не распознана. Попробуйте заново." << endl;
            break;
        }
        if (!Inserting && command == 4) break;
        else if (command == 3) continue;
        
        int flag = 0;
        flag = fread_list(workers_list, path);
        if (flag == 0) {
            cout << "Данные были загружены." << endl;
            if (!file_used) {
                push_back(used_files, file);
            }
            if (_AUTO_OUTPUT) {
                show_list(workers_list);
            }
        }
        else if (flag == 2) {
            cout << " |\\/| Все данные, хранимые в файле, не соответствуют формату," << endl;
            cout << " |/\\| или идентичны существующим. Чтение не произведено. " << endl;
        }
        else if (flag == 1) {
            cout << " [X] Не удалось открыть файл. " << endl;
        }
        
        break;
    }
    path.erase();
}

void menu_fwrite(WORKER*& workers_list) {
    if (is_list_empty(workers_list)) {
        cout << "Список пуст. Сохранение списка работников в файл не произведено. " << endl;
        return;
    }
    bool Inserting = true;
    string path;
    bool existing = false;
    int flag = 0;
    cout << " • Запись в файл. ";
    while (Inserting) {
        cout << "Введите название файла или полный путь к файлу: " << endl;
        getline(cin, path);
        if (path == "/back") {
            cout << endl << "Возвращение в меню. " << endl;
            break;
        }
        else if (strcmp(path.c_str(), " ") == 0 || strcmp(path.c_str(), "\n") == 0 || strcmp(path.c_str(), "") == 0) {
            cout << " [X] Введена пустая строка. Попробуйте заново." << endl;
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
            cout << " [X] Ошибка записи в файл. ";
            if (flag == 1) {
                cout << "Неверно указан путь к файлу." << endl;
            }
            cout << "Попробуйте заново: " << endl;
            getline(cin, path);
            if (path == "/back") {
                cout << endl << "Возвращение в меню. " << endl;
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
                cout << "Файл создан. ";
            }
            cout << "Запись произведена." << endl;
        }
        path.erase();
        break;
    }
}

void menu_sort(WORKER*& workers_list) {
    if (is_list_empty(workers_list)) {
        cout << "Список пуст. Сортировка не произведена. " << endl;
        return;
    }
    bool subInserting = true;
    string text_command;
    int command_1 = 0;
    int command_2 = 0;
    bool Direction = true; //true - возрастание, false - убывание
    cout << " • Сортировка списка. " << endl;
    cout << "1 - сортировка по фамилии и инициалам; " << endl;
    cout << "2 - сортировка по должности; " << endl;
    cout << "3 - сортировка по году трудоустройства; " << endl;
    cout << "4 - отмена." << endl;
    cin.ignore(cin.rdbuf()->in_avail(), '\n');
    getline(cin, text_command);
    while (subInserting) { // ввод первой команды
        if (text_command == "/back") {
            cout << "Возвращение в меню. " << endl;
            return;
        }
        else if (to_number(text_command, command_1) == 0) {
            if (command_1 < 1 || command_1 > 4) {
                cout << "Неверный номер команды. Попробуйте заново." << endl;
                getline(cin, text_command);
                continue;
            }
            break;
        }
        else {
            cout << "Команда не распознана. Попробуйте заново." << endl;
            getline(cin, text_command);
        }
    }
    if (command_1 == 4) {
        cout << "Возвращение в меню. " << endl;
        return;
    }
    cout << "1 - сортировка по возрастанию(или по алфавиту); " << endl;
    cout << "2 - сортировка по убыванию; " << endl;
    cin.ignore(cin.rdbuf()->in_avail(), '\n');
    getline(cin, text_command);
    while (subInserting) { // ввод второй команды
        if (to_number(text_command, command_2) == 0) {
            if (command_2 < 1 || command_2 > 2) {
                cout << "Неверный номер команды. Попробуйте заново." << endl;
                getline(cin, text_command);
                continue;
            }
            break;
        }
        else {
            cout << "Команда не распознана. Попробуйте заново." << endl;
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
        cout << "Возвращение в меню. " << endl;
        break;
    }
    if (command_1 == 4) return;

    if (check_list_accuracy(workers_list)) {
        cout << "Список отсортирован. " << endl;
    }
    else {
        cout << " [X] Нарашена структура списка." << endl;
    }
    if (_AUTO_OUTPUT) {
        show_list(workers_list);
    }
}

void menu_task(WORKER*& workers_list) {
    if (is_list_empty(workers_list)) {
        cout << "Список пуст. Выполнение задачи невозможно. " << endl;
        return;
    }
    WORKER* found_workers = nullptr;
    string text_command;
    int year = 0;
    bool subInserting = true;
    cout << " • Поиск заботника с бОльшим стажем работы. " << endl;
    cout << " • Введите сравниваемый стаж работы: " << endl;
    while (subInserting) {
        getline(cin, text_command);
        if (to_number(text_command, year)) {
            if (text_command == "/back") {
                cout << "Возвращение в меню. " << endl;
                return;
            }
            cout << "Год должен быть числом. Попробуйте заново." << endl;
            continue;
        }
        else if (year > 100) {
            cout << "Год должен быть настоящим. Попробуйте заново." << endl;
            continue;
        }
        else {
            break;
        }
    }
    found_workers = dotask_list(workers_list, year);
    if (found_workers != nullptr) {
        cout << "Список найденых рабочих: " << endl;
        show_list(found_workers);
        clear_list(found_workers);
    }
    else {
        cout << " [X] Ни один рабочий не удовлетворяет условию. " << endl;
    }
}

void menu_show(WORKER* workers_list) {
    if (!is_list_empty(workers_list)) {
        cout << " • Список: " << endl;
        show_list(workers_list);
    }
    else {
        cout << "Список пуст. " << endl;
    }
}

void menu_help() {
    cout << endl << setw(44) << right << "**** Помощь по командам ****" << endl << endl;
    cout << "/add - добавить сотрудника в позицию. Следующая команда:" << endl;
    cout << setw(5) << ' ' << setw(1) << "<номер позиции> - добавить на позицию;" << endl;
    cout << setw(5) << ' ' << setw(1) << "позиция -1 добавляет в конец." << endl;
    cout << endl;
    cout << "/delete - удалить сотрудника. Следующая команда:" << endl;
    cout << setw(5) << ' ' << setw(1) << "<номер позиции> - удалить из этой позиции;" << endl;
    cout << setw(5) << ' ' << setw(1) << "позиция -1 удаляет из конца." << endl;
    cout << endl;
    cout << "/edit - редактировать сотрудника. Следующая команда: " << endl;
    cout << setw(5) << ' ' << setw(1) << "<номер позиции>." << endl;
    cout << endl;
    cout << "/fread - считать данные сотрудников из файла. Следующая команда: " << endl;
    cout << setw(5) << ' ' << setw(1) << "<путь к файлу>." << endl;
    cout << endl;
    cout << "/fwrite - записать данные сотрудников в файл. Следующая команда: " << endl;
    cout << setw(5) << ' ' << setw(1) << "<путь к файлу>." << endl;
    cout << endl;
    cout << "/sort - сортировка списка сотрудников. Следующие команды: " << endl;
    cout << setw(5) << ' ' << setw(1) << "<поле сортировки>." << endl;
    cout << setw(5) << ' ' << setw(1) << "<направление сортировки>." << endl;
    cout << endl;
    cout << "/find - поиск сотрудника. Следующие команды: " << endl;
    cout << setw(5) << ' ' << setw(1) << "<данные сотрудника>." << endl;
    cout << endl;
    cout << "/task - поиск сотрудников с бОльшим годом трудоустройства." << endl;
    cout << setw(5) << ' ' << setw(1) << "<год трудоустройства>." << endl;
    cout << endl;
    cout << "/show - вывод списка сотрудников в консоль." << endl;
    cout << endl;
    cout << "/back - возвращение в меню. Можно использовать только" << endl;
    cout << setw(5) << ' ' << setw(1) << "сразу после вызова других команд." << endl;
    cout << endl;
    cout << "/help - помощь." << endl;
    cout << endl;
    cout << "/exit - завершение работы." << endl << endl;
    cout << "Формат ввода ФИО («_» это пробел):" << endl;
    cout << setw(5) << ' ' << setw(1) << "Фамилия_И.О." << endl;
    cout << setw(5) << ' ' << setw(1) << "Фамилия_И._О." << endl;
    cout << setw(5) << ' ' << setw(1) << "Фамилия_И." << endl;
    cout << "Год должен быть в диапазоне [1900; нынешний]." << endl;
}
