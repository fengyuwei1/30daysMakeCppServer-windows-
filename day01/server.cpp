#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <winsock2.h>
#include <cstring>
#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA data;
    if (WSAStartup(MAKEWORD(2, 2), &data) != 0) {
        printf("WSAStartup ʧ��\n");
        return 1;
    }

    SOCKET socketword = socket(AF_INET, SOCK_STREAM, 0);
    if (socketword == INVALID_SOCKET) {
        printf("�׽��ִ���ʧ��: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    struct sockaddr_in serv_addr;
    ZeroMemory(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(8888);

    if (bind(socketword, (sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
        printf("��ʧ��: %d\n", WSAGetLastError());
        closesocket(socketword);
        WSACleanup();
        return 1;
    }

    if (listen(socketword, SOMAXCONN) == SOCKET_ERROR) {
        printf("����ʧ��: %d\n", WSAGetLastError());
        closesocket(socketword);
        WSACleanup();
        return 1;
    }

    printf("����������8888�˿��Ͻ��м���\n");

    struct sockaddr_in clnt_addr;
    int clnt_addr_len = sizeof(clnt_addr);
    ZeroMemory(&clnt_addr,sizeof(clnt_addr));

    SOCKET clnt_socket_word = accept(socketword, (sockaddr*)&clnt_addr, &clnt_addr_len);
    if (clnt_socket_word == INVALID_SOCKET) {
        printf("����ʧ��: %d\n", WSAGetLastError());
        closesocket(socketword);
        WSACleanup();
        return 1;
    }

    printf("�¿ͻ��������ӣ�IP: %s Port: %d\n",inet_ntoa(clnt_addr.sin_addr),ntohs(clnt_addr.sin_port));

    closesocket(clnt_socket_word);
    closesocket(socketword);
    WSACleanup();
    return 0;
}