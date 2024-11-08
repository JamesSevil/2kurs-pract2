#pragma once

#include "includes.h"
#include "menu.h"

#define PORT 7432

int server, new_socket; // идентификатор сокетов сервера и нового(для взаимодействия)
struct sockaddr_in server_address; // информация о адресе сервера
int addrlen = sizeof(server_address);
int opt = 1; // переменная для настройки сокета

void createServer(DataBase& carshop); 
void createSocket(); // ф-ия создания сокета сервера
void connectClient(DataBase& carshop); // ф-ия прослушивания и принятия входящих соединений
void procOfReq(int client_socket, DataBase& carshop, mutex& mx); // ф-ия обработки запроса от клиента

#include "../src/network.cpp"