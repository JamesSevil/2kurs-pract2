#pragma once

#include "includes.h"
#include "list.h"
#include "json.hpp"

int CountLine(string& filepath); // ф-ия подсчёта строк в файле
string finput(string& filepath); // чтение из файла
void foutput(string& filepath, string text); // запись в файл

struct DataBase {
    string nameBD; // название БД
    int tupleslimit; // лимит строк
    SinglyLinkedList<string> nametables; // названия таблиц
    SinglyLinkedList<string> stlb; // столбцы таблиц
    SinglyLinkedList<int> fileindex; // кол-во файлов таблиц

    struct Where { // структура для фильтрации
        string table;
        string column;
        string value;
        string logicalOP;
        bool check; // В частности для select, проверка условия(если просто условие - true, если условиестолбец - false)
    };

    void parse(); // ф-ия парсинга
    void mkdir(); // ф-ия формирования директории
    string checkcommand(string& command); // ф-ия фильтрации команд

    // ф-ии insert
    string isValidInsert(string& command); // ф-ия обработки команды INSERT
    string insert(string& table, string& values); // ф-ия вставки в таблицу

    // ф-ии delete
    string isValidDel(string& command); // ф-ия обработки команды DELETE
    string del(string& table); // ф-ия удаления всех строк таблицы
    string delWithValue(string& table, string& stolbec, string& values); // ф-ия удаления строк таблицы по значению
    string delWithLogic(SinglyLinkedList<Where>& conditions, string& table); // ф-ия удаления строк таблицы с логикой

    // ф-ии select
    string isValidSelect(string& command); // ф-ия проверки ввода команды select
    string select(SinglyLinkedList<Where>& conditions); // ф-ия обычного селекта
    string selectWithValue(SinglyLinkedList<Where>& conditions, string& table, string& stolbec, struct Where value); // ф-ия селекта с where для обычного условия
    string selectWithLogic(SinglyLinkedList<Where>& conditions, SinglyLinkedList<string>& table, SinglyLinkedList<string>& stolbec, SinglyLinkedList<Where>& value);

    // Вспомогательные ф-ии, чтобы избежать повтора кода в основных ф-иях
    bool checkLockTable(string table); // ф-ия проверки, закрыта ли таблица
    SinglyLinkedList<int> findIndexStlb(SinglyLinkedList<Where>& conditions); // ф-ия нахождения индекса столбцов(для select)
    int findIndexStlbCond(string table, string stolbec); // ф-ия нахождения индекса столбца условия(для select)
    SinglyLinkedList<string> textInFile(SinglyLinkedList<Where>& conditions); // ф-ия инпута текста из таблиц(для select)
    SinglyLinkedList<string> findStlbTable(SinglyLinkedList<Where>& conditions, SinglyLinkedList<string>& tables, int stlbindexvalnext, string table); // ф-ия инпута нужных колонок из таблиц для условиястолбец(для select)
    string sample(SinglyLinkedList<int>& stlbindex, SinglyLinkedList<string>& tables); // ф-ия выборки(для select)
};

#include "../src/menu.cpp"