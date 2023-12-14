#include "pch.h"
#include "DBManager.h"
#include "Debug.h"

struct Player {
    int id;
    int score;
};

bool DBManager::Init()
{
    
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return false;
    }

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        WSACleanup();
        return false;
    }

   
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // ������ IP �ּ�
    serverAddr.sin_port = htons(8888);  // ������ ��Ʈ ��ȣ

    if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        closesocket(clientSocket);
        WSACleanup();
        return false;
    }

    playerId = rand() % 100000;
    playerScore = rand() % 100000;

    return true;
}

void DBManager::Update()
{
    send(clientSocket, reinterpret_cast<const char*>(&playerId), sizeof(playerId), 0);

    // �÷��̾��� ���� ����
    send(clientSocket, reinterpret_cast<const char*>(&playerScore), sizeof(playerScore), 0);

    // ��ŷ ���� ���� �� ���
    for (int i = 0; i < 10; ++i) {
        Player player;
        recv(clientSocket, reinterpret_cast<char*>(&player), sizeof(player), 0);
        Debug(player.id, 10, 100 + 20 * i);
        Debug(player.score, 100, 100 + 20 * i);
    }
}

void DBManager::Release()
{
    closesocket(clientSocket);
    WSACleanup();

}
