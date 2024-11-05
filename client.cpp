#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 7432

using namespace std;

int main() {
    int client;
    struct sockaddr_in server_address;

    // создание TCP-сокета
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0) {
        cout << "Ошибка установленного сокета!" << endl;
        return -1;
    }

    // установка адреса и порта
    server_address.sin_port = htons(PORT); // преобразование порта в сетевой порядок байт
    server_address.sin_family = AF_INET; // семейство адресов (IPv 4)

    // Преобразование адреса IPv4 из текстового представления в двоичное
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        cout << "Неверный адрес/Адрес не поддерживается" << endl;
        return -1;
    }

    // подключение к серверу
    if ((connect(client, (struct sockaddr*)&server_address, sizeof(server_address))) < 0) {
        cout << "Ошибка подключения к серверу!" << endl;
        return -1;
    }
    cout << "Успешное подключение к серверу!" << endl;

    while (true) {
        // отправка сообщений серверу
        string message;
        cout << "Вы: ";
        getline(cin, message);
        if (message == "#") { // отключаемся
            cout << "Завершение работы..." << endl;
            break;
        }
        send(client, message.c_str(), message.size(), 0);
        // чтение ответа от сервера
        char buffer[1024] = {0};
        int check = read(client, buffer, 1024);
        if (check <= 0) { // если сервер отключился
            cout << "Сервер отключился, завершение работы..." << endl;
            break;
        }
        string conditions(buffer);
        cout << "Сервер: " << conditions << endl;
    }

    // закрытие сокета
    close(client);

    return 0;
}