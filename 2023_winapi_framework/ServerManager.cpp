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
    serverAddr.sin_addr.s_addr = inet_addr("172.31.2.235");  // 서버의 IP 주소 (로컬 호스트)
    serverAddr.sin_port = htons(8000);  // 서버의 포트 번호

    if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        closesocket(clientSocket);
        WSACleanup();
        return false;
    }

    Player* p = new Player();
    p->id = playerId;
    p->password = playerPassword;
    p->score = 0;

    // 데이터의 크기를 전송
    // int dataSize = sizeof(Player);
    // {
    //     std::lock_guard<std::mutex> lock(sendMutex);  // send에 뮤텍스 적용
    //     send(clientSocket, reinterpret_cast<char*>(&dataSize), sizeof(int), 0);
    // }

    // 실제 데이터를 전송
    {
        std::lock_guard<std::mutex> lock(sendMutex);  // send에 뮤텍스 적용
        send(clientSocket, reinterpret_cast<char*>(p), sizeof(Player), 0);
    }

    // 비동기로 서버에서 로그인 응답을 기다림
    Player* receivedPlayer = new Player();
    {
        std::lock_guard<std::mutex> lock(recvMutex);  // recv에 뮤텍스 적용
        recv(clientSocket, reinterpret_cast<char*>(receivedPlayer), sizeof(Player), 0);
    }
    // 받아온 데이터를 처리
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

	// 데이터의 크기를 전송
	int dataSize = sizeof(Player);
	{
		std::lock_guard<std::mutex> lock(sendMutex);  // send에 뮤텍스 적용
		send(clientSocket, reinterpret_cast<const char*>(&dataSize), sizeof(int), 0);
	}

	// 실제 데이터를 전송
	{
		std::lock_guard<std::mutex> lock(sendMutex);  // send에 뮤텍스 적용
		send(clientSocket, reinterpret_cast<const char*>(&playerData), sizeof(Player), 0);
	}

	// 서버에서 응답을 기다림
	// ...

	// 서버에서 데이터를 받아오는 조건이 필요한 경우에는 아래와 같이 조건을 추가하여 수신할 수 있습니다.
	/*
	if (/* 서버에서 데이터를 받아와야 하는 조건 * /) {
		for (int i = 0; i < 10; ++i) {
			Player receivedPlayer;
			{
				std::lock_guard<std::mutex> lock(recvMutex);  // recv에 뮤텍스 적용
				recv(clientSocket, reinterpret_cast<char*>(&receivedPlayer), sizeof(receivedPlayer), 0);
			}
			// 받아온 데이터를 처리
		}
	}
	*/
}

void ServerManager::Release() {
	closesocket(clientSocket);
	WSACleanup();
}