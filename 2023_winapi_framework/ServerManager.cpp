#include "pch.h"
#include "ServerManager.h"
#include "Debug.h"

struct Player {
    wstring id;
    wstring password;
    int score;
};

bool ServerManager::Load() {
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return false;
    }

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        WSACleanup();
        return false;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("172.31.2.235");  // ������ IP �ּ�
    serverAddr.sin_port = htons(8000);  // ������ ��Ʈ ��ȣ

    if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        closesocket(clientSocket);
        WSACleanup();
        return false;
    }
    Player p;
    p.id = playerId;
    p.password = playerPassword;
    p.score = 0;
    send(clientSocket, reinterpret_cast<char*>(&p), sizeof(p), 0);
    playerScore = p.score;
    isLogin = true;

    return true;
}

void ServerManager::Send() {
    Player playerData;
    playerData.id = playerId;
    playerData.password = playerPassword;
    playerData.score = playerScore;

    send(clientSocket, reinterpret_cast<const char*>(&playerData), sizeof(playerData), 0);

    // �������� �����͸� �޾ƿ��� ������ �ʿ��� ��쿡�� �Ʒ��� ���� ������ �߰��Ͽ� ������ �� �ֽ��ϴ�.
    /*
    if (/* �������� �����͸� �޾ƿ;� �ϴ� ���� * /) {
        for (int i = 0; i < 10; ++i) {
            Player receivedPlayer;
            recv(clientSocket, reinterpret_cast<char*>(&receivedPlayer), sizeof(receivedPlayer), 0);
            // �޾ƿ� �����͸� ó��
        }
    }
    */
}

void ServerManager::Release() {
    closesocket(clientSocket);
    WSACleanup();
}