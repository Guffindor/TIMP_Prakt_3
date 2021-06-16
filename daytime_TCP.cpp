
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;



int main(int argc, char **argv)
{
    sockaddr_in * myAddr = new (sockaddr_in);
    myAddr->sin_family = AF_INET;
    myAddr->sin_port = 0;
    myAddr->sin_addr.s_addr = 0;

    sockaddr_in * remoteAddr = new (sockaddr_in);
    remoteAddr->sin_family = AF_INET;
    remoteAddr->sin_port = htons(13); //порт
    remoteAddr->sin_addr.s_addr = inet_addr("82.179.90.12");

    char *buf = new char [256];
    strcpy(buf, "Сколько времечка??\n");
    int msgLen = strlen(buf);

    int mySocket = socket(AF_INET, SOCK_STREAM, 0);  //udp типа поэтому DGRAM
    if (mySocket == -1) {
        cerr << "Ошибка открытия сокета";
    }

    int rc = bind(mySocket, (const sockaddr*) myAddr, sizeof (sockaddr_in));
    if (rc == -1) {
        close(mySocket);
        cerr << "Ошибка привязки сокета к адресу";
    }

    rc = connect(mySocket, (const sockaddr*) remoteAddr, sizeof(sockaddr_in));
    if (rc == -1) {
        close(mySocket);
        cerr << "Ошибка соединения с удаленным сервером";
    }

    rc = send(mySocket, buf, msgLen, 0);
    if (rc == -1) {
        close(mySocket);
        cerr << "Ошибка отправки сообщения";
    }
    cout << "Отправили: " << buf << endl;

    rc = recv(mySocket, buf, 256, 0);
    if (rc == -1) {
        close(mySocket);
        cerr << "Ошибка получения сообщения";
    }
    buf[rc]= '\0';
    cout<<"Приняли: "<< buf << endl;


    close(mySocket);
    delete myAddr;
    delete remoteAddr;
    delete[] buf;

    return 0;
}
