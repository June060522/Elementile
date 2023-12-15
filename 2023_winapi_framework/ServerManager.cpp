#include "pch.h"
#include "ServerManager.h"
#include "Debug.h"

struct Player {
	string id = "";
	string password = "";
	int score = 0;
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
    serverAddr.sin_addr.s_addr = inet_addr("172.31.2.235");  // ������ IP �ּ� (���� ȣ��Ʈ)
    serverAddr.sin_port = htons(8000);  // ������ ��Ʈ ��ȣ

    if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        closesocket(clientSocket);
        WSACleanup();
        return false;
    }

    Player* p = new Player();
    p->id = playerId;
    p->password = playerPassword;
    p->score = 0;

    // �������� ũ�⸦ ����
    // int dataSize = sizeof(Player);
    // {
    //     std::lock_guard<std::mutex> lock(sendMutex);  // send�� ���ؽ� ����
    //     send(clientSocket, reinterpret_cast<char*>(&dataSize), sizeof(int), 0);
    // }

    // ���� �����͸� ����
    {
        std::lock_guard<std::mutex> lock(sendMutex);  // send�� ���ؽ� ����
        send(clientSocket, reinterpret_cast<char*>(p), sizeof(Player), 0);
    }

    // �񵿱�� �������� �α��� ������ ��ٸ�
    Player* receivedPlayer = new Player();
    {
        std::lock_guard<std::mutex> lock(recvMutex);  // recv�� ���ؽ� ����
        recv(clientSocket, reinterpret_cast<char*>(receivedPlayer), sizeof(Player), 0);
    }
    // �޾ƿ� �����͸� ó��
    playerScore = receivedPlayer->score;
    isLogin = true;
    closesocket(clientSocket);

    return true;
}


void ServerManager::Send() {
	Player playerData;
	playerData.id = playerId;
	playerData.password = playerPassword;
	playerData.score = playerScore;

	// �������� ũ�⸦ ����
	int dataSize = sizeof(Player);
	{
		std::lock_guard<std::mutex> lock(sendMutex);  // send�� ���ؽ� ����
		send(clientSocket, reinterpret_cast<const char*>(&dataSize), sizeof(int), 0);
	}

	// ���� �����͸� ����
	{
		std::lock_guard<std::mutex> lock(sendMutex);  // send�� ���ؽ� ����
		send(clientSocket, reinterpret_cast<const char*>(&playerData), sizeof(Player), 0);
	}

	// �������� ������ ��ٸ�
	// ...

	// �������� �����͸� �޾ƿ��� ������ �ʿ��� ��쿡�� �Ʒ��� ���� ������ �߰��Ͽ� ������ �� �ֽ��ϴ�.
	/*
	if (/* �������� �����͸� �޾ƿ;� �ϴ� ���� * /) {
		for (int i = 0; i < 10; ++i) {
			Player receivedPlayer;
			{
				std::lock_guard<std::mutex> lock(recvMutex);  // recv�� ���ؽ� ����
				recv(clientSocket, reinterpret_cast<char*>(&receivedPlayer), sizeof(receivedPlayer), 0);
			}
			// �޾ƿ� �����͸� ó��
		}
	}
	*/
}

void ServerManager::Release() {
	closesocket(clientSocket);
	WSACleanup();
}